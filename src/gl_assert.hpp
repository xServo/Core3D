#pragma once
#ifdef _WIN32
#include <intrin.h>
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
          x;\
          ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#include <signal.h>
#define ASSERT(x) if (!(x)) raise(SIGTRAP);
#define GLCall(x) GLClearError();\
      x;\
      ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#endif
void GLClearError(); 
bool GLLogCall(const char* function, const char* file, int line); 
