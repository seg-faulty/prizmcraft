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

    bopti_image_t *top = image_transform(&top_flat, block_transformation_matrix);
    bopti_image_t *front = image_alloc(BLOCK_SIZE, BLOCK_SIZE + 7, IMAGE_RGB565A);
    bopti_image_t *side = image_alloc(BLOCK_SIZE, BLOCK_SIZE + 7, IMAGE_RGB565A);

    image_fill(front, image_alpha(IMAGE_RGB565A));
    image_fill(side, image_alpha(IMAGE_RGB565A));

    for (int x = 0; x < BLOCK_SIZE; x++) {
        for (int y = 0; y < BLOCK_SIZE; y++) {
            color_t front_pixel = image_get_pixel(&front_flat, x, y);
            image_set_pixel(front, x, y + (x / 2), front_pixel);

            color_t side_pixel = image_get_pixel(&side_flat, x, y);
            image_set_pixel(side, x, (side->height - BLOCK_SIZE) + y - (x / 2), side_pixel);
        }
    }

    block.item = image_alloc(32, 32, IMAGE_RGB565A);
    image_fill(block.item, image_alpha(IMAGE_RGB565A));
    image_add_image(0, 0, top, block.item, 1);
    image_add_image(0, top->height / 2, front, block.item, 1);
    image_add_image(front->width, top->height / 2, side, block.item, 1);

	struct image_linear_map map_top;
	image_scale(top, BLOCK_SCALE*65536, BLOCK_SCALE*65536, &map_top);

	struct image_linear_map map_front;
	image_scale(front, BLOCK_SCALE*65536, BLOCK_SCALE*65536, &map_front);

	struct image_linear_map map_side;
	image_scale(side, BLOCK_SCALE*65536, BLOCK_SCALE*65536, &map_side);

    block.top = image_linear_alloc(top, &map_top);
    block.front = image_linear_alloc(front, &map_front);
    block.side = image_linear_alloc(side, &map_side);

    image_free(top);
    image_free(front);
    image_free(side);

    return block;

}

void block_destroy(Block block) {
    if (image_valid(block.top)) { image_free(block.top); }
    if (image_valid(block.front)) { image_free(block.front); }
    if (image_valid(block.side)) { image_free(block.side); }
}

void block_draw(Block block, int x, int y, int z) {
    if (((y < WORLD_HEIGHT-1) ? !block_is_transparent(world[y+1][z][x]) : 0) && ((x > 0) ? !block_is_transparent(world[y][z-1][x]) : 0) && ((z > 0) ? !block_is_transparent(world[y][z][x-1]) : 0)) { return; }

    int real_x = (int)(0.5f*DWIDTH + BLOCK_SIZE*BLOCK_SCALE*((float)z - (float)x - 1.0f) - camera[0]);
    int real_y = (int)(0.5f*DHEIGHT - 0.5f*BLOCK_SIZE*BLOCK_SCALE*(2.0f*(float)y + (float)z + (float)x) + camera[1]);

    if (real_x + 2*BLOCK_SIZE*BLOCK_SCALE < 0 || real_x > DWIDTH) { return; }
    if (real_y + BLOCK_SCALE*block.front->height < 0 || real_y - BLOCK_SCALE*block.top->height > DHEIGHT) { return; }

    if (((z > 0) ? block_is_transparent(world[y][z-1][x]) : true)) {
        dimage(real_x, real_y, block.front);
    }

    if (((x > 0) ? block_is_transparent(world[y][z][x-1]) : true)) {
        dimage(real_x+block.front->width, real_y, block.side);
    }

    if (((y < WORLD_HEIGHT-1) ? block_is_transparent(world[y+1][z][x]) : true)) {
        dimage(real_x, real_y-0.5*block.top->height, block.top);
    }
}

void block_draw_selected(Block block) {
    int start_x = DWIDTH - block.item->width - 5;
    int start_y = 5;

    dimage(start_x, start_y, block.item);
}

bool block_is_transparent(int block) {
    return block == BLOCK_GLASS || block == BLOCK_LEAVES || block == BLOCK_AIR;
}
