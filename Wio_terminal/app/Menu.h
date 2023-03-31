#ifndef MENU_H
#define MENU_H

#include <lvgl.h>
#include "State.h"
#include "Arduino.h"

class GUI;

class Menu
{
private:
    inline static lv_group_t *groupMenu;
public:
    static GUI *gui;
    static lv_obj_t *screen1;
    static lv_obj_t *screen2;

    static void setup(GUI *g);

    static void tick();

    static void handle_menu(lv_obj_t *obj, lv_event_t event);

    static lv_group_t *mainMenu(lv_obj_t *parent);

    static void menuView(lv_task_t *task);

};

#endif
