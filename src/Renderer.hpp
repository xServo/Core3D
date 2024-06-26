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
        Renderer(const int WIDTH, const int HEIGHT)
        : SCREEN_WIDTH(WIDTH), SCREEN_HEIGHT(HEIGHT) {
          GLFWwindow* gWindow = NULL;
          init();
          Shader();
          Projection();
        }

        GLFWwindow* gWindow;

        void Draw();
        void Swap();
        void Clear();
        void Wireframe(bool flag);
        void init();
        void quit();
        bool m_Wireframe;
        unsigned int shaderID;
    private:
        const int SCREEN_WIDTH;
        const int SCREEN_HEIGHT;
        const float NEAR_PLANE = 0.1; 
        const float FAR_PLANE = 10;
        void Shader();
        void Projection();
};
