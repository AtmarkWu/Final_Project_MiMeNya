#ifndef Cat_H_INCLUDED
#define Cat_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Cat object]
*/
typedef struct _Cat
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    ALLEGRO_BITMAP *img1;
    ALLEGRO_BITMAP *img2;
    ALLEGRO_BITMAP *img3;
    ALLEGRO_BITMAP *img4;
    ALLEGRO_BITMAP *img5;
    ALLEGRO_BITMAP *img6;
    ALLEGRO_BITMAP *img7;
    Shape *hitbox; // the hitbox of object
} Cat;
Elements *New_Cat(int label);
void Cat_update(Elements *self);
void Cat_interact(Elements *self, Elements *tar);
void Cat_draw(Elements *self);
void Cat_destory(Elements *self);
void _Cat_update_position(Elements *self, int dx, int dy);
#endif