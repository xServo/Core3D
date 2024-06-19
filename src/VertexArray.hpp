#pragma once 
#include <glew.h>
#include <iostream>
#include "VertexBuffer.hpp"
#include "Renderer.hpp"

class VertexArray {
    public:
        unsigned int m_ID;
        VertexArray(const void* positions, unsigned int size);
        void Bind();
    
};