#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED
#include "scene.h"
#include "../element/pageOne.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

/*
   [Book object]
*/
typedef enum BookEleType
{
    Page1Up_L //第一頁上方物件



} BookEleType;

typedef struct _Book
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_BITMAP *background_image; //【存放背景】
    ALLEGRO_BITMAP *button[3]; //【存放按鈕：[0]返回遊戲畫面 | [1]下一頁 | [2]上一頁】
    bool over_button; //【該按鈕是否與滑鼠位置重疊->只針對返回遊戲畫面鍵】
    float X[3], Y[3]; //【按鈕各自的XY座標】
    int button_W[3], button_H[3]; //【按鈕圖片的長寬(固定)】

    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    int title_x, title_y;

} Book;

Scene *New_Book(int label);
void Book_update(Scene *self);
void Book_draw(Scene *self);
void Book_destroy(Scene *self);

void Book_DetectButtonOn(Scene *self);
int BookTurnPage(Scene *self);

#endif
