#ifndef GEXTRA_DISPLAY_H
#define GEXTRA_DISPLAY_H

#include <gint/display.h>

void dimage_scale(int x, int y, float scale, const bopti_image_t *image);
void dsubimage_scale(int x, int y, const bopti_image_t *image, int left, int top, int width, int height, float scale);

#endif
