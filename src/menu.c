#include <gint/display.h>

#include <gint-extras/display.h>

#include <assets.h>
#include <menu.h>

Menu menu_create(int x, int y, float scale) {
    Menu menu;
    menu.x = x;
    menu.y = y;
    menu.scale = scale;
    menu.selected = 0;

    menu.entries = vector_create();

    return menu;
}

void menu_add_entry(Menu *menu, char *entry) {
    vector_push(&(menu->entries), entry);
}

void menu_draw(Menu *menu) {
    for (int i = 0; i < menu->entries.size; i++) {
        if (i == menu->selected) {
            dsubimage_scale(menu->x - 0.5*button.width*menu->scale, menu->y + i*0.5*button.height*menu->scale + 2.0f*menu->scale*i, &button, 0, 20, 100, 20, menu->scale);
        } else {
            dsubimage_scale(menu->x - 0.5*button.width*menu->scale, menu->y + i*0.5*button.height*menu->scale + 2.0f*menu->scale*i, &button, 0, 0, 100, 20, menu->scale);
        }
        
        dtext_opt(menu->x, menu->y + 0.5*button.height*menu->scale*(i + 0.5) + 2.0f*menu->scale*i, C_WHITE, C_NONE, DTEXT_CENTER, DTEXT_MIDDLE, vector_at(&(menu->entries), i));
    }
}

void menu_up(Menu *menu) {
    if (menu->selected == 0) {
        menu->selected = (menu->entries.size) ? menu->entries.size-1 : 0;
    } else {
        menu->selected--;
    }
}

void menu_down(Menu *menu) {
    if (++menu->selected >= menu->entries.size) {
        menu->selected = 0;
    }
}

void menu_destroy(Menu *menu) {
    vector_free(&(menu->entries));

    menu->x = 0;
    menu->y = 0;
    menu->scale = 0;
    menu->selected = 0;
}
