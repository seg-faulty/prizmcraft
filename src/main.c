#include <gint/display.h>
#include <gint/keyboard.h>
#include <gint/gint.h>
#include <gint/rtc.h>
#include <gint/clock.h>

#include <gint-extras/image.h>
#include <gint-extras/display.h>

#include <fxlibc/printf.h>

#include <assets.h>
#include <block.h>
#include <camera.h>
#include <constants.h>
#include <prizm_maths.h>
#include <world.h>

int frames_count = 0;
int current_fps = 0;
int next_fps = 0;

uint32_t last_second = 0;

Block stone;
Block cobblestone;
Block bricks;
Block dirt;
Block grass;

float camera_translation[2] = { 0, 0 };
int handle_input() {
	key_event_t event = pollevent();
	if (event.type == KEYEV_DOWN) {
		switch (event.key) {
			case KEY_LEFT:
				camera_translation[0] = (float)-(2*BLOCK_SCALE*BLOCK_SIZE)/(float)current_fps;
				break;
			case KEY_RIGHT:
				camera_translation[0] = (float)(2*BLOCK_SCALE*BLOCK_SIZE)/(float)current_fps;
				break;
			case KEY_UP:
				camera_translation[1] = (float)-(2*BLOCK_SCALE*BLOCK_SIZE)/(float)current_fps;
				break;
			case KEY_DOWN:
				camera_translation[1] = (float)(2*BLOCK_SCALE*BLOCK_SIZE)/(float)current_fps;
				break;
			case KEY_MENU: {
				return 1;
			}
		}
	} else if (event.type == KEYEV_UP) {
		switch (event.key) {
			case KEY_LEFT:
			case KEY_RIGHT:
				camera_translation[0] = 0;
				break;
			case KEY_UP:
			case KEY_DOWN:
				camera_translation[1] = 0;
				break;
		}
	}

	return 0;
}

void draw() {
	dclear(0x6f7e);

	world_draw();

	dprint(10, 10, C_WHITE, "FPS: %d", current_fps);

	dupdate();
}

void update() {
	camera_move(camera_translation[0], camera_translation[1]);
}

int main(void)
{
	gint_setrestart(1);
	__printf_enable_fp();
	clock_set_speed(CLOCK_SPEED_F4);

	// bopti_image_t *bg = image_alloc(DWIDTH, DHEIGHT, IMAGE_RGB565A);

	// for (int y = 0; y < DHEIGHT; y += 64) {
	// 	for (int x = 0; x < DWIDTH; x += 64) {
	// 		image_add_subimage(x, y, &img_textures, 96, 48, 32, 32, bg, 2);
	// 	}
	// }

	// bopti_image_t *title = image_alloc(133, 18, IMAGE_RGB565A);
	// image_fill(title, 1);
	// image_add_subimage(0, 0, &img_textures, 0, 48, 64, 18, title, 1);
	// image_add_subimage(64, 0, &img_textures, 0, 66, 69, 18, title, 1);

	// screen = image_alloc(DWIDTH, DHEIGHT, IMAGE_RGB565A);
	
	stone = block_new(0, 0, 0, 0, 0, 0);
	cobblestone = block_new(16, 0, 16, 0, 16, 0);
	bricks = block_new(32, 0, 32, 0, 32, 0);
	dirt = block_new(48, 0, 48, 0, 48, 0);
	grass = block_new(80, 0, 64, 0, 64, 0);

	world_generate();

	for (;;) {
		if (handle_input() == 1) { break; }
		update();
		draw();

		next_fps++;

		if (rtc_ticks() - last_second >= 128) {
			last_second = rtc_ticks();
			current_fps = next_fps;
			next_fps = 0;
		}

	}

	return 1;
}
