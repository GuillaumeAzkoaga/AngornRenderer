#include "RenderingUtils.h"
#include <iostream>
#include <cstdio>

#include <string>


GLenum glCheckError_(const char* file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
            case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
       
        std::string out = "GL_" + error + " at " + std::string(file) + " (" + std::to_string(line)+  ")." + "\n \nMore details in errorlog.txt" ;
        MessageBox(NULL, out.c_str(), "GL ERROR" , MB_TASKMODAL | MB_SETFOREGROUND | MB_ICONERROR);
        ExitProcess(0);
    }
    return errorCode;
}

void GLAPIENTRY MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,	
    const GLchar* message,	
    const void* userParam)
{        
    std::cout << "GL Error: " + std::string(message) << std::endl;

	/*fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);*/
}

