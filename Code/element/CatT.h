#ifndef CATT_H_INCLUDED
#define CATT_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [catT object]
*/
//only 一隻貓的測試
typedef struct _catT
{
    int x, y; // the position of cat
    int width, height;

    ALLEGRO_BITMAP *cat;

    Shape *hitbox; // the hitbox of object

    bool Caught; //記錄這隻貓是否被抓到

} catT;

Elements *New_catT(int label);
void catT_update(Elements *self);
void catT_interact(Elements *self, Elements *tar);
void catT_draw(Elements *self);
void catT_destory(Elements *self);

#endif
