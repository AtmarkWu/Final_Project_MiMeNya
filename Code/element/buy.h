#ifndef BUY_H_INCLUDED
#define BUY_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Buy object]
*/
typedef struct _Buy
{
    //【所有的肉泥(不確定數量)】
    ALLEGRO_BITMAP *background_image; //【新增儲存圖片的變數】
    ALLEGRO_BITMAP *button[2]; //【存放四種按鈕】
    ALLEGRO_BITMAP *hightlight_button[2]; //【四種按鈕在滑鼠在上方時會發光】
    bool over_button[2]; //【該按鈕是否與滑鼠位置重疊】
    int X[2], Y[2]; //【按鈕各自的XY座標】
    int XH[2], YH[2];
    int button_W[2], button_H[2]; //【按鈕圖片的長寬(固定)】
    int buttonH_W[2], buttonH_H[2];

    ALLEGRO_BITMAP *food[4]; //食物圖示
    int food_X, food_Y;

    int MeatPrice[5]; //[1]:第一個肉泥價格、[2]:第二個肉泥價格......
    ALLEGRO_BITMAP *NoMoney; //錢不夠時顯示的圖片
    bool NoEnough; //判斷是否購買時錢不夠(用來顯示特定標題字&圖片)

    //ALLEGRO_SAMPLE *song;
    //ALLEGRO_SAMPLE_INSTANCE *sample_instance;

    //付錢音效
    ALLEGRO_SAMPLE *PayMoney;
    ALLEGRO_SAMPLE_INSTANCE *PayMoney_sample_instance;

    //按鈕音效
    ALLEGRO_SAMPLE *ButtonClick;
    ALLEGRO_SAMPLE_INSTANCE *Click_sample_instance;

    ALLEGRO_FONT *font;
    int q_x, q_y; //購買詢問字體用
    int NE_x, NE_y; //錢不夠買時的標題字用



} Buy;

Elements *New_Buy(int label);
void buy_update(Elements *self);
void buy_interact(Elements *self, Elements *tar);
void buy_draw(Elements *self);
void buy_destroy(Elements *self);

void Buy_DetectButtonOn(Elements *self);

#endif
