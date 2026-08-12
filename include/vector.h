#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    char **data;
    int size;
    int max_size;
} Vector;

Vector vector_create();

void vector_push(Vector *v, char *str);
char *vector_at(Vector *v, int i);

void vector_free(Vector *v);

#endif
