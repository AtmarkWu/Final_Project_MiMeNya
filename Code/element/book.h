#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Book object]
*/

typedef struct _Book
{
    ALLEGRO_BITMAP *background_image; //【存放背景】
    ALLEGRO_BITMAP *button[3]; //【存放按鈕：[0]返回遊戲畫面 | [1]下一頁 | [2]上一頁】
    bool over_button; //【該按鈕是否與滑鼠位置重疊->只針對返回遊戲畫面鍵】
    float X[3], Y[3]; //【按鈕各自的XY座標】
    int button_W[3], button_H[3]; //【按鈕圖片的長寬(固定)】

    ALLEGRO_BITMAP *cover; //圖鑑封面裝飾

    int title_x, title_y;
    ALLEGRO_FONT *font;

    int pressD; //紀錄是否按下D，在按下放開的瞬間改變page的值
    int pressA; //紀錄是否按下A，在按下放開的瞬間改變page的值

} Book;

Elements *New_Book(int label);
void Book_update(Elements *self);
void Book_interact(Elements *self, Elements *tar);
void Book_draw(Elements *self);
void Book_destroy(Elements *self);

void Book_DetectButtonOn(Elements *self);
int BookTurnPage(Elements *self);

#endif
