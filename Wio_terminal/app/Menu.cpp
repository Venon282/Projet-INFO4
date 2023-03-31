#include "Menu.h"
#include "GUI.h"

GUI *Menu::gui;
lv_obj_t *Menu::screen1;
lv_obj_t *Menu::screen2;

void Menu::setup(GUI *g)
{
    gui = g;
    screen1 = lv_scr_act();
    screen2 = lv_obj_create(NULL,NULL);  // screen for submenus
    lv_obj_set_style_local_bg_color(screen2, LV_OBJ_PART_MAIN, 0, LV_COLOR_BLACK);
    lv_task_t *task = lv_task_create(menuView, 500, LV_TASK_PRIO_MID, NULL);
    lv_task_set_repeat_count(task, 1);
}

void Menu::tick()
{
    lv_task_handler();
}

void Menu::handle_menu(lv_obj_t *obj, lv_event_t event)
{
    // Make the focused button checked
    uint16_t focusIndex = lv_btnmatrix_get_focused_btn(obj);
    lv_btnmatrix_clear_btn_ctrl_all(obj, LV_BTNMATRIX_CTRL_CHECK_STATE);
    lv_btnmatrix_set_btn_ctrl(obj, focusIndex, LV_BTNMATRIX_CTRL_CHECK_STATE);

    // If the enter button is pressed
    if (event == LV_EVENT_VALUE_CHANGED)
    {
        const char *txt = lv_btnmatrix_get_active_btn_text(obj);

        if (txt == "Continuous")
        {
            Serial.println("Continuous recognition");
            gui->setState(State::CONTINUOUS);
        }
        else if (txt == "Manual")
        {
            Serial.println("Manual recognition");
            gui->setState(State::MANUAL);
        }
        else if (txt == "Spectrum")
        {
            Serial.println("Audio spectrum");
            gui->setState(State::SPECTRUM);
            lv_scr_load(screen2);  // Switch screen
            gui->initSpectrum();
        }
        else if (txt == "Results")
        {
            Serial.println("Show results");
            gui->setState(State::RESULTS);
        }
        else if (txt == "LoRaWAN")
        {
            Serial.println("Send with LoRaWAN");
            gui->setState(State::LORAWAN);
        }
        else if (txt == "Time")
        {
            Serial.println("Show/edit time");
            gui->setState(State::TIME);
        }
    }
}

// Main menu creation
lv_group_t *Menu::mainMenu(lv_obj_t *parent)
{
    static const char *btnm_map[] = {"Continuous", "Manual", "Spectrum", "\n", "Results", "LoRaWAN", "Time", ""};

    lv_obj_t *btnm1 = lv_btnmatrix_create(parent, NULL);
    lv_btnmatrix_set_map(btnm1, btnm_map);
    lv_obj_set_size(btnm1, landscape.safeWidth, landscape.safeHeight);
    lv_obj_align(btnm1, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_event_cb(btnm1, handle_menu);

    lv_group_t *g = lv_group_create();
    lv_group_add_obj(g, btnm1);
    return g;
}

void Menu::menuView(lv_task_t *task)
{
    groupMenu = mainMenu(lv_scr_act());
    lv_indev_set_group(gui->input, groupMenu);
}
