#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Menu object]
*/
typedef struct _Menu
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;

    ALLEGRO_BITMAP *background_image; //【新增儲存圖片的變數】
    ALLEGRO_BITMAP *button[4]; //【存放四種按鈕】
    ALLEGRO_BITMAP *hightlight_button[4]; //【四種按鈕在滑鼠在上方時會發光】
    bool over_button[4]; //【該按鈕是否與滑鼠位置重疊】
    int X[4], Y[4]; //【按鈕各自的XY座標】
    int XH[4], YH[4]; //放大效果按鈕的XY座標
    int button_W[4], button_H[4]; //【按鈕圖片的長寬(固定)】
    int buttonH_W[4], buttonH_H[4];

    int click;

    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    int title_x, title_y;    //按鈕音效

    ALLEGRO_SAMPLE *ButtonClick;
    ALLEGRO_SAMPLE_INSTANCE *Click_sample_instance;

    int timerF;

} Menu;

Scene *New_Menu(int label);
void menu_update(Scene *self);
void menu_draw(Scene *self);
void menu_destroy(Scene *self);

void DetectButtonOn(Scene *self);

#endif
