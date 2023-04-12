#include "renderer.h"
#include "iostream"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum temp = glGetError())
    {
        std::cout << "ERROR : " << temp << function << ' ' << file << ":" << line << std::endl;
        return false;
    }
    return true;
}