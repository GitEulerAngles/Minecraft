#include "blocks.h"
void block::setSquares() {
    squares[0].position = glm::vec3(position.x, position.y + 0.5f, position.z);
    squares[1].position = glm::vec3(position.x, position.y - 0.5f, position.z);
    squares[2].position = glm::vec3(position.x + 0.5f, position.y, position.z);
    squares[3].position = glm::vec3(position.x - 0.5f, position.y, position.z);
    squares[4].position = glm::vec3(position.x, position.y, position.z + 0.5f);
    squares[5].position = glm::vec3(position.x, position.y, position.z - 0.5f);

    squares[0].triangles[0] = { squares[0].position.x + 0.5f, squares[0].position.y, squares[0].position.z - 0.5f };
    squares[0].triangles[1] = { squares[0].position.x + 0.5f, squares[0].position.y, squares[0].position.z + 0.5f };
    squares[0].triangles[2] = { squares[0].position.x - 0.5f, squares[0].position.y, squares[0].position.z + 0.5f };
    squares[0].triangles[3] = { squares[0].position.x + 0.5f, squares[0].position.y, squares[0].position.z - 0.5f };
    squares[0].triangles[4] = { squares[0].position.x - 0.5f, squares[0].position.y, squares[0].position.z - 0.5f };
    squares[0].triangles[5] = { squares[0].position.x - 0.5f, squares[0].position.y, squares[0].position.z + 0.5f };
    squares[1].triangles[0] = { squares[1].position.x + 0.5f, squares[1].position.y, squares[1].position.z - 0.5f };
    squares[1].triangles[1] = { squares[1].position.x + 0.5f, squares[1].position.y, squares[1].position.z + 0.5f };
    squares[1].triangles[2] = { squares[1].position.x - 0.5f, squares[1].position.y, squares[1].position.z + 0.5f };
    squares[1].triangles[3] = { squares[1].position.x + 0.5f, squares[1].position.y, squares[1].position.z - 0.5f };
    squares[1].triangles[4] = { squares[1].position.x - 0.5f, squares[1].position.y, squares[1].position.z - 0.5f };
    squares[1].triangles[5] = { squares[1].position.x - 0.5f, squares[1].position.y, squares[1].position.z + 0.5f };
    squares[2].triangles[0] = { squares[2].position.x, squares[2].position.y + 0.5f, squares[2].position.z + 0.5f };
    squares[2].triangles[1] = { squares[2].position.x, squares[2].position.y - 0.5f, squares[2].position.z + 0.5f };
    squares[2].triangles[2] = { squares[2].position.x, squares[2].position.y - 0.5f, squares[2].position.z - 0.5f };
    squares[2].triangles[3] = { squares[2].position.x, squares[2].position.y + 0.5f, squares[2].position.z + 0.5f };
    squares[2].triangles[4] = { squares[2].position.x, squares[2].position.y + 0.5f, squares[2].position.z - 0.5f };
    squares[2].triangles[5] = { squares[2].position.x, squares[2].position.y - 0.5f, squares[2].position.z - 0.5f };
    squares[3].triangles[0] = { squares[3].position.x, squares[3].position.y + 0.5f, squares[3].position.z + 0.5f };
    squares[3].triangles[1] = { squares[3].position.x, squares[3].position.y - 0.5f, squares[3].position.z + 0.5f };
    squares[3].triangles[2] = { squares[3].position.x, squares[3].position.y - 0.5f, squares[3].position.z - 0.5f };
    squares[3].triangles[3] = { squares[3].position.x, squares[3].position.y + 0.5f, squares[3].position.z + 0.5f };
    squares[3].triangles[4] = { squares[3].position.x, squares[3].position.y + 0.5f, squares[3].position.z - 0.5f };
    squares[3].triangles[5] = { squares[3].position.x, squares[3].position.y - 0.5f, squares[3].position.z - 0.5f };
    squares[4].triangles[0] = { squares[4].position.x - 0.5f, squares[4].position.y + 0.5f, squares[4].position.z };
    squares[4].triangles[1] = { squares[4].position.x + 0.5f, squares[4].position.y - 0.5f, squares[4].position.z };
    squares[4].triangles[2] = { squares[4].position.x - 0.5f, squares[4].position.y - 0.5f, squares[4].position.z };
    squares[4].triangles[3] = { squares[4].position.x - 0.5f, squares[4].position.y + 0.5f, squares[4].position.z };
    squares[4].triangles[4] = { squares[4].position.x + 0.5f, squares[4].position.y - 0.5f, squares[4].position.z };
    squares[4].triangles[5] = { squares[4].position.x + 0.5f, squares[4].position.y + 0.5f, squares[4].position.z };
    squares[5].triangles[0] = { squares[5].position.x - 0.5f, squares[5].position.y + 0.5f, squares[5].position.z };
    squares[5].triangles[1] = { squares[5].position.x + 0.5f, squares[5].position.y - 0.5f, squares[5].position.z };
    squares[5].triangles[2] = { squares[5].position.x - 0.5f, squares[5].position.y - 0.5f, squares[5].position.z };
    squares[5].triangles[3] = { squares[5].position.x - 0.5f, squares[5].position.y + 0.5f, squares[5].position.z };
    squares[5].triangles[4] = { squares[5].position.x + 0.5f, squares[5].position.y - 0.5f, squares[5].position.z };
    squares[5].triangles[5] = { squares[5].position.x + 0.5f, squares[5].position.y + 0.5f, squares[5].position.z };
}
void block::orderBlockFaces(glm::vec3 cameraPos) {
    float distances[6];
    for (int i = 0; i < 6; i++)
        distances[i] = glm::distance(cameraPos, squares[i].position);

    for (int i = 5; i >= 1; i--)
    for (int j = 0; j < i; j++) {
        if (distances[j] < distances[j + 1]) {
            // Swap lower data set and higher data set
            float temp_dist = distances[j + 1];
            distances[j + 1] = distances[j];
            distances[j] = temp_dist;
            // Swap squares vector
            square temp_square = squares[j + 1];
            squares[j + 1] = squares[j];
            squares[j] = temp_square;
        }
    }
}

