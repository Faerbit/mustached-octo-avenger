#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <SDL.h>

#include <string>

#endif 

class Window {
    public:
        Window(std::string title, int width, int height, bool fullscreen);
        ~Window();
        SDL_Window* getWindow();
    private:
        SDL_Window* window;
};
