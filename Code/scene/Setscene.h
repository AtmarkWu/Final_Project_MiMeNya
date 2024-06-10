#ifndef SETTING_H_INCLUDED
#define SETTING_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Setting object]
*/
typedef struct _Setting
{
    ALLEGRO_FONT *font;

    ALLEGRO_BITMAP *background_image; //【新增儲存圖片的變數】
    ALLEGRO_BITMAP *button[2]; //【存放兩種按鈕】-> ON/OFF
    ALLEGRO_BITMAP *hightlight_button[2]; //【兩種按鈕在滑鼠在上方時會發光】
    bool over_button[3]; //【該按鈕是否與滑鼠位置重疊】-> 有3個選項所以要3個
    int X[3], Y[3]; //【按鈕各自的XY座標】
    int XH[3], YH[3];
    int button_W[2], button_H[2]; //【按鈕圖片的長寬(固定)】
    int buttonH_W[2], buttonH_H[2];

    ALLEGRO_BITMAP *backbutton; //回到菜單的按鈕
    ALLEGRO_BITMAP *highlight_backbutton;
    bool over_backbutton; //【該按鈕是否與滑鼠位置重疊】
    int backX, backY; //【按鈕各自的XY座標】
    int backXH, backYH;
    int backbutton_W, backbutton_H; //【按鈕圖片的長寬(固定)】
    int backbuttonH_W, backbuttonH_H;

    int title_x, title_y;

    int click;
    
    //設定按鈕聲音
    ALLEGRO_SAMPLE *ButtonClick;
    ALLEGRO_SAMPLE_INSTANCE *Click_sample_instance;

} Setting;

Scene *New_Setting(int label);
void Setting_update(Scene *self);
void Setting_draw(Scene *self);
void Setting_destroy(Scene *self);

void Setting_DetectButtonOn(Scene *self);

#endif
