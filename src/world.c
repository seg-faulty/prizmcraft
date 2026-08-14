#include <camera.h>
#include <cursor.h>
#include <game.h>
#include <world.h>

uint8_t world[WORLD_HEIGHT][WORLD_LENGTH][WORLD_WIDTH];

void world_generate() {
    for (uint8_t y = 0; y < WORLD_HEIGHT; y++) {
        for (uint8_t z = 0; z < WORLD_WIDTH; z++) {
            for (uint8_t x = 0; x < WORLD_LENGTH; x++) {
                if (y == 0) {
                    world[y][z][x] = BLOCK_STONE;
                } else if (y < 3) {
                    world[y][z][x] = BLOCK_DIRT;
                } else if (y == 3) {
                    world[y][z][x] = BLOCK_GRASS;
                } else {
                    world[y][z][x] = BLOCK_AIR;
                }
            }
        }
    }
}

void world_draw() {
    for (int8_t y = 0; y < WORLD_HEIGHT; y++) {
        for (int8_t z = WORLD_WIDTH-1; z >= 0; z--) {
            for (int8_t x = WORLD_LENGTH-1; x >= 0; x--) {
                uint8_t block = world[y][x][z];
                bool is_cursor = (mode) ? false : (cursor.x == x && cursor.y == y && cursor.z == z);
                if (block == BLOCK_AIR && !is_cursor) { continue; }

                switch (block) {
                    case BLOCK_STONE:
                        block_draw(stone, x, y, z);
                        break;
                    case BLOCK_COBBLESTONE:
                        block_draw(cobblestone, x, y, z);
                        break;
                    case BLOCK_DIRT:
                        block_draw(dirt, x, y, z);
                        break;
                    case BLOCK_GRASS:
                        block_draw(grass, x, y, z);
                        break;
                }

                if (is_cursor) {
                    cursor_draw();
                }
            }
        }
    }
}
