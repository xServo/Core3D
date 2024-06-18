#ifndef Renderer_hpp
#include <signal.h>
#include <glew.h>
// unfinished https://www.youtube.com/watch?v=FBbPWSOQ0-w&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=10
#define ASSERT(x) if (!(x)) raise(SIGTRAP);
void GLClearError(); 
bool GLLogCall(); 
#endif