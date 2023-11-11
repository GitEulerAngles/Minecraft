#ifndef SHADERS
#define SHADERS

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct shaders {
    GLuint vertexShader, fragmentShader, shaderProgram;
    std::string vertexShaderSource, fragmentShaderSource;

    void defineShader(std::string *source, std::string path);
    void loadShaderProgram();
};
class camera {
public:
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 upDirection = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraDirection, cameraRight, cameraUp;
    glm::mat4 model, view, projection;
    void mouse_callback(GLFWwindow* window);
    void updateCamera(shaders* shader);
private:
    float lastX = 800.0f / 2.0;
    float lastY = 600.0f / 2.0;
    float yaw = 0, pitch = 0;
};

#endif SHADERS
