#include <gint/image.h>

#include <gint-extras/display.h>

typedef struct image_linear_map image_linear_map;

void dimage_scale(int x, int y, float scale, const bopti_image_t *image) {
	image_linear_map map;
	image_scale(image, scale*65536, scale*65536, &map);

	bopti_image_t *scaled_image = image_linear_alloc(image, &map);

	dimage(x, y, scaled_image);

	image_free(scaled_image);
}

void dsubimage_scale(int x, int y, const bopti_image_t *image, int left, int top, int width, int height, float scale) {
	bopti_image_t sub_image;
	image_sub(image, left, top, width, height, &sub_image);
	dimage_scale(x, y, scale, &sub_image);
}
