#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>

enum AttributeFormat {
    POSITION = 1 << 0, 
    NORMAL = 1 << 1, 
    UV = 1 << 2
};

class Model {
public:
    Model(float* vertices, float* colors, float* uvs, int vertexCount, bool interleaved, int attributeFormat);

    void draw() const;

    ~Model();

private:
    GLuint vao; 
    GLuint vboVertices;
    GLuint vboColors;
    GLuint vboUVs;
    int vertexCount;
    bool interleaved;
    int attributeFormat;

    void setupVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
};

#endif