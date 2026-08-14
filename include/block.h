#ifndef BLOCK_H
#define BLOCK_H

#include <gint/display.h>

typedef struct {
    bopti_image_t *top;
    bopti_image_t *front;
    bopti_image_t *side;
} Block;

Block block_new(int, int, int, int, int, int);
void block_destroy(Block);
void block_draw(Block, int, int, int);

void block_draw_selected(Block block);

#endif
