#ifndef PRIZM_MATHS
#define PRIZM_MATHS 

typedef float mat3x3[3][3];
typedef float mat3x1[3];

static const mat3x3 block_transformation_matrix = {
    { 1.0f, -1.0f, 16.0f },
    { 0.5f, 0.5f, 0.0f },
    { 0.0f, 0.0f, 1.0f }
};

int abs(int);

void transform_point(const mat3x3, mat3x1, mat3x1);

#endif
