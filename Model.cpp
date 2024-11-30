#include "Model.h"
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

Model::Model(float* vertices, float* colors, float* uvs, int vertexCount, bool interleaved, int attributeFormat)
    : vertexCount(vertexCount), vboVertices(0), vboColors(0), vboUVs(0), vao(0), interleaved(interleaved), attributeFormat(attributeFormat) {

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);

    if (interleaved) {
        int stride = 0;
        if (attributeFormat & POSITION) stride += 3;
        if (attributeFormat & NORMAL)   stride += 3;
        if (attributeFormat & UV)       stride += 2;

        glBufferData(GL_ARRAY_BUFFER, vertexCount * stride * sizeof(float), vertices, GL_STATIC_DRAW);

        int offset = 0;

        if (attributeFormat & POSITION) {
            setupVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
            offset += 3;
        }

        if (attributeFormat & NORMAL) {
            setupVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
            offset += 3;
        }

        if (attributeFormat & UV) {
            setupVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
        }
    }
    else {
        glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(float), vertices, GL_STATIC_DRAW);
        setupVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        if (colors != nullptr) {
            glGenBuffers(1, &vboColors);
            glBindBuffer(GL_ARRAY_BUFFER, vboColors);
            glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(float), colors, GL_STATIC_DRAW);
            setupVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        }

        if (uvs != nullptr) {
            glGenBuffers(1, &vboUVs);
            glBindBuffer(GL_ARRAY_BUFFER, vboUVs);
            glBufferData(GL_ARRAY_BUFFER, vertexCount * 2 * sizeof(float), uvs, GL_STATIC_DRAW);
            setupVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Model::Model(const std::string& path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    processNode(scene->mRootNode, scene);

    glBindVertexArray(0);
}

void Model::processNode(aiNode* node, const aiScene* scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh, scene);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene);
    }
}

void Model::processMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        // Positions
        vertices.push_back(mesh->mVertices[i].x);
        vertices.push_back(mesh->mVertices[i].y);
        vertices.push_back(mesh->mVertices[i].z);

        // Normals
        if (mesh->HasNormals()) {
            vertices.push_back(mesh->mNormals[i].x);
            vertices.push_back(mesh->mNormals[i].y);
            vertices.push_back(mesh->mNormals[i].z);
        }
        else {
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);
        }

        // Texture coordinates
        if (mesh->mTextureCoords[0]) {
            vertices.push_back(mesh->mTextureCoords[0][i].x);
            vertices.push_back(mesh->mTextureCoords[0][i].y);
        }
        else {
            vertices.push_back(0.0f);
            vertices.push_back(0.0f);
        }
    }

    // Process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Upload vertex data
    glGenBuffers(1, &vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // Upload index data
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Setup vertex attributes
    setupVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);                 // Positions
    setupVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // Normals
    setupVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // UVs

    vertexCount = static_cast<int>(vertices.size() / 8); // 8 = position(3) + normal(3) + UV(2)
    indexCount = static_cast<int>(indices.size());
}

void Model::setupVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);
}

void Model::draw() const {
    glBindVertexArray(vao);
    if (indexCount > 0) {
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    }
    else {
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    }
    glBindVertexArray(0);
}

Model::~Model() {
    if (vboVertices) {
        glDeleteBuffers(1, &vboVertices);
    }
    if (vboColors) {
        glDeleteBuffers(1, &vboColors);
    }
    if (ebo) {
        glDeleteBuffers(1, &ebo);
    }
    if (vboUVs) {
        glDeleteBuffers(1, &vboUVs);
    }
    if (vao) {
        glDeleteVertexArrays(1, &vao);
    }
}
