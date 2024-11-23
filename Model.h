#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>

// Attribute Format Flags
enum AttributeFormat {
    POSITION = 1 << 0, // Binary 0001: Position (3 floats)
    NORMAL = 1 << 1, // Binary 0010: Normal (3 floats)
    UV = 1 << 2  // Binary 0100: UV (2 floats)
};

class Model {
public:
    // Constructor for interleaved or separate attribute data
    Model(float* vertices, float* colors, float* uvs, int vertexCount, bool interleaved, int attributeFormat);

    // Draw the model
    void draw() const;

    // Destructor to clean up buffers
    ~Model();

private:
    GLuint vao;          // Vertex Array Object
    GLuint vboVertices;  // Vertex Buffer Object for vertices
    GLuint vboColors;    // VBO for colors (if provided separately)
    GLuint vboUVs;       // VBO for UVs (if provided separately)
    int vertexCount;     // Number of vertices
    bool interleaved;    // Whether data is interleaved
    int attributeFormat; // Attribute format (Position, Normal, UV)

    // Helper to set up vertex attribute pointers
    void setupVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
};

#endif // MODEL_H
