#ifndef GENERATION
#define GENERATION

#include "blocks.h"
#include <chrono>
#include <thread>

extern Camera camera; 
extern Texture texture;
extern GameMap game;

void generateWorld();
void loadChunk(GameMap* game, glm::vec2 chunkOnPlayer);

#endif //!GENERATION
