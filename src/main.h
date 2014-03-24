#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SOIL.h>

#include <iostream>

#include <shader.h>

#endif

void checkGlError();
void load_triangle();
int main(int argc, char* argv[]);
