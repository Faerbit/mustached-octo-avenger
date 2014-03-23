#include <main.h>

void checkGlError() {
    GLenum glError = glGetError();

    switch (glError) {
        case GL_NO_ERROR:
            std::cout << "GL_NO_ERROR\n";
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

void load_triangle() {
    float vertices[] = {
         0.0f,  0.5f,
         0.5f, -0.5f,
        -0.5f, -0.5f
    };

    GLuint vertexArrayObject;
    checkGlError();
    glGenVertexArrays(1, &vertexArrayObject);
    checkGlError();
    glBindVertexArray(vertexArrayObject);
    checkGlError();

    GLuint vertexBuffer;
    checkGlError();
    glGenBuffers(1, &vertexBuffer);
    checkGlError();
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    checkGlError();
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    checkGlError();

    Shader vertexShader(GL_VERTEX_SHADER, "shaders/simple.vert");
    checkGlError();
    Shader fragmentShader(GL_FRAGMENT_SHADER, "shaders/simple.frag");
    checkGlError();

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader.getReference());
    glAttachShader(shaderProgram, fragmentShader.getReference());
    checkGlError();

    glBindFragDataLocation(shaderProgram, 0, "outColor");
    checkGlError();

    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    checkGlError();

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);
    checkGlError();

}


int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    SDL_Window* window = SDL_CreateWindow("Mustached Octo Avenger", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 786, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    checkGlError();

    glewExperimental = GL_TRUE;
    checkGlError();
    glewInit();
    std::cout << "glewInit GlError:\n";
    checkGlError();

    load_triangle();
    checkGlError();

    SDL_Event windowEvent;
    while(true) {
        glDrawArrays(GL_TRIANGLES, 0, 3);
        if (SDL_PollEvent(&windowEvent)) {
            if (windowEvent.type == SDL_QUIT ||
                (windowEvent.type == SDL_KEYUP &&
                windowEvent.key.keysym.sym == SDLK_ESCAPE))
                    break;
        }
        SDL_GL_SwapWindow(window);
    }
    SDL_GL_DeleteContext(context);
    SDL_Quit();
    return 0;
}
