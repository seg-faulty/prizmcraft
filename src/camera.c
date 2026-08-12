#include <camera.h>
#include <constants.h>
#include <game.h>

float camera[2] = { 0, 50 };
bool camera_controls[4] = { false, false, false, false };

void camera_update() {
    if (camera_controls[0]) {
        camera[0] -= (float)(2*BLOCK_SCALE*BLOCK_SIZE)/(float)current_fps;
    } else if (camera_controls[1]) {
        camera[0] += (float)(2*BLOCK_SCALE*BLOCK_SIZE)/(float)current_fps;
    }

    if (camera_controls[2]) {
        camera[1] -= (float)(2*BLOCK_SCALE*BLOCK_SIZE)/(float)current_fps;
    } else if (camera_controls[3]) {
        camera[1] += (float)(2*BLOCK_SCALE*BLOCK_SIZE)/(float)current_fps;
    }
}
