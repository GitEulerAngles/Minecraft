#include "blocks.h"
#include "perlin.hpp"

glm::vec2 getTextureCoords(int width, int height, bool x, bool y, int face_type) {
    float x_b = (face_type % width) * 16;
    float y_b = floor(face_type / width) * 16;

    x_b += (int)x * 16;
    y_b += (int)y * 16;

    return glm::vec2(x_b / (float)(width*16), y_b / (float)(height*16));
}
void GameMap::setChunk(int chunk_x, int chunk_y) {
    static siv::PerlinNoise p(std::rand());
    data[glm::vec2(chunk_x, chunk_y)] = new Chunk;
    Chunk* current_chunk = data[glm::vec2(chunk_x, chunk_y)];
    for (int x = 0; x < 16; x++)
    for (int z = 0; z < 16; z++)
    for (int y = 0; y < 64; y++) {
        double c = p.noise2D_0_1(
            static_cast<double>((x + 16 * chunk_x) / 50.0),
            static_cast<double>((z + 16 * chunk_y) / 50.0)
        );
        if (y < c * 50.0f && y < 20) {
            current_chunk->chunkData[x][y][z].type = BlockType::sand;
        }
        else if (y < c * 50.0f) {
            current_chunk->chunkData[x][y][z].type = BlockType::grass;
            if (y != 0)
                current_chunk->chunkData[x][y - 1][z].type = BlockType::dirt;
        }
    }
}
void GameMap::setChunkRenderer(int chunk_x, int chunk_y) {
    if (data.find(glm::vec2(chunk_x, chunk_y)) == data.end())
        return;

    renderer[glm::vec2(chunk_x, chunk_y)] = new ChunkRenderer;
    ChunkRenderer* current_chunk = renderer[glm::vec2(chunk_x, chunk_y)];
    current_chunk->pChunkData = data[glm::vec2(chunk_x, chunk_y)];
    for (int x = 0; x < 16; x++)
    for (int z = 0; z < 16; z++)
    for (int y = 0; y < 64; y++) {
        current_chunk->chunkData[x][y][z].type = current_chunk->pChunkData->chunkData[x][y][z].type;
        current_chunk->chunkData[x][y][z].position = { x + (16 * chunk_x),y,z + (16 * chunk_y) };
    }
}
void GameMap::setActiveSides(int chunk_x, int chunk_y) {
    ChunkRenderer* current_chunk = renderer[glm::vec2(chunk_x, chunk_y)];

    // For blocks in middle.
    for (int x = 1; x < 15; x++)
    for (int z = 1; z < 15; z++)
    for (int y = 0; y < 64; y++) {
        for (int i = 0; i < 6; ++i) {
            current_chunk->chunkData[x][y][z].sidesActive[i] = true;
        }

        if (y + 1 < 64 && current_chunk->chunkData[x][y + 1][z].type != BlockType::air) { // Bottom face
            current_chunk->chunkData[x][y][z].sidesActive[0] = false;
        }
        if (y - 1 >= 0 && current_chunk->chunkData[x][y - 1][z].type != BlockType::air) { // Top face
            current_chunk->chunkData[x][y][z].sidesActive[1] = false;
        }

        if (x + 1 < 16 && current_chunk->chunkData[x + 1][y][z].type != BlockType::air) { // Right
            current_chunk->chunkData[x][y][z].sidesActive[2] = false;
        }
        if (x - 1 >= 0 && current_chunk->chunkData[x - 1][y][z].type != BlockType::air) { // Left
            current_chunk->chunkData[x][y][z].sidesActive[3] = false;
        }

        if (z + 1 < 16 && current_chunk->chunkData[x][y][z + 1].type != BlockType::air) { // Front
            current_chunk->chunkData[x][y][z].sidesActive[4] = false;
        }
        if (z - 1 >= 0 && current_chunk->chunkData[x][y][z - 1].type != BlockType::air) { // Back
            current_chunk->chunkData[x][y][z].sidesActive[5] = false;
        }

    }

    // For blocks near edges
    for (int axis = 0; axis < 2; axis++)
    for (int x = 0; x < 16; x += axis ? 1 : 15)
    for (int z = 0; z < 16; z += axis ? 15 : 1)
    for (int y = 0; y < 64; y++) {
        for (int i = 0; i < 6; i++)
            current_chunk->chunkData[x][y][z].sidesActive[i] = true;

        if (y + 1 < 64 && current_chunk->chunkData[x][y + 1][z].type != BlockType::air) // Bottom face
                current_chunk->chunkData[x][y][z].sidesActive[0] = false;

        if (y - 1 >= 0 && current_chunk->chunkData[x][y - 1][z].type != BlockType::air) // Top face
            current_chunk->chunkData[x][y][z].sidesActive[1] = false;

        if ((x == 15 && data[glm::vec2(chunk_x + 1, chunk_y)]->chunkData[0][y][z].type != BlockType::air) ||
            (x != 15 && current_chunk->chunkData[x + 1][y][z].type != BlockType::air)) {
            current_chunk->chunkData[x][y][z].sidesActive[2] = false;
        }

        if ((x == 0 && data[glm::vec2(chunk_x - 1, chunk_y)]->chunkData[15][y][z].type != BlockType::air) ||
            (x != 0 && current_chunk->chunkData[x - 1][y][z].type != BlockType::air)) {
            current_chunk->chunkData[x][y][z].sidesActive[3] = false;
        }

        if ((z == 15 && data[glm::vec2(chunk_x, chunk_y + 1)]->chunkData[x][y][0].type != BlockType::air) || 
            (z != 15 && current_chunk->chunkData[x][y][z + 1].type != BlockType::air)) {
            current_chunk->chunkData[x][y][z].sidesActive[4] = false;
        }

        if ((z == 0 && data[glm::vec2(chunk_x, chunk_y - 1)]->chunkData[x][y][15].type != BlockType::air) || 
            (z != 0 && current_chunk->chunkData[x][y][z - 1].type != BlockType::air)) {
            current_chunk->chunkData[x][y][z].sidesActive[5] = false;
        }
    }

    current_chunk->ready = true;
}
void BlockRenderer::getSquareTextures(int width, int height, std::array<Square, 6>& squares) {
    int block_type = (int)type;

    int coords[6];
    for (int i = 0; i < 6; i++)
        coords[i] = BlockCoords[block_type][i];

    const bool blockEdges[4][2] = {
        {0,1}, {1,0}, {0,0}, {1,1}
    };

    for (int j = 0; j < 6; j++)
    for (int i = 0; i < 4; i++) {
        squares.at(j).texturePos[i] = getTextureCoords(width / 16, height / 16, blockEdges[i][0], blockEdges[i][1], coords[j]);
    }
}
void BlockRenderer::getSquareVertices(std::array<Square, 6>& squares) {
    glm::vec3 v1 = glm::vec3(position.x, position.y + 0.5f, position.z);
    glm::vec3 v2 = glm::vec3(position.x, position.y - 0.5f, position.z);
    glm::vec3 v3 = glm::vec3(position.x + 0.5f, position.y, position.z);
    glm::vec3 v4 = glm::vec3(position.x - 0.5f, position.y, position.z);
    glm::vec3 v5 = glm::vec3(position.x, position.y, position.z + 0.5f);
    glm::vec3 v6 = glm::vec3(position.x, position.y, position.z - 0.5f);

    squares[0].triangles[0] = { v1.x + 0.5f, v1.y, v1.z - 0.5f };
    squares[0].triangles[1] = { v1.x - 0.5f, v1.y, v1.z + 0.5f };
    squares[0].triangles[2] = { v1.x + 0.5f, v1.y, v1.z + 0.5f };
    squares[0].triangles[3] = { v1.x - 0.5f, v1.y, v1.z - 0.5f };
    squares[1].triangles[0] = { v2.x + 0.5f, v2.y, v2.z - 0.5f };
    squares[1].triangles[1] = { v2.x - 0.5f, v2.y, v2.z + 0.5f };
    squares[1].triangles[2] = { v2.x + 0.5f, v2.y, v2.z + 0.5f };
    squares[1].triangles[3] = { v2.x - 0.5f, v2.y, v2.z - 0.5f };
    squares[2].triangles[0] = { v3.x, v3.y - 0.5f, v3.z + 0.5f };
    squares[2].triangles[1] = { v3.x, v3.y + 0.5f, v3.z - 0.5f };
    squares[2].triangles[2] = { v3.x, v3.y + 0.5f, v3.z + 0.5f };
    squares[2].triangles[3] = { v3.x, v3.y - 0.5f, v3.z - 0.5f };
    squares[3].triangles[0] = { v4.x, v4.y - 0.5f, v4.z - 0.5f };
    squares[3].triangles[1] = { v4.x, v4.y + 0.5f, v4.z + 0.5f };
    squares[3].triangles[2] = { v4.x, v4.y + 0.5f, v4.z - 0.5f };
    squares[3].triangles[3] = { v4.x, v4.y - 0.5f, v4.z + 0.5f };
    squares[4].triangles[0] = { v5.x - 0.5f, v5.y - 0.5f, v5.z };
    squares[4].triangles[1] = { v5.x + 0.5f, v5.y + 0.5f, v5.z };
    squares[4].triangles[2] = { v5.x - 0.5f, v5.y + 0.5f, v5.z };
    squares[4].triangles[3] = { v5.x + 0.5f, v5.y - 0.5f, v5.z };
    squares[5].triangles[0] = { v6.x + 0.5f, v6.y - 0.5f, v6.z };
    squares[5].triangles[1] = { v6.x - 0.5f, v6.y + 0.5f, v6.z };
    squares[5].triangles[2] = { v6.x + 0.5f, v6.y + 0.5f, v6.z };
    squares[5].triangles[3] = { v6.x - 0.5f, v6.y - 0.5f, v6.z };
}
void ChunkRenderer::loadChunkVertices() {
    indices.clear();
    vertices.clear();
    for (int x = 0; x < 16; x++)
    for (int z = 0; z < 16; z++)
    for (int y = 0; y < 64; y++) {
        std::array<Square, 6> squares;
        chunkData[x][y][z].getSquareTextures(64, 16, squares);
        chunkData[x][y][z].getSquareVertices(squares);
        for (int i = 0; i < 6; i++) {
            if (chunkData[x][y][z].sidesActive[i] && pChunkData->chunkData[x][y][z].type != BlockType::air) {
                // Division by 20??? I don't know why this works.
                int count = floor(vertices.size() / 20);
                indices.insert(indices.end(), { (unsigned int)(count * 4), 
                    (unsigned int)(count * 4 + 1), 
                    (unsigned int)(count * 4 + 2), 
                    (unsigned int)(count * 4), 
                    (unsigned int)(count * 4 + 1), 
                    (unsigned int)(count * 4 + 3) });
                for (int j = 0; j < 4; j++) {
                    vertices.push_back(squares[i].triangles[j].x);
                    vertices.push_back(squares[i].triangles[j].y);
                    vertices.push_back(squares[i].triangles[j].z);
                    vertices.push_back(squares[i].texturePos[j].x);
                    vertices.push_back(squares[i].texturePos[j].y);
                }
            }
        }
    }

    glBindVertexArray(VAO);

    // Indices attribute
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // Texture attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    getOpenGLError("Trouble attributing buffer data: ");
}
void ChunkRenderer::unloadChunkVertices() {
    vertices.clear();
    indices.clear();
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);

    getOpenGLError("Trouble delete buffer data: ");
}
void ChunkRenderer::drawChunkVertices() {
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    getOpenGLError("Trouble drawing buffer data: ");
}
void ChunkRenderer::init() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    getOpenGLError("Trouble generating buffer data: ");
}
