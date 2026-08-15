#include <gint/image.h>

#include <gint-extras/image.h>

typedef struct image_linear_map image_linear_map;

void image_sub_scale(const bopti_image_t *src, int x, int y, int width, int height, int scale, bopti_image_t *dst) {
	if (scale == 1) {
		image_sub(src, x, y, width, height, dst);
	}

	bopti_image_t sub_image;
	image_sub(src, x, y, width, height, &sub_image);
	
	image_linear_map map;
	image_scale(&sub_image, scale*65536, scale*65536, &map);
	dst = image_linear_alloc(&sub_image, &map);
}

void image_add_subimage(int x, int y, const bopti_image_t *from, int left, int top, int width, int height, bopti_image_t *to, int scale) {
	bopti_image_t sub_image;
	image_sub(from, left, top, width, height, &sub_image);

	bopti_image_t *scaled_image;

	if (scale != 1) {
		image_linear_map map;
		image_scale(&sub_image, scale*65536, scale*65536, &map);
		scaled_image = image_linear_alloc(&sub_image, &map);
	} else {
		scaled_image = image_copy_alloc(&sub_image, sub_image.format);
	}

	for (int i = 0; i < height*scale; i++) {
		for (int j = 0; j < width*scale; j++) {
			int pixel = image_get_pixel(scaled_image, j, i);
			if (from->format == IMAGE_RGB565A || from->format == IMAGE_P4_RGB565A || from->format == IMAGE_P8_RGB565A) {
				if (pixel == image_alpha(from->format)) { continue; }
			}
			image_set_pixel(to, x + j, y + i, pixel);
		}
	}

	image_free(scaled_image);
}

void image_add_image(int x, int y, const bopti_image_t *from, bopti_image_t *to, int scale) {
	image_add_subimage(x, y, from, 0, 0, from->width, from->height, to, scale);
}

bopti_image_t * image_transform(const bopti_image_t *src, const mat3x3 trans) {
	int t_width = 0;
	int t_height = 0;
	for (int y = 0; y <= src->height; y++) {
		for (int x = 0; x <= src->width; x++) {
			mat3x1 pos = { x, y, 1 };
			mat3x1 pos_trans = { 0, 0, 0 };
			transform_point(block_transformation_matrix, pos, pos_trans);

			if (pos_trans[0] > (float)t_width) {
				t_width = (int)pos_trans[0];
			}
			if (pos_trans[1] > (float)t_height) {
				t_height = (int)pos_trans[1];
			}
		}
	}

	bopti_image_t *dst = image_alloc(t_width, t_height, src->format);
	image_fill(dst, 1);
	for (int y = 0; y < src->height; y++) {
		for (int x = 0; x < src->width; x++) {
			mat3x1 pos = { x, y, 1 };
			mat3x1 pos_trans = { 0, 0, 0 };
			transform_point(trans, pos, pos_trans);

			image_set_pixel(dst, (int)pos_trans[0], (int)pos_trans[1], image_get_pixel(src, x, y));
		}
	}

	return dst;
}

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} Color_RGB;

Color_RGB hex_to_rgb(color_t c) {
    Color_RGB rgb;

	rgb.r = c >> 11;
	rgb.g = (c - (rgb.r << 11)) >> 5;
	rgb.b = c - (rgb.r << 11) - (rgb.g << 5);

    return rgb;
}

color_t blend_colors(color_t c1, color_t c2, float opacity) {
	Color_RGB rgb1 = hex_to_rgb(c1);
	Color_RGB rgb2 = hex_to_rgb(c2);

	int diff_r = rgb2.r - rgb1.r;
	int diff_g = rgb2.g - rgb1.g;
	int diff_b = rgb2.b - rgb1.b;

	float r = rgb1.r + opacity*(float)diff_r;
	float g = rgb1.g + opacity*(float)diff_g;
	float b = rgb1.b + opacity*(float)diff_b;

	return ((int)r << 11) + ((int)g << 5) + (int)b;
}

color_t last_color;
color_t blended;
bool last_color_set = false;

void image_fill_opacity(bopti_image_t *img, int value, float opacity) {
	for (int y = 0; y < img->height; y++) {
		for (int x = 0; x < img->width; x++) {
			color_t pixel = image_get_pixel(img, x, y);
			if (pixel != last_color || !last_color_set) {
				blended = blend_colors(pixel, value, opacity);
				last_color = pixel;
				last_color_set = true;
			}

			image_set_pixel(img, x, y, blended);
		}
	}
	last_color_set = false;
}
