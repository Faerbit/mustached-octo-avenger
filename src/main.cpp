#include <main.h>


int main(int argc, char* argv[]) {

    Window window("Octo Avenger", 1024, 786, false);
    Context context(window.getWindow());

    float vertices[] = {
        //Position    Texcoords
        -0.5f,  0.8f, 0.0f, 0.0f,  // Top-left
         0.5f,  0.8f, 1.0f, 0.0f,  // Top-right
         0.5f,  0.0f, 1.0f, 1.0f,  // Bottom-right
        -0.5f,  0.0f, 0.0f, 1.0f,  // Bottom-left
            //Mirror
        -0.5f,  0.0f, 0.0f, 1.0f,  // Top-left
         0.5f,  0.0f, 1.0f, 1.0f,  // Top-right
         0.5f, -0.8f, 1.0f, 0.0f,  // Bottom-right
        -0.5f, -0.8f, 0.0f, 0.0f  // Bottom-left
    };

    GLuint vertexArrayObject;
    
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint elements[] = {
        0, 1, 2,
        0, 3, 2,
        4, 5, 6,
        4, 7, 6
    };

    GLuint elementBufferObject;
    glGenBuffers(1, &elementBufferObject);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);


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
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);

    GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));

    glm::mat4 view = glm::lookAt(
        glm::vec3(1.2f, 1.2f, 1.2f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f)
    );
    
    GLint uniView = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 projection = glm::perspective(45.0f, 1024.0f/786.0f, 1.0f, 10.f);
    GLint uniProjection = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(uniProjection, 1, GL_FALSE, glm::value_ptr(projection));

    GLuint textures[2];
    glGenTextures(2, textures);

    int width, height;
    unsigned char* image;

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    image = SOIL_load_image("assets/textures/sample.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
    glUniform1i(glGetUniformLocation(shaderProgram, "texKitten"), 0);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    printGlError();

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    image = SOIL_load_image("assets/textures/sample2.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
    glUniform1i(glGetUniformLocation(shaderProgram, "texPuppy"), 1);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    auto timer = glGetUniformLocation(shaderProgram, "time");
    GLint uniModel = glGetUniformLocation(shaderProgram, "model");
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    printGlError();

    SDL_Event windowEvent;
    while(true) {
        glClear(GL_COLOR_BUFFER_BIT);

        float time = (float)clock()/(float)CLOCKS_PER_SEC;

        glm::mat4 trans;
        trans = glm::rotate(trans, time*10.0f, glm::vec3(0.0f, 0.0f, 1.0f));

        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(trans));

        glUniform1f(timer, (sin(time * 50.0f)+1.0f)/2.0f);

        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
        if (SDL_PollEvent(&windowEvent)) {
            if (windowEvent.type == SDL_QUIT ||
                (windowEvent.type == SDL_KEYUP &&
                windowEvent.key.keysym.sym == SDLK_ESCAPE))
                    break;
        }
        SDL_GL_SwapWindow(window.getWindow());
    }
    glDeleteProgram(shaderProgram);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArrays(1, &vertexArrayObject);
    return 0;
}
