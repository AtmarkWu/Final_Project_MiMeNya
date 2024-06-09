#ifndef PAGETWO_H_INCLUDED
#define PAGETWO_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [PageTwo object]
*/
typedef struct _PageTwo
{
    //預視圖設定
    int x[2], y[2];          // the position of image
    int width[2], height[2]; // the width and height of image
    ALLEGRO_BITMAP *frame[2]; //真正產生互動的範圍圖片
    ALLEGRO_BITMAP *decFrame[2]; //上面有裝飾的
    //預視圖內容圖片設定
    int Cx[2], Cy[2];
    int C_w[2], C_h[2];
    ALLEGRO_BITMAP *NoContent; //沒有該貓咪時顯示的圖片(預設)
    ALLEGRO_BITMAP *Content[2]; //有該貓咪時顯示的圖片
    ALLEGRO_BITMAP *LackSign; //沒有該貓咪的標籤
    ALLEGRO_BITMAP *GetSign; //擁有該貓咪的標籤
    ALLEGRO_BITMAP *NewSign; //該貓咪為新獲得的標籤

    //細節放大圖設定
    bool Open[2]; //玩家是否有關閉or開啟預視圖
    ALLEGRO_BITMAP *Detail;
    int current_open; //紀錄現在正打開的細節放大圖是誰
    //細節放大圖內容設定
    int Dx[2], Dy[2];
    int D_w[2], D_h[2];
    ALLEGRO_BITMAP *D_content[2]; //該貓咪的全貌圖
    //細節圖要顯示的貓咪持有數設定
    int titleX, titleY;
    ALLEGRO_FONT *font;

} PageTwo;

Elements *New_PageTwo(int label);
void PageTwo_update(Elements *self);
void PageTwo_interact(Elements *self, Elements *tar);
void PageTwo_draw(Elements *self);
void PageTwo_destory(Elements *self);

void SeeDetail2(Elements *self);
void HowManyCatIHave2(Elements *self, int Cat_n);
void PrintNumber2(Elements *self, int num, int gap);


#endif
