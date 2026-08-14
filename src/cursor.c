#include <constants.h>
#include <cursor.h>

Cursor cursor;

void cursor_init() {
    cursor.block = block_new(80, 48, 80, 48, 80, 48);
    cursor.x = 0;
    cursor.y = 4;
    cursor.z = 0;
}

void cursor_draw() {
    block_draw(cursor.block, cursor.x, cursor.y, cursor.z);
}

void cursor_move(int dx, int dy, int dz) {
    cursor.x += dx;
    cursor.y += dy;
    cursor.z += dz;

    if (cursor.x < 0) { cursor.x = 0; }
    else if (cursor.x >= WORLD_LENGTH) { cursor.x = WORLD_LENGTH-1; }

    if (cursor.y < 0) { cursor.y = 0; }
    else if (cursor.y >= WORLD_HEIGHT) { cursor.y = WORLD_HEIGHT-1; }

    if (cursor.z < 0) { cursor.z = 0; }
    else if (cursor.z >= WORLD_WIDTH) { cursor.z = WORLD_WIDTH-1; }

    // TODO: Make sure the cursor is connected to a block
}
