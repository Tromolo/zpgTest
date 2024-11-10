#include "Model.h"

Model::Model(float* vertices, float* colors, int vertexCount, bool interleaved)
    : vertexCount(vertexCount), vboVertices(0), vboColors(0), vao(0), interleaved(interleaved) {

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);

    if (interleaved) {
        glBufferData(GL_ARRAY_BUFFER, vertexCount * 6 * sizeof(float), vertices, GL_STATIC_DRAW);

        setupVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);          // Position
        setupVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Color
        setupVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Normal
    }
    else {
        glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(float), vertices, GL_STATIC_DRAW);
        setupVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);           // Position

        if (colors != nullptr) {
            glGenBuffers(1, &vboColors);
            glBindBuffer(GL_ARRAY_BUFFER, vboColors);
            glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * sizeof(float), colors, GL_STATIC_DRAW);
            setupVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);      // Color
            glBindBuffer(GL_ARRAY_BUFFER, 0);
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
        vboVertices = 0; 
    }
    if (vboColors) {
        glDeleteBuffers(1, &vboColors);
        vboColors = 0;
    }
    if (vao) {
        glDeleteVertexArrays(1, &vao);
        vao = 0;
    }
}
