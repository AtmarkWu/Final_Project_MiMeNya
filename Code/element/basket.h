#ifndef Basket_H_INCLUDED
#define Basket_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [Basket object]
*/
typedef struct _Basket
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    ALLEGRO_BITMAP *img1;
    ALLEGRO_BITMAP *img2;
    ALLEGRO_BITMAP *img3;
    Shape *hitbox; // the hitbox of object
    Shape *hitbox1;
    Shape *hitbox2;
    Shape *hitbox3;
} Basket;
Elements *New_Basket(int label);
void Basket_update(Elements *self);
void Basket_interact(Elements *self, Elements *tar);
void Basket_draw(Elements *self);
void Basket_destory(Elements *self);

#endif