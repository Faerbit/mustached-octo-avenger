#ifndef CONTEXT_H_INCLUDED
#define CONTEXT_H_INCLUDED

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <string>
#include <iostream>

#endif

class Context {
    public:
        Context(std::string title, int width, int height, bool fullscreen);
        ~Context();
        SDL_Window* getWindow();
        SDL_GLContext getContext();
    private:
        SDL_Window* window;
        SDL_GLContext context;
};
