#ifndef WINDOW
#define WINDOW

#include "shaders.h"

class window {
public:
    GLFWwindow* screen;
    shaders* shader = new shaders;
    bool running = true;
    int width, height;

    window(std::string name, int w, int h) {
        if (!glfwInit()) {
            fprintf(stderr, "Failed to initialize GLFW\n");
        }
        screen = glfwCreateWindow(w, h, name.c_str(), NULL, NULL);
        width = w; height = h;

        if (screen == NULL) {
            fprintf(stderr, "Failed to open GLFW window.\n");
            glfwTerminate();
        }
        glfwMakeContextCurrent(screen);
        glewExperimental = true;
        if (glewInit() != GLEW_OK) {
            fprintf(stderr, "Failed to initialize GLEW\n");
        }

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwSetInputMode(screen, GLFW_STICKY_KEYS, GL_TRUE);

        shader->defineShader(&shader->vertexShaderSource, "vertexShader.txt");
        shader->defineShader(&shader->fragmentShaderSource, "fragementShader.txt");
        shader->loadShaderProgram();
    }

    void input();
    void update();
    void render();
    void setup();
    void clean();
};

#endif // !WINDOW
