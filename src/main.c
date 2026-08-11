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
#include <constants.h>
#include <prizm_maths.h>

int frames_count = 0;
int current_fps = 0;
int next_fps = 0;

uint32_t last_second = 0;
bopti_image_t *screen;

Block grass;
Block dirt;
Block stone;
Block bricks;

int handle_input() {
	key_event_t event = pollevent();
	if (event.type == KEYEV_DOWN) {
		switch (event.key) {
			case KEY_MENU: {
				return 1;
			}
		}
	}

	return 0;
}

void draw() {
	image_fill(screen, 0x6f7e);

	block_draw(grass, 50, 50);
	dimage(0, 0, screen);

	dprint(10, 10, C_WHITE, "FPS: %d", current_fps);

	dupdate();
}

int main(void)
{
	gint_setrestart(1);
	__printf_enable_fp();

	bopti_image_t *bg = image_alloc(DWIDTH, DHEIGHT, IMAGE_RGB565A);

	for (int y = 0; y < DHEIGHT; y += 64) {
		for (int x = 0; x < DWIDTH; x += 64) {
			image_add_subimage(x, y, &img_textures, 96, 48, 32, 32, bg, 2);
		}
	}

	bopti_image_t *title = image_alloc(133, 18, IMAGE_RGB565A);
	image_fill(title, 1);
	image_add_subimage(0, 0, &img_textures, 0, 48, 64, 18, title, 1);
	image_add_subimage(64, 0, &img_textures, 0, 66, 69, 18, title, 1);

	screen = image_alloc(DWIDTH, DHEIGHT, IMAGE_RGB565A);

	grass = block_new(80, 0, 64, 0, 64, 0);

	for (;;) {
		draw();
		if (handle_input() == 1) { break; }

		next_fps++;

		if (rtc_ticks() - last_second >= 128) {
			last_second = rtc_ticks();
			current_fps = next_fps;
			next_fps = 0;
		}

	}

	return 1;
}
