#include "VertexArray.hpp"

VertexArray::VertexArray(const void* positions, unsigned int size) {
    unsigned int vSize = 3;
    GLCall(glGenVertexArrays(1, &m_ID));  
    GLCall(glBindVertexArray(m_ID));
    VertexBuffer vb(positions, (vSize*size)*sizeof(float));
    GLCall(glEnableVertexAttribArray(0));
    // index, values per vertex, type, normalize?, size of vertex in bytes, offset to first vertex 
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * vSize, 0));
    
    // color buffer
    static const float colors[] = {
        0.583f,  0.771f,  0.014f,

        0.597f,  0.770f,  0.761f,
        0.597f,  0.770f,  0.761f,

        0.014f,  0.184f,  0.576f,
        0.014f,  0.184f,  0.576f,

        0.997f,  0.513f,  0.064f,

        0.055f,  0.953f,  0.042f,

        0.982f,  0.099f,  0.879f,
    };
    // color buffer
    unsigned int cb;
    GLCall(glGenBuffers(1, &cb)); 
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, cb));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW)); // danger: sizeof arr
    GLCall(glEnableVertexAttribArray(1));
    GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0)); 

    // UNBIND
    GLCall(glBindVertexArray(0));
}

void VertexArray::Bind() {
    GLCall(glBindVertexArray(m_ID));
}
