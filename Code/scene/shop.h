#ifndef SHOP_H_INCLUDED
#define SHOP_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Shop object]
*/
typedef struct _Shop
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;

    //【所有的肉泥(不確定數量)】
    ALLEGRO_BITMAP *background_image; //【新增儲存圖片的變數】
    ALLEGRO_BITMAP *button[3]; //【存放四種按鈕】
    ALLEGRO_BITMAP *hightlight_button[3]; //【四種按鈕在滑鼠在上方時會發光】
    bool over_button[3]; //【該按鈕是否與滑鼠位置重疊】
    int X[6], Y[6]; //【按鈕各自的XY座標】
    int button_W, button_H; //【按鈕圖片的長寬(固定)】

    //back to gamescene button
    ALLEGRO_BITMAP *back_button; //【回到頁面】
    ALLEGRO_BITMAP *highlight_back_button; //【回到頁面發光】
    bool over_back_button; //【該按鈕是否與滑鼠位置重疊】
    int back_button_X, back_button_Y;
    int back_button_W, back_button_H;

    ALLEGRO_BITMAP *Money;

    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    int title_x, title_y;



} Shop;

Scene *New_Shop(int label);
void shop_update(Scene *self);
void shop_draw(Scene *self);
void shop_destroy(Scene *self);

void Shop_DetectButtonOn(Scene *self);

#endif
