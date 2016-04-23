#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED

//#include <GL/glew.h>
#include <epoxy/gl.h>
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>


class Shader {
    public:
        Shader(GLenum shaderType, std::string path);
        ~Shader();
        GLuint getReference();
    private:
        GLuint reference;
};

#endif
