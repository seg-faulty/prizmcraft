#ifndef MENU_H
#define MENU_H

#include <sys/types.h>

#include <vector.h>

typedef struct {
    int x;
    int y;
    float scale;
    Vector entries;
    uint8_t selected;
} Menu;

Menu menu_create(int x, int y, float scale);

void menu_add_entry(Menu *menu, char *entry);
void menu_draw(Menu *menu);
void menu_up(Menu *menu);
void menu_down(Menu *menu);

void menu_destroy(Menu *menu);

#endif
