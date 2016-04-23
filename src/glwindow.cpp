#include <glwindow.h>

GlWindow::GlWindow(std::string title, int width, int height, bool fullscreen) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
            SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

    const char* ctitle = title.c_str();
    if (fullscreen) {
        this->window = SDL_CreateWindow(ctitle, SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED, width, height,
                SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
    }
    else {
        this->window = SDL_CreateWindow(ctitle, SDL_WINDOWPOS_CENTERED,
                SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    }


    this->context = SDL_GL_CreateContext(window);
}

SDL_Window* GlWindow::getWindow() {
    return this->window;
}

SDL_GLContext GlWindow::getContext() {
    return this->context;
}

GlWindow::~GlWindow() {
    SDL_GL_DeleteContext(this->context);
    SDL_Quit();
}

void printGlError() {
    GLenum glError = glGetError();
    bool done = false;
    while (!done) {
        glError = glGetError();
        switch (glError) {
            case GL_NO_ERROR:
                done = true;
                break;
            case GL_INVALID_ENUM:
                std::cerr << "GL_INVALID_ENUM\n";
                break;
            case GL_INVALID_VALUE:
                std::cerr << "GL_INVALID_VALUE\n";
                break;
            case GL_INVALID_OPERATION:
                std::cerr << "GL_INVALID_OPERATION\n";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION\n";
                break;
            case GL_OUT_OF_MEMORY:
                std::cerr << "GL_OUT_OF_MEMORY\n";
                break;
            case GL_STACK_UNDERFLOW:
                std::cerr << "GL_STACK_UNDERFLOW\n";
                break;
            case GL_STACK_OVERFLOW:
                std::cerr << "GL_STACK_OVERFLOW\n";
                break;
            default:
                std::cerr << "Unknown OpenGL error!\n";
                break;
        }
    }
}
