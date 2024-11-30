#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <string>

enum AttributeFormat {
    POSITION = 1 << 0, 
    NORMAL = 1 << 1, 
    UV = 1 << 2
};

class Model {
public:
    Model(float* vertices, float* colors, float* uvs, int vertexCount, bool interleaved, int attributeFormat);
    Model(const std::string& path);
    void draw() const;

    ~Model();

private:
    GLuint vao; 
    GLuint vboVertices;
    GLuint vboColors;
    GLuint vboUVs;
    GLuint ebo;
    int vertexCount;
    bool interleaved;
    int attributeFormat;
    int indexCount;

    void processNode(struct aiNode* node, const struct aiScene* scene);

    void processMesh(struct aiMesh* mesh, const struct aiScene* scene);

    void setupVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
};

#endif