#ifndef GEXTRA_IMAGE_H
#define GEXTRA_IMAGE_H

#include <gint/display.h>

#include <prizm_maths.h>

void image_add_subimage(int, int, const bopti_image_t*, int, int, int, int, bopti_image_t*, int);
void image_add_image(int, int, const bopti_image_t*, bopti_image_t*, int);

bopti_image_t *image_transform(const bopti_image_t*, const mat3x3);

#endif
