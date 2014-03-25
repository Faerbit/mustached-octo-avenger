#include <context.h>

Context::Context(std::string title, int width, int height, bool fullscreen) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    const char* ctitle = title.c_str();
    if (fullscreen) {
        std::cout << "Fullscreen mode not implemented" << std::endl;
    }
    else {
        this->window = SDL_CreateWindow(ctitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    }
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

SDL_Window* Context::getWindow() {
    return this->window;
}

SDL_GLContext Context::getContext() {
    return this->context;
}

Context::~Context() {
    SDL_GL_DeleteContext(this->context);
    SDL_Quit();
}
