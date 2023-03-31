#ifndef GUI_H
#define GUI_H

#include <lvgl.h>
#include <TFT_eSPI.h>
#include "Arduino.h"
#include "Menu.h"
#include "State.h"
#include "Spectrum.cpp"
#define LVGL_TICK_PERIOD 16

struct Orientation
{
    int type;
    int width;
    int height;
    int safeWidth;
    int safeHeight;
};

static const Orientation landscape = {3, 320, 240, 300, 170};

static TFT_eSPI tft = TFT_eSPI();

// LVGL display buffers data
static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10];
static lv_color_t buf2[LV_HOR_RES_MAX * 10];

class GUI
{
public:
    inline static lv_indev_t *input;
    static State state;
    static Menu menu;
    static Spectrum spectrum;

    static void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);

    static bool BTN_A(lv_indev_drv_t *indev, lv_indev_data_t *data);

    static bool BTN_B(lv_indev_drv_t *indev, lv_indev_data_t *data);

    static bool BTN_C(lv_indev_drv_t *indev, lv_indev_data_t *data);

    static bool processBTN(int pin, lv_indev_data_t *data);

    static bool keypad_navigation(lv_indev_drv_t *drv, lv_indev_data_t *data);

    void setup();

    static void tick();

    static bool backBTN();

    static void initSpectrum();

    static void initMenu();

    static void handle_button(lv_obj_t *obj, lv_event_t event);

    static State getState();

    static void setState(State next);

};

#endif
