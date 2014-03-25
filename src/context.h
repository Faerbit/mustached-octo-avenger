#ifndef CONTEXT_H_INCLUDED
#define CONTEXT_H_INCLUDED

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <iostream>

#endif

class Context {
    public:
        Context(SDL_Window* window);
        ~Context();
        SDL_GLContext getContext();
    private:
        SDL_GLContext context;
};
