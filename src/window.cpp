#include <window.h>

Window::Window(std::string title, int width, int height, bool fullscreen) {
    SDL_Init(SDL_INIT_VIDEO);

    const char* ctitle = title.c_str();
    if (fullscreen) {
        std::cout << "Fullscreen mode not implemented" << std::endl;
    }
    else {
        this->window = SDL_CreateWindow(ctitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    }
}

SDL_Window* Window::getWindow() {
    return this->window;
}

Window::~Window() {
    SDL_Quit();
}
