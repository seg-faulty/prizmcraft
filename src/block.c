#include <gint/image.h>

#include <gint-extras/display.h>
#include <gint-extras/image.h>

#include <assets.h>
#include <block.h>
#include <camera.h>
#include <constants.h>
#include <world.h>

Block block_new(int t_x, int t_y, int f_x, int f_y, int s_x, int s_y) {
    bopti_image_t top_flat;
    image_sub(&img_textures, t_x, t_y, BLOCK_SIZE, BLOCK_SIZE, &top_flat);

    bopti_image_t front_flat;
    image_sub(&img_textures, f_x, f_y, BLOCK_SIZE, BLOCK_SIZE, &front_flat);

    bopti_image_t side_flat;
    image_sub(&img_textures, s_x, s_y, BLOCK_SIZE, BLOCK_SIZE, &side_flat);

    Block block;

    block.top = image_transform(&top_flat, block_transformation_matrix);
    block.front = image_alloc(BLOCK_SIZE, BLOCK_SIZE + 7, IMAGE_RGB565A);
    block.side = image_alloc(BLOCK_SIZE, BLOCK_SIZE + 7, IMAGE_RGB565A);
    image_fill(block.front, image_alpha(IMAGE_RGB565A));
    image_fill(block.side, image_alpha(IMAGE_RGB565A));

    for (int x = 0; x < BLOCK_SIZE; x++) {
        for (int y = 0; y < BLOCK_SIZE; y++) {
            color_t front_pixel = image_get_pixel(&front_flat, x, y);
            image_set_pixel(block.front, x, y + (x / 2), front_pixel);

            color_t side_pixel = image_get_pixel(&side_flat, x, y);
            image_set_pixel(block.side, x, (block.side->height - BLOCK_SIZE) + y - (x / 2), side_pixel);
        }
    }

    return block;

}

void block_destroy(Block block) {
    if (image_valid(block.top)) { image_free(block.top); }
    if (image_valid(block.front)) { image_free(block.front); }
    if (image_valid(block.side)) { image_free(block.side); }
}

void block_draw(Block block, int x, int y, int z) {
    if (((y < WORLD_HEIGHT-1) ? world[y+1][z][x] : 0) && ((x > 0) ? world[y][z-1][x] : 0) && ((z > 0) ? world[y][z][x-1] : 0)) { return; }

    int real_x = (int)(0.5f*DWIDTH + BLOCK_SIZE*BLOCK_SCALE*((float)z - (float)x - 1.0f) - camera[0]);
    int real_y = (int)(0.5f*DHEIGHT - 0.5f*BLOCK_SIZE*BLOCK_SCALE*(2.0f*(float)y + (float)z + (float)x) - camera[1]);

    if (real_x + 2*BLOCK_SIZE*BLOCK_SCALE < 0 || real_x > DWIDTH) { return; }
    if (real_y + BLOCK_SCALE*block.front->height < 0 || real_y - BLOCK_SCALE*block.top->height > DHEIGHT) { return; }

    if (((z > 0) ? !world[y][z-1][x] : 1)) {
        dimage_scale(real_x, real_y, BLOCK_SCALE, block.front);
    }

    if (((x > 0) ? !world[y][z][x-1] : 1)) {
        dimage_scale(real_x+block.front->width*BLOCK_SCALE, real_y, BLOCK_SCALE, block.side);
    }

    if (((y < WORLD_HEIGHT-1) ? !world[y+1][z][x] : 1)) {
        dimage_scale(real_x, real_y-0.5*BLOCK_SCALE*block.top->height, BLOCK_SCALE, block.top);
    }
}

void block_draw_selected(Block block) {
    int start_x = DWIDTH - block.front->width - block.side->width - 3;
    int start_y = 11;
    
    dimage_scale(start_x, start_y, 1.0f, block.front);
    dimage_scale(start_x+block.front->width, start_y, 1.0f, block.side);
    dimage_scale(start_x, start_y-0.5*block.top->height, 1.0f, block.top);
}