void block::drawBlock(std::vector<GLfloat>* vertices) {
    std::vector<GLfloat> block;

    block = {
        // Positions         // Colors
        // Square 1
        squares[0].triangles[0].x,squares[0].triangles[0].y,squares[0].triangles[0].z, 0.0f, 0.0f, 1.0f,
        squares[0].triangles[1].x,squares[0].triangles[1].y,squares[0].triangles[1].z, 0.0f, 1.0f, 1.0f,
        squares[0].triangles[2].x,squares[0].triangles[2].y,squares[0].triangles[2].z, 0.0f, 0.0f, 1.0f,
        squares[0].triangles[3].x,squares[0].triangles[3].y,squares[0].triangles[3].z, 0.0f, 0.0f, 1.0f,
        squares[0].triangles[4].x,squares[0].triangles[4].y,squares[0].triangles[4].z, 0.0f, 1.0f, 1.0f,
        squares[0].triangles[5].x,squares[0].triangles[5].y,squares[0].triangles[5].z, 0.0f, 0.0f, 1.0f,
        // Square 2
        squares[1].triangles[0].x,squares[1].triangles[0].y,squares[1].triangles[0].z, 0.0f, 0.0f, 1.0f,
        squares[1].triangles[1].x,squares[1].triangles[1].y,squares[1].triangles[1].z, 0.0f, 1.0f, 1.0f,
        squares[1].triangles[2].x,squares[1].triangles[2].y,squares[1].triangles[2].z, 0.0f, 0.0f, 1.0f,
        squares[1].triangles[3].x,squares[1].triangles[3].y,squares[1].triangles[3].z, 0.0f, 0.0f, 1.0f,
        squares[1].triangles[4].x,squares[1].triangles[4].y,squares[1].triangles[4].z, 0.0f, 1.0f, 1.0f,
        squares[1].triangles[5].x,squares[1].triangles[5].y,squares[1].triangles[5].z, 0.0f, 0.0f, 1.0f,
        // Square 3
        squares[2].triangles[0].x,squares[2].triangles[0].y,squares[2].triangles[0].z, 0.0f, 0.0f, 1.0f,
        squares[2].triangles[1].x,squares[2].triangles[1].y,squares[2].triangles[1].z, 0.0f, 1.0f, 1.0f,
        squares[2].triangles[2].x,squares[2].triangles[2].y,squares[2].triangles[2].z, 0.0f, 0.0f, 1.0f,
        squares[2].triangles[3].x,squares[2].triangles[3].y,squares[2].triangles[3].z, 0.0f, 0.0f, 1.0f,
        squares[2].triangles[4].x,squares[2].triangles[4].y,squares[2].triangles[4].z, 0.0f, 1.0f, 1.0f,
        squares[2].triangles[5].x,squares[2].triangles[5].y,squares[2].triangles[5].z, 0.0f, 0.0f, 1.0f,
        // Square 4
        squares[3].triangles[0].x,squares[3].triangles[0].y,squares[3].triangles[0].z, 0.0f, 0.0f, 1.0f,
        squares[3].triangles[1].x,squares[3].triangles[1].y,squares[3].triangles[1].z, 0.0f, 1.0f, 1.0f,
        squares[3].triangles[2].x,squares[3].triangles[2].y,squares[3].triangles[2].z, 0.0f, 0.0f, 1.0f,
        squares[3].triangles[3].x,squares[3].triangles[3].y,squares[3].triangles[3].z, 0.0f, 0.0f, 1.0f,
        squares[3].triangles[4].x,squares[3].triangles[4].y,squares[3].triangles[4].z, 0.0f, 1.0f, 1.0f,
        squares[3].triangles[5].x,squares[3].triangles[5].y,squares[3].triangles[5].z, 0.0f, 0.0f, 1.0f,
        // Square 5
        squares[4].triangles[0].x,squares[4].triangles[0].y,squares[4].triangles[0].z, 0.0f, 0.0f, 1.0f,
        squares[4].triangles[1].x,squares[4].triangles[1].y,squares[4].triangles[1].z, 0.0f, 1.0f, 1.0f,
        squares[4].triangles[2].x,squares[4].triangles[2].y,squares[4].triangles[2].z, 0.0f, 0.0f, 1.0f,
        squares[4].triangles[3].x,squares[4].triangles[3].y,squares[4].triangles[3].z, 0.0f, 0.0f, 1.0f,
        squares[4].triangles[4].x,squares[4].triangles[4].y,squares[4].triangles[4].z, 0.0f, 1.0f, 1.0f,
        squares[4].triangles[5].x,squares[4].triangles[5].y,squares[4].triangles[5].z, 0.0f, 0.0f, 1.0f,
        // Square 6
        squares[5].triangles[0].x,squares[5].triangles[0].y,squares[5].triangles[0].z, 0.0f, 0.0f, 1.0f,
        squares[5].triangles[1].x,squares[5].triangles[1].y,squares[5].triangles[1].z, 0.0f, 1.0f, 1.0f,
        squares[5].triangles[2].x,squares[5].triangles[2].y,squares[5].triangles[2].z, 0.0f, 0.0f, 1.0f,
        squares[5].triangles[3].x,squares[5].triangles[3].y,squares[5].triangles[3].z, 0.0f, 0.0f, 1.0f,
        squares[5].triangles[4].x,squares[5].triangles[4].y,squares[5].triangles[4].z, 0.0f, 1.0f, 1.0f,
        squares[5].triangles[5].x,squares[5].triangles[5].y,squares[5].triangles[5].z, 0.0f, 0.0f, 1.0f,
    };
    for (int i = 0; i < block.size(); i++)
        vertices->push_back(block[i]);
}
