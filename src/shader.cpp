#include <shader.h>

Shader::Shader(GLenum shaderType, std::string path) {
    std::string source;
    std::ifstream sourceFile(path);
    if (sourceFile.is_open()) {
        source.assign(std::istreambuf_iterator<char>(sourceFile),
                    std::istreambuf_iterator<char>());
        sourceFile.close();
    }
    //TODO implement exceptions
    else {
        std::cerr << "Unable to open '" << path << "'!" << std::endl;
    }
    const char * csource = source.c_str();

    this->reference = glCreateShader(shaderType);
    glShaderSource(this->reference, 1, &csource, NULL);
    glCompileShader(this->reference);

    GLint status;
    glGetShaderiv(this->reference, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetShaderiv(this->reference, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *infoLog = new GLchar[infoLogLength];
        glGetShaderInfoLog(this->reference, infoLogLength, NULL, infoLog);
        std::cerr << "Compilation of shader '" << path << "' failed. Log:"
            << std::endl << infoLog << std::endl;
        delete [] infoLog;
    }
}

GLuint Shader::getReference() {
    return this->reference;
}

Shader::~Shader() {
    glDeleteShader(this->reference);
}
