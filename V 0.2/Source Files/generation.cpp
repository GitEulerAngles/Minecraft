#include "generation.h"

Camera camera;
Texture texture;
GameMap game;

void loadChunk(GameMap* game, glm::vec2 chunkOnPlayer) {
    glm::vec2 currentChunk;

    for (int count = 0; count <= RENDER_VAR; count++)
    for (int x = -count; x <= count; x++) {
        if (x == -count || x == count) {
            for (int y = -count; y <= count; y++) {
                currentChunk = { chunkOnPlayer.x + x, chunkOnPlayer.y + y };
                if (game->renderer.count(currentChunk) == 0) {
                    game->setChunkRenderer(currentChunk.x, currentChunk.y);
                    game->setActiveSides(currentChunk.x, currentChunk.y);
                    return;
                }
            }
        }

        currentChunk = { chunkOnPlayer.x + x, chunkOnPlayer.y + count };
        if (game->renderer.count(currentChunk) == 0) {
            game->setChunkRenderer(currentChunk.x, currentChunk.y);
            game->setActiveSides(currentChunk.x, currentChunk.y);
            return;
        }

        currentChunk = { chunkOnPlayer.x + x, chunkOnPlayer.y - count };
        if (game->renderer.count(currentChunk) == 0) {
            game->setChunkRenderer(currentChunk.x, currentChunk.y);
            game->setActiveSides(currentChunk.x, currentChunk.y);
            return;
        }
    }
}

void generateWorld() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        glm::vec2 chunkOnPlayer = { floor(camera.cameraPos.x / 16),  floor(camera.cameraPos.z / 16) };

        for (int y = -RENDER_VAR - 1; y <= RENDER_VAR + 1; y++)
        for (int x = -RENDER_VAR - 1; x <= RENDER_VAR + 1; x++) {
            glm::vec2 currentChunk = { chunkOnPlayer.x + x, chunkOnPlayer.y + y };
            if (game.data.count(currentChunk) == 0) {
                game.setChunk(currentChunk.x, currentChunk.y);
            }
        }

        loadChunk(&game, chunkOnPlayer);
    }
}
