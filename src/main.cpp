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

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    SDL_Window* window = SDL_CreateWindow("Mustached Octo Avenger", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 786, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);

    glewExperimental = GL_TRUE;
    checkGlError();
    glewInit();
    std::cout << "glewInit GlError:\n";
    checkGlError();

    float vertices[] = {
         0.0f,  0.5f, 1.0f, 0.0f, 0.0f, // Vertex 1: Red
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Vertex 2: Green
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f  // Vertex 3: Blue
    };

    GLuint vertexArrayObject;
    
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    Shader vertexShader(GL_VERTEX_SHADER, "shaders/simple.vert");
    Shader fragmentShader(GL_FRAGMENT_SHADER, "shaders/simple.frag");

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader.getReference());
    glAttachShader(shaderProgram, fragmentShader.getReference());

    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));
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
    glDeleteProgram(shaderProgram);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArrays(1, &vertexArrayObject);
    SDL_GL_DeleteContext(context);
    SDL_Quit();
    return 0;
}
