#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <SOIL.h>

#include <window.h>
#include <context.h>
#include <shader.h>

#define  GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <chrono>
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;

#endif

int main(int argc, char* argv[]);
