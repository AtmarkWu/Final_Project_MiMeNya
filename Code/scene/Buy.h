#ifndef BUY_H_INCLUDED
#define BUY_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Buy object]
*/
typedef struct _Buy
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;

    //【所有的肉泥(不確定數量)】
    ALLEGRO_BITMAP *background_image; //【新增儲存圖片的變數】
    ALLEGRO_BITMAP *button[2]; //【存放四種按鈕】
    ALLEGRO_BITMAP *hightlight_button[2]; //【四種按鈕在滑鼠在上方時會發光】
    bool over_button[2]; //【該按鈕是否與滑鼠位置重疊】
    int X[4], Y[4]; //【按鈕各自的XY座標】
    int button_W, button_H; //【按鈕圖片的長寬(固定)】

    ALLEGRO_BITMAP *food[3]; //【四種按鈕在滑鼠在上方時會發光】
    int food_X, food_Y;

    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    int title_x, title_y;

} Buy;

Scene *New_Buy(int label);
void buy_update(Scene *self);
void buy_draw(Scene *self);
void buy_destroy(Scene *self);

void Buy_DetectButtonOn(Scene *self);

#endif
