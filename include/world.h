#ifndef WORLD_H
#define WORLD_H

#include <sys/types.h>

#include <block.h>
#include <constants.h>

extern uint8_t world[WORLD_HEIGHT][WORLD_WIDTH][WORLD_LENGTH];

extern Block stone;
extern Block cobblestone;
extern Block bricks;
extern Block dirt;
extern Block grass;
extern Block planks;
extern Block log;
extern Block leaves;
extern Block glass;

void world_generate();
void world_draw();

#endif
