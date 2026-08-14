#ifndef BLOCK_H
#define BLOCK_H

#include <gint/display.h>

typedef struct {
    bopti_image_t *top;
    bopti_image_t *front;
    bopti_image_t *side;
} Block;

Block block_new(int t_x, int t_y, int f_x, int f_y, int s_x, int s_y);
void block_destroy(Block block);
void block_draw(Block block, int x, int y, int z);

void block_draw_selected(Block block);

bool block_is_transparent(int block);

#endif
