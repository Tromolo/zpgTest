#include "Model.h"
#include <iostream>

Model::Model(float* vertices, float* colors, float* uvs, int vertexCount, bool interleaved, int attributeFormat)
    : vertexCount(vertexCount), vboVertices(0), vboColors(0), vboUVs(0), vao(0), interleaved(interleaved), attributeFormat(attributeFormat) {

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);

    if (interleaved) {
        // Calculate stride based on attribute format
        int stride = 0;
        if (attributeFormat & POSITION) stride += 3; // 3 floats for Position
        if (attributeFormat & NORMAL)   stride += 3; // 3 floats for Normal
        if (attributeFormat & UV)       stride += 2; // 2 floats for UV

        glBufferData(GL_ARRAY_BUFFER, vertexCount * stride * sizeof(float), vertices, GL_STATIC_DRAW);

        int offset = 0;

        // Set up attributes dynamically based on the format
        if (attributeFormat & POSITION) {
            setupVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
            offset += 3; // Move offset for the next attribute
        }

        if (attributeFormat & NORMAL) {
            setupVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
            offset += 3; // Move offset for the next attribute
        }

        if (attributeFormat & UV) {
            setupVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
        }
    }
    else {
        // Handle separate buffers for each attribute
        glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(float), vertices, GL_STATIC_DRAW);
        setupVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Position

        if (colors != nullptr) {
            glGenBuffers(1, &vboColors);
            glBindBuffer(GL_ARRAY_BUFFER, vboColors);
            glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(float), colors, GL_STATIC_DRAW);
            setupVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Color
        }

        if (uvs != nullptr) {
            glGenBuffers(1, &vboUVs);
            glBindBuffer(GL_ARRAY_BUFFER, vboUVs);
            glBufferData(GL_ARRAY_BUFFER, vertexCount * 2 * sizeof(float), uvs, GL_STATIC_DRAW);
            setupVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0); // UV
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Model::setupVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);
}

void Model::draw() const {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}

Model::~Model() {
    if (vboVertices) {
        glDeleteBuffers(1, &vboVertices);
    }
    if (vboColors) {
        glDeleteBuffers(1, &vboColors);
    }
    if (vboUVs) {
        glDeleteBuffers(1, &vboUVs);
    }
    if (vao) {
        glDeleteVertexArrays(1, &vao);
    }
}
