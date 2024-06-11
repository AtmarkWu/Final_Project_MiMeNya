#ifndef EXIT_H_INCLUDED
#define EXIT_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Exit object]
*/

typedef struct _Exit
{
    ALLEGRO_BITMAP *image[48]; //【存放背景】

    int currentFrame;
    int FakeTimer;

    //按鈕音效
    ALLEGRO_SAMPLE *ButtonClick;
    ALLEGRO_SAMPLE_INSTANCE *Click_sample_instance;

    int click;

} Exit;

Elements *New_Exit(int label);
void Exit_update(Elements *self);
void Exit_interact(Elements *self, Elements *tar);
void Exit_draw(Elements *self);
void Exit_destroy(Elements *self);

//int ExitTurnPage(Elements *self);

#endif
