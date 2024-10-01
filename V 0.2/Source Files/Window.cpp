#include "Window.hpp"
#include "blocks.h"
#include "generation.h"
#include <math.h>
#include <thread>

void Window::setup() {
    srand(time(NULL));

    glfwSetInputMode(screen, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);

    glUseProgram(shader->shaderProgram);

    texture.updateTexture();

    camera.projection = glm::perspective(glm::radians(90.0f), (float)width / (float)height, 0.1f, 1000.0f);

    // Clear the color buffer
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
void Window::input() {
    camera.cameraRight = glm::normalize(glm::cross(camera.upDirection, camera.cameraDirection));

    if (glfwGetKey(screen, GLFW_KEY_W) == GLFW_PRESS)
        camera.cameraPos += 0.5f * camera.cameraDirection;
    if (glfwGetKey(screen, GLFW_KEY_S) == GLFW_PRESS)
        camera.cameraPos -= 0.5f * camera.cameraDirection;
    if (glfwGetKey(screen, GLFW_KEY_A) == GLFW_PRESS)
        camera.cameraPos += 0.5f * camera.cameraRight;
    if (glfwGetKey(screen, GLFW_KEY_D) == GLFW_PRESS)
        camera.cameraPos -= 0.5f * camera.cameraRight;

    camera.mouse_callback(screen);
}

void Window::update() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::vec2 chunkOnPlayer = { floor(camera.cameraPos.x / 16),  floor(camera.cameraPos.z / 16) };

    for (auto chunk : game.renderer)
    if (chunk.second->ready) {
        chunk.second->cooked = true;
        chunk.second->ready = false;
        chunk.second->init();
        chunk.second->loadChunkVertices();
    }

    for (auto chunk = game.renderer.begin(); chunk != game.renderer.end(); chunk++)
    if (chunk->first.x > chunkOnPlayer.x + RENDER_VAR || chunk->first.x < chunkOnPlayer.x - RENDER_VAR
        || chunk->first.y > chunkOnPlayer.y + RENDER_VAR || chunk->first.y < chunkOnPlayer.y - RENDER_VAR) {
        chunk->second->unloadChunkVertices();
        delete chunk->second;
        chunk = game.renderer.erase(chunk);
        break;
    }

    camera.updateCamera(shader);
}
void Window::render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, texture.textureID);

    for (auto chunk : game.renderer) {
        if (chunk.second->cooked && camera.isChunkVisible(chunk.first))
            chunk.second->drawChunkVertices();
    }

    glfwSwapBuffers(screen);
    glfwPollEvents();
}
void Window::clean() {
    glDeleteShader(shader->vertexShader);
    glDeleteShader(shader->fragmentShader);
}
