#include <context.h>

Context::Context(SDL_Window* window) {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    this->context = SDL_GL_CreateContext(window);

    glewExperimental = GL_TRUE;
    // Ignore glewInit GlError
    GLenum glError = glGetError();
    if (glError != GL_NO_ERROR){
        std::cout << "Unexpected OpenGL error before glewInit()." << std::endl;
    }
    glewInit();
    glError = glGetError();
    if (glError != GL_INVALID_ENUM) {
        std::cout << "Unexpected OpenGL error after glewInit()." << std::endl;
    }
}


SDL_GLContext Context::getContext() {
    return this->context;
}

Context::~Context() {
    SDL_GL_DeleteContext(this->context);
}
