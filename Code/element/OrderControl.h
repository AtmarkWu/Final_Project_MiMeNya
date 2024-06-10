#ifndef ORDERCONRTOL_H_INCLUDED
#define ORDERCONRTOL_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [OrderControl object]
*/
typedef struct _OrderControl
{
    //背景圖片設定
    ALLEGRO_BITMAP *background;

    //Clients
    ALLEGRO_BITMAP *Client[2];

    //回到遊戲主畫面的按鈕設定
    int x, y, width, height;
    bool over_button;
    ALLEGRO_BITMAP *button;
    ALLEGRO_BITMAP *highlight;

    int Accept_X, Accept_Y, A_Width, A_Height;
    bool over_Accept_button;

    ALLEGRO_BITMAP *Accept;
    ALLEGRO_BITMAP *Accept_highlight;

    //按鈕音效
    ALLEGRO_SAMPLE *ButtonClick;
    ALLEGRO_SAMPLE_INSTANCE *Click_sample_instance;

    //按鈕音效
    ALLEGRO_SAMPLE *Cashin;
    ALLEGRO_SAMPLE_INSTANCE *Cashin_sample_instance;

    int click;
    

} OrderControl;

Elements *New_OrderControl(int label);
void OrderControl_update(Elements *self);
void OrderControl_interact(Elements *self, Elements *tar);
void OrderControl_draw(Elements *self);
void OrderControl_destory(Elements *self);

void Order_DetectButtonOn(Elements *self);


#endif
