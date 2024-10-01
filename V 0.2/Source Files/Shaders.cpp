#include "Shaders.h"
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION    
#include "stb_image.h"

void getOpenGLError(const std::string& prompt) {
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << prompt << error << std::endl;
    }
}
void Texture::updateTexture() {
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    unsigned char* data = stbi_load("textureAtlas.png", &width, &height, &nrChannels, 0);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    else {
        std::cout << "Failed to load textureID." << std::endl;
    }

    stbi_image_free(data);
}
void Shaders::defineShader(std::string* source, std::string path) {
    std::ifstream file(path);
    std::string line, shader;
    while (std::getline(file, line)) {
        shader += line + '\n';
    }
    *source = shader;
}
void Shaders::loadShaderProgram() {
    // Create vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vShaderCode = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);
    
    // Check for linking errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    }

    // Create fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fShaderCode = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);

    // Check for linking errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    }

    // Create shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        fprintf(stderr, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s", infoLog);
    }
}
void Camera::mouse_callback(GLFWwindow* window) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraDirection = glm::normalize(front);
}
void Camera::updateCamera(Shaders *shader) {
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

    view = glm::lookAt(cameraPos, cameraPos + cameraDirection, upDirection);

    glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
}
bool Camera::isChunkVisible(glm::vec2 chunkPos) {
    chunkPos *= glm::vec2(16);

    glm::vec3 newCameraPos = cameraPos - 48.0f * cameraDirection;

    view = glm::lookAt(newCameraPos, newCameraPos + cameraDirection, upDirection);

    glm::vec4 chunkPosViewSpace = view * glm::vec4(chunkPos.x + 8, cameraPos.y * cameraDirection.y, chunkPos.y + 8, 1.0);

    glm::vec4 chunkPosClipSpace = projection * chunkPosViewSpace;

    glm::vec3 chunkPosNDC = glm::vec3(chunkPosClipSpace) / chunkPosClipSpace.w;

    return (
        chunkPosNDC.x >= -1.0 && chunkPosNDC.x <= 1.0 &&
        chunkPosNDC.y >= -1.0 && chunkPosNDC.y <= 1.0 &&
        chunkPosNDC.z >= -1.0 && chunkPosNDC.z <= 1.0
        );
}
