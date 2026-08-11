#include <prizm_maths.h>

int abs(int x) {
	if (x < 0) {
		return -1*x;
	}
	return x;
}

void transform_point(const mat3x3 trans, mat3x1 point, mat3x1 result) {
    result[0] = trans[0][0]*point[0] + trans[0][1]*point[1] + trans[0][2]*point[2];
    result[1] = trans[1][0]*point[0] + trans[1][1]*point[1] + trans[1][2]*point[2];
    result[2] = trans[2][0]*point[0] + trans[2][1]*point[1] + trans[2][2]*point[2];
}
