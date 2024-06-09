#ifndef Meat_H_INCLUDED
#define Meat_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
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
    int lenMeat;
    int meatsX[100], meatsY[100], meatType[100];
    ALLEGRO_BITMAP *img;
    ALLEGRO_BITMAP *img1;
    ALLEGRO_BITMAP *img2;
    ALLEGRO_BITMAP *img3;
    Shape *hitbox; // the hitbox of object
    ALLEGRO_COLOR color;

    //記下目前拖出去的肉泥是哪個種類
    int currentMeat;
} Meat;

Elements *New_Meat(int label);
void Meat_update(Elements *self);
void Meat_interact(Elements *self, Elements *tar);
void Meat_draw(Elements *self);
void Meat_destory(Elements *self);

#endif
