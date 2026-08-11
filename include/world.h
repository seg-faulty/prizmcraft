#ifndef WORLD_H
#define WORLD_H

#include <sys/types.h>

#include <block.h>
#include <constants.h>

extern uint8_t world[WORLD_HEIGHT][WORLD_LENGTH][WORLD_WIDTH];

extern Block stone;
extern Block cobblestone;
extern Block bricks;
extern Block dirt;
extern Block grass;

void world_generate();
void world_draw();

#endif
