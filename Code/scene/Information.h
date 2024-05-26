#ifndef INFORMATION_H_INCLUDED
#define INFORMATION_H_INCLUDED
#include "scene.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

/*
   [Information object]
*/
typedef struct _Info
{
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_BITMAP *background_image; //【新增儲存圖片的變數】
    ALLEGRO_BITMAP *button; //【存放按鈕】
    ALLEGRO_BITMAP *hightlight_button; //【按鈕在滑鼠在上方時會發光】
    bool over_button; //【該按鈕是否與滑鼠位置重疊】
    int X[2], Y[2]; //【按鈕各自的XY座標】
    int button_W, button_H; //【按鈕圖片的長寬(固定)】

    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    int title_x, title_y;

} Info;

Scene *New_Info(int label);
void Info_update(Scene *self);
void Info_draw(Scene *self);
void Info_destroy(Scene *self);

void Info_DetectButtonOn(Scene *self);

#endif
