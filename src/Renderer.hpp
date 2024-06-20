#pragma once

#include <iostream>
#include <signal.h>
#include <glew.h>
#include <glfw3.h>
// unfinished https://www.youtube.com/watch?v=FBbPWSOQ0-w&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=10
#define ASSERT(x) if (!(x)) raise(SIGTRAP);
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError(); 
bool GLLogCall(const char* function, const char* file, int line); 

class Renderer {
    public:
        GLFWwindow* gWindow;
        Renderer(GLFWwindow* window);
        bool m_Wireframe;

        void Draw();
        void Clear();
        void Wireframe(bool flag);
};
