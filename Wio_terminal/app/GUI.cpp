#include "GUI.h"

State GUI::state;
Menu GUI::menu;
Spectrum GUI::spectrum;

/* Display flushing */
void GUI::my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint16_t c;

    tft.startWrite(); /* Start new TFT transaction */
    tft.setAddrWindow(area->x1, area->y1, (area->x2 - area->x1 + 1), (area->y2 - area->y1 + 1)); /* set the working window */
    for (int y = area->y1; y <= area->y2; y++)
    {
        for (int x = area->x1; x <= area->x2; x++)
        {
            c = color_p->full;
            tft.writeColor(c, 1);
            color_p++;
        }
    }
    tft.endWrite();            /* terminate TFT transaction */
    lv_disp_flush_ready(disp); /* tell lvgl that flushing is done */
}

bool GUI::BTN_A(lv_indev_drv_t *indev, lv_indev_data_t *data)
{
    return processBTN(WIO_KEY_A, data);
}

bool GUI::BTN_B(lv_indev_drv_t *indev, lv_indev_data_t *data)
{
    return processBTN(WIO_KEY_B, data);
}

bool GUI::BTN_C(lv_indev_drv_t *indev, lv_indev_data_t *data)
{
    return processBTN(WIO_KEY_C, data);
}

bool GUI::processBTN(int pin, lv_indev_data_t *data)
{
    bool btn_pr = digitalRead(pin) == LOW;
    if (btn_pr)
    {
        data->state = LV_INDEV_STATE_PR;
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }
    return false;
}

// Change state of LV data according to the pressed button
bool GUI::keypad_navigation(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
    bool isPressed = true;
    if (digitalRead(WIO_5S_UP) == LOW)
    {
        data->key = LV_KEY_UP;
    }
    else if (digitalRead(WIO_5S_DOWN) == LOW)
    {
        data->key = LV_KEY_DOWN;
    }
    else if (digitalRead(WIO_5S_LEFT) == LOW)
    {
        data->key = LV_KEY_LEFT;
    }
    else if (digitalRead(WIO_5S_RIGHT) == LOW)
    {
        data->key = LV_KEY_RIGHT;
    }
    else if (digitalRead(WIO_5S_PRESS) == LOW)
    {
        data->key = LV_KEY_ENTER;
        analogWrite(WIO_BUZZER, 128);
        delay(100);
        analogWrite(WIO_BUZZER, 0);
    }
    else
    {
        isPressed = false;
    }

    if (isPressed)
    {
        data->state = LV_INDEV_STATE_PR;
    }
    else
    {
        data->state = LV_INDEV_STATE_REL;
    }

    return false; /*No buffering now so no more data read*/
}

void GUI::setup()
{
    // Configure the buttons to be input
    pinMode(WIO_KEY_C, INPUT_PULLUP);
    pinMode(WIO_KEY_B, INPUT_PULLUP);
    pinMode(WIO_KEY_A, INPUT_PULLUP);

    pinMode(WIO_5S_UP, INPUT_PULLUP);
    pinMode(WIO_5S_DOWN, INPUT_PULLUP);
    pinMode(WIO_5S_LEFT, INPUT_PULLUP);
    pinMode(WIO_5S_RIGHT, INPUT_PULLUP);
    pinMode(WIO_5S_PRESS, INPUT_PULLUP);

    // Configure the buzzer to be output
    pinMode(WIO_BUZZER, OUTPUT);

    tft.begin();                       /* TFT init */
    tft.setRotation(landscape.type); /* Landscape orientation */

    //drawImage<uint16_t>("robin.bpm", 0, 0);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.setFreeFont(&FreeSansBoldOblique12pt7b); //select Free, Sans, Bold, Oblique, 12pt.
    tft.drawString("PROJECT ROBIN",70,80);//prints string at (70,80)
    //tft.drawFastHLine(70,130,200,TFT_WHITE);
    tft.drawRect(70,130,200,20,TFT_WHITE); 
    delay(1000);
    tft.setFreeFont(NULL);

    lv_init(); // Init LVGL library

    lv_disp_buf_init(&disp_buf, buf, buf2, LV_HOR_RES_MAX * 10); // Init display buffers

    tft.fillRect(70,130,50,20,TFT_WHITE); 
    delay(100);
    
    /*Initialize the display*/
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = landscape.width;
    disp_drv.ver_res = landscape.height;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.buffer = &disp_buf;
    lv_disp_drv_register(&disp_drv);

    tft.fillRect(70,130,100,20,TFT_WHITE); 
    delay(500);
    
    /*Initialize the buttons*/
    lv_indev_drv_t indev_drv1;
    lv_indev_drv_init(&indev_drv1);
    indev_drv1.type = LV_INDEV_TYPE_BUTTON;
    indev_drv1.read_cb = BTN_C;
    lv_indev_t *my_indev1 = lv_indev_drv_register(&indev_drv1);

    lv_indev_drv_t indev_drv2;
    lv_indev_drv_init(&indev_drv2);
    indev_drv2.type = LV_INDEV_TYPE_BUTTON;
    indev_drv2.read_cb = BTN_B;
    lv_indev_t *my_indev2 = lv_indev_drv_register(&indev_drv2);

    lv_indev_drv_t indev_drv3;
    lv_indev_drv_init(&indev_drv3);
    indev_drv3.type = LV_INDEV_TYPE_BUTTON;
    indev_drv3.read_cb = BTN_A;
    lv_indev_t *my_indev3 = lv_indev_drv_register(&indev_drv3);

    lv_indev_drv_t indev_drv4;
    lv_indev_drv_init(&indev_drv4);
    indev_drv4.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv4.read_cb = keypad_navigation;
    input = lv_indev_drv_register(&indev_drv4);

    tft.fillRect(70,130,150,20,TFT_WHITE); 
    delay(200);
    
    state = State::MENU;
    menu.setup(this);

    tft.fillRect(70,130,200,20,TFT_WHITE); 
    delay(1000);
}

void GUI::tick()
{
    lv_tick_inc(LVGL_TICK_PERIOD);
    
    switch (state)
    {
    case State::MENU:
        menu.tick();
        break;
    case State::SPECTRUM:
        spectrum.tick();
        break;
    default:
        menu.tick();
        break;
    }

    if(backBTN() && state != State::MENU) {
        state = State::MENU;
        spectrum.dispFreq = true;
        initMenu();
    }
}

bool GUI::backBTN() {
    return digitalRead(WIO_KEY_C) == LOW;
}

void GUI::initSpectrum()
{
    spectrum.setup(&tft);
}

void GUI::initMenu()
{
    lv_scr_load(Menu::screen1); // Load menu screen
}

void GUI::handle_button(lv_obj_t *obj, lv_event_t event)
{
    if (event == LV_EVENT_CLICKED)
    {
        Serial.println("Clicked");
    }
    else if (event == LV_EVENT_VALUE_CHANGED)
    {
        Serial.println("Toggled");
    }
}

State GUI::getState()
{
    return state;
}
void GUI::setState(State next)
{
    state = next;
}
