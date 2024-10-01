#include "Window.hpp"
#include "generation.h"
#include <iostream>

std::thread generation;

int main() {
    Window w("m1necwaft",1920,1080);

    w.setup();

    generation = std::thread(generateWorld);

    while (!glfwWindowShouldClose(w.screen))
    {
        w.input();
        w.update();
        w.render();
    }

    generation.join();

    w.clean();
}
