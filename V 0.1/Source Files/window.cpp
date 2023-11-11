#include "window.hpp"
#include "blocks.h"
#include <math.h>

GLuint VBO, VAO, EBO;
camera c; block b[2];

std::vector<GLfloat> vertices;


void window::setup() {
    glfwSetInputMode(screen, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    b[0].position = { 0,0,0 };
    b[1].position = { 1,1,1 };

    for (int i = 0; i < 2; i++)
        b[i].setSquares();

    c.projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    //std::vector<GLfloat> square;
    //float mapSin[501][501];
    //for (int x = 0; x < 501; x++)
    //for (int y = 0; y < 501; y++) {
    //    mapSin[x][y] = sin(y*.1)+cos(x*.1);
    //}
    //
    //for (int x = 0; x < 500; x++)
    //for (int y = 0; y < 500; y++) {
    //    square = {
    //        // Positions         // Colors
    //        ( 0.5f + x)/20.0f, ( 0.5f + y)/20.0f, 0.0f + mapSin[x+1][y+1], 0.0f, 0.0f, 1.0f,   // Top Left
    //        (-0.5f + x)/20.0f, (-0.5f + y)/20.0f, 0.0f + mapSin[x][y],     0.0f, 0.0f, 0.5f,   // Bottom Right
    //        ( 0.5f + x)/20.0f, (-0.5f + y)/20.0f, 0.0f + mapSin[x + 1][y], 0.0f, 0.0f, 0.0f,   // Bottom Left 
    //        // Positions         // Colors 
    //        ( 0.5f + x)/20.0f, ( 0.5f + y)/20.0f, 0.0f + mapSin[x+1][y+1], 0.0f, 0.0f, 1.0f,   // Top Left
    //        (-0.5f + x)/20.0f, (-0.5f + y)/20.0f, 0.0f + mapSin[x][y],     0.0f, 0.0f, 0.5f,   // Bottom Right
    //        (-0.5f + x)/20.0f, ( 0.5f + y)/20.0f, 0.0f + mapSin[x][y+1],   0.0f, 0.0f, 0.0f    // Top Right
    //    };
    //    for (int i = 0; i < 36; i++) {
    //        vertices.push_back(square[i]);
    //    }
    //}

    // Clear the color buffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
void window::input() {
    c.cameraRight = glm::normalize(glm::cross(c.upDirection, c.cameraDirection));

    if (glfwGetKey(screen, GLFW_KEY_W) == GLFW_PRESS)
        c.cameraPos += 0.2f * c.cameraDirection;
    if (glfwGetKey(screen, GLFW_KEY_S) == GLFW_PRESS)
        c.cameraPos -= 0.2f * c.cameraDirection;
    if (glfwGetKey(screen, GLFW_KEY_A) == GLFW_PRESS)
        c.cameraPos += 0.2f * c.cameraRight;
    if (glfwGetKey(screen, GLFW_KEY_D) == GLFW_PRESS)
        c.cameraPos -= 0.2f * c.cameraRight;

    c.mouse_callback(screen);
}
void window::update() {
    glUseProgram(shader->shaderProgram);

    c.updateCamera(shader);

    for (int i = 0; i < 2; i++) {
        b[i].orderBlockFaces(c.cameraPos);
        b[i].drawBlock(&vertices);
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cout << "OpenGL error: " << err << std::endl;
    }
}
void window::render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    glBindVertexArray(0);
    glfwSwapBuffers(screen);
    glfwPollEvents();
}
void window::clean() {
    glDeleteShader(shader->vertexShader);
    glDeleteShader(shader->fragmentShader);
    glDeleteBuffers(vertices.size(), &VBO);
    glDeleteBuffers(vertices.size(), &VAO);
    glDeleteBuffers(vertices.size(), &EBO);
}
