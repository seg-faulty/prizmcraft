#include <gint/kmalloc.h>

#include <string.h>

#include <vector.h>

Vector vector_create() {
    Vector v;
    v.max_size = 5;
    v.data = kmalloc(sizeof(char*)*v.max_size, "_uram");
    v.size = 0;
    
    return v;
}

void vector_push(Vector *v, char *str) {
    if (v->size == v->max_size) {
        char **backup = kmalloc(sizeof(char*)*v->max_size, "_uram");
        memcpy(backup, v->data, sizeof(char*)*v->max_size);
        kfree(v->data);

        v->max_size *= 2;
        v->data = kmalloc(sizeof(char*)*v->max_size, "_uram");
        memcpy(v->data, backup, sizeof(char*)*(v->max_size/2));
        kfree(backup);
    }

    v->data[v->size++] = str;
}

char *vector_at(Vector *v, int i) {
    if (i >= v->size) {
        return "\0";
    }

    return v->data[i];
}

void vector_free(Vector *v) {
    kfree(v->data);
    v->size = 0;
    v->max_size = 0;
}
