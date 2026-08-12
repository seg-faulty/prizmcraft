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
#include <game.h>
#include <menu.h>
#include <prizm_maths.h>
#include <world.h>

int frames_count = 0;
int current_fps = 0;
int next_fps = 0;
uint32_t last_second = 0;

uint8_t scene = SCENE_TITLE;

Block stone;
Block cobblestone;
Block bricks;
Block dirt;
Block grass;

bopti_image_t bg;
bopti_image_t button;
bopti_image_t *title;

Menu title_menu;

int handle_input() {
	key_event_t event = pollevent();
	switch (scene) {
		case SCENE_TITLE:
			if (event.type == KEYEV_DOWN) {
				switch (event.key) {
					case KEY_UP:
						menu_up(&title_menu);
						break;
					case KEY_DOWN:
						menu_down(&title_menu);
						break;
					case KEY_EXE:
						if (title_menu.selected == 0) { scene = SCENE_GAME; }
						break;
					case KEY_MENU: {
						return 1;
					}
				}
			}
			break;
		case SCENE_GAME:
			if (event.type == KEYEV_DOWN) {
				switch (event.key) {
					case KEY_LEFT:
						camera_controls[0] = true;
						camera_controls[1] = false;
						break;
					case KEY_RIGHT:
						camera_controls[0] = false;
						camera_controls[1] = true;
						break;
					case KEY_UP:
						camera_controls[2] = true;
						camera_controls[3] = false;
						break;
					case KEY_DOWN:
						camera_controls[2] = false;
						camera_controls[3] = true;
						break;
					case KEY_MENU: {
						return 1;
					}
				}
			} else if (event.type == KEYEV_UP) {
				switch (event.key) {
					case KEY_LEFT:
						camera_controls[0] = false;
						break;
					case KEY_RIGHT:
						camera_controls[1] = false;
						break;
					case KEY_UP:
						camera_controls[2] = false;
						break;
					case KEY_DOWN:
						camera_controls[3] = false;
						break;
				}
			}
			break;
	}


	return 0;
}

void draw() {
	dclear(0x6f7e);

	switch (scene) {
		case SCENE_TITLE: 
			for (int y = 0; y < DHEIGHT; y += 64) {
				for (int x = 0; x < DWIDTH; x += 64) {
					dimage_scale(x, y, 2, &bg);
				}
			}
			dimage_scale(0.5*(DWIDTH - 2*title->width), 5, 2, title);
			menu_draw(&title_menu);
			break;
		case SCENE_GAME:
			world_draw();
		
			break;
	}

	dprint(10, 10, C_WHITE, "FPS: %d", current_fps);

	dupdate();
}

void update() {
	camera_update();
}

int main(void)
{
	gint_setrestart(1);
	__printf_enable_fp();
	clock_set_speed(CLOCK_SPEED_F4);

	image_sub(&img_textures, 96, 48, 32, 32, &bg);

	title = image_alloc(133, 18, IMAGE_RGB565A);
	image_fill(title, 1);
	image_add_subimage(0, 0, &img_textures, 0, 48, 64, 18, title, 1);
	image_add_subimage(64, 0, &img_textures, 0, 66, 69, 18, title, 1);
	
	image_sub(&img_textures, 0, 88, 100, 40, &button);

	title_menu = menu_create(0.5*DWIDTH, 0.5*DHEIGHT - 0.75*(button.height + 2), 1.5);
	menu_add_entry(&title_menu, "Play");
	menu_add_entry(&title_menu, "Reset");

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
