#include "window.hpp"
#include <iostream>

int main() {
    window w("m1necwaft",1920,1080);

    w.setup();

    while (!glfwWindowShouldClose(w.screen))
    {
        w.input();
        w.update();
        w.render();
    }

    w.clean();
}
