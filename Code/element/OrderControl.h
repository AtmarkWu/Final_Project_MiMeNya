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

    //回到遊戲主畫面的按鈕設定
    int x, y, width, height;
    bool over_button;
    ALLEGRO_BITMAP *button;
    ALLEGRO_BITMAP *highlight;
    

} OrderControl;

Elements *New_OrderControl(int label);
void OrderControl_update(Elements *self);
void OrderControl_interact(Elements *self, Elements *tar);
void OrderControl_draw(Elements *self);
void OrderControl_destory(Elements *self);

void Order_DetectButtonOn(Elements *self);

//void SeeDetail(Elements *self);
//void HowManyCatIHave(Elements *self, int Cat_n);
//void PrintNumber(Elements *self, int num, int gap);


#endif
