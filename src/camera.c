#include <camera.h>

float camera[2] = { 0, 50 };

void camera_move(float dx, float dy) {
    camera[0] += dx;
    camera[1] += dy;
}
