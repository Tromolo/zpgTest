#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>

class Model {
public:
    Model(float* vertices, float* colors, int vertexCount, bool interleaved);
    void setupVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
    ~Model();
    void draw() const;      

private:
    GLuint vao;         
    GLuint vboVertices;    
    GLuint vboColors;     
    int vertexCount;       
    bool interleaved;
};

#endif
