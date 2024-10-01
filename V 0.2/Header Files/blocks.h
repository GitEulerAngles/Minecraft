#ifndef BLOCKS
#define BLOCKS

#include "Shaders.h"
#include <random>
#include <unordered_map>
#include <array>

#define RENDER_VAR 8

const int BlockCoords[][6] = {
    {2,0,1,1,1,1},
    {0,0,0,0,0,0},
    {3,3,3,3,3,3}
};
enum BlockType {
    air = -1,
    grass = 0, 
    dirt = 1,
    sand = 2
};
struct Vec2Hash {
    std::size_t operator () (const glm::vec2& p) const {
        auto hash1 = std::hash<float>{}(p.x);
        auto hash2 = std::hash<float>{}(p.y);
        return hash1 ^ hash2;
    }
};
struct Square {
    glm::vec3 triangles[4];
    glm::vec2 texturePos[4];
};
struct Block {
    BlockType type = BlockType::air;
};
struct BlockRenderer : Block {
    void getSquareVertices(std::array<Square, 6>& squares);
    void getSquareTextures(int width, int height, std::array<Square, 6>& squares);
    bool sidesActive[6];
    glm::vec3 position = { 0,0,0 };
};
struct Chunk {
    Block chunkData[16][64][16];
};
struct ChunkRenderer {
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    bool ready = false, cooked = false;
    GLuint VBO, VAO, EBO;
    Chunk* pChunkData;
    BlockRenderer chunkData[16][64][16];
    void loadChunkVertices();
    void unloadChunkVertices();
    void drawChunkVertices();
    void init();
};
class GameMap {
public:
    void setChunk(int chunk_x, int chunk_y);
    void setChunkRenderer(int chunk_x, int chunk_y);
    void setActiveSides(int chunk_x, int chunk_y);
    std::unordered_map<glm::vec2, Chunk*, Vec2Hash> data;
    std::unordered_map<glm::vec2, ChunkRenderer*, Vec2Hash> renderer;
};
#endif // !BLOCKS
