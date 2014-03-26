#ifndef GLWINDOW_H_INCLUDED
#define GLWINDOW_H_INCLUDED

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <iostream>
#include <string>

#endif 

class GlWindow {
    public:
        GlWindow(std::string title, int width, int height, bool fullscreen);
        ~GlWindow();
        SDL_Window* getWindow();
        SDL_GLContext getContext();
    private:
        SDL_Window* window;
        SDL_GLContext context;
};

void printGlError();
