#ifndef CAPTURE_H_INCLUDED
#define CAPTURE_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Capture object]
*/
typedef struct _Capture
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *Catch;
    Shape *hitbox; // the hitbox of object

    //設定模式(現在是否為顯示網子的模式)
    int Ready; //0 -> 不顯示 | 1 -> 顯示

} Capture;
Elements *New_Capture(int label);
void Capture_update(Elements *self);
void Capture_interact(Elements *self, Elements *tar);
void Capture_draw(Elements *self);
void Capture_destory(Elements *self);

#endif