#ifndef GEXTRA_IMAGE_H
#define GEXTRA_IMAGE_H

#include <gint/display.h>

#include <prizm_maths.h>

void image_sub_scale(const bopti_image_t *src, int x, int y, int width, int height, int scale, bopti_image_t *dst);
void image_add_subimage(int x, int y, const bopti_image_t *from, int left, int top, int width, int height, bopti_image_t *to, int scale);
void image_add_image(int x, int y, const bopti_image_t *from, bopti_image_t *to, int scale);

bopti_image_t * image_transform(const bopti_image_t *src, const mat3x3 trans);

void image_fill_opacity(bopti_image_t *img, int value, float opacity);

#endif
