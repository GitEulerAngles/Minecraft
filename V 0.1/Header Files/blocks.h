#include "shaders.h"

enum blockType {
    grass
};
struct square {
    glm::vec3 triangles[6], position;
};
struct block {
    void drawBlock(std::vector<GLfloat>* vertices);
    void setSquares();
    void orderBlockFaces(glm::vec3 cameraPos);
    square squares[6];
    glm::vec3 position = {0,0,0};
    blockType type;
};

