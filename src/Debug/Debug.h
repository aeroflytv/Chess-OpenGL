#include <iostream>

#define LOG(x) std::cout << "[" << __FILE_NAME__ << ": " << __LINE__ << "] " << x << std::endl;



#define ASSERT(x) if (!(x)) std::cout << "Error" << std::endl;;
#define GLCall(x) GLClearError();\
  x;\
  ASSERT(GLLogCall(#x, __FILE__, __LINE__))


void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

