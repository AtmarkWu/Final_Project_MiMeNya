#ifndef SHOP_H_INCLUDED
#define SHOP_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Shop object]
*/
typedef struct _Shop
{
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

    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;

    //字體設定
    ALLEGRO_FONT *font;
    int title_x, title_y;



} Shop;

Elements *New_Shop(int label);
void shop_update(Elements *self);
void shop_interact(Elements *self, Elements *tar);
void shop_draw(Elements *self);
void shop_destroy(Elements *self);

void Shop_DetectButtonOn(Elements *self);
void HowManyMoneyIHave(Elements *self);
void PrintMoney(Elements *self, int num, int gap);

#endif