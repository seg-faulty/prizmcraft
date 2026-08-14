#ifndef CURSOR_H
#define CURSOR_H

#include <block.h>

typedef struct {
    Block block;
    int x;
    int y;
    int z;
} Cursor;

extern Cursor cursor;

void cursor_init();
void cursor_draw();
void cursor_move(int dx, int dy, int dz);

#endif
