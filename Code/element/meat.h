#ifndef Meat_H_INCLUDED
#define Meat_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Meat object]
*/
typedef struct _Meat
{
    int x, y; // the position of image
    int posx, posy; // the position of put down meat
    int r;    // the radius
    int in;
    int click; // to know when to draw
    int currentColor;
    bool deleteFlag;
    //int lenMeat;
    //int meatsX[100], meatsY[100], meatType[100];
    ALLEGRO_BITMAP *img;
    ALLEGRO_BITMAP *img1;
    ALLEGRO_BITMAP *img2;
    ALLEGRO_BITMAP *img3;
    Shape *hitbox; // the hitbox of object
    ALLEGRO_COLOR color;

    //拾起音效
    ALLEGRO_SAMPLE *PickUp;
    ALLEGRO_SAMPLE_INSTANCE *PickUp_sample_instance;
    //放下
    ALLEGRO_SAMPLE *PutDown;
    ALLEGRO_SAMPLE_INSTANCE *PutDown_sample_instance;

    //記下目前拖出去的肉泥是哪個種類
    int currentMeat;
} Meat;

Elements *New_Meat(int label);
void Meat_update(Elements *self);
void Meat_interact(Elements *self, Elements *tar);
void Meat_draw(Elements *self);
void Meat_destory(Elements *self);

#endif
