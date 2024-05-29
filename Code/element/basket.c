#include "basket.h"
#include "../shapes/Rectangle.h"
/*
   [Basket function]
*/
Elements *New_Basket(int label)
{
    Basket *pDerivedObj = (Basket *)malloc(sizeof(Basket));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/basket_pink.png");
    pDerivedObj->img1 = al_load_bitmap("assets/image/basket_red.png");
    pDerivedObj->img2 = al_load_bitmap("assets/image/basket_green.png");
    pDerivedObj->img3 = al_load_bitmap("assets/image/basket_blue.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 90;
    pDerivedObj->y = HEIGHT - pDerivedObj->height-50;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    pDerivedObj->hitbox1 = New_Rectangle(pDerivedObj->x+200,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width+200,
                                        pDerivedObj->y + pDerivedObj->height);
    pDerivedObj->hitbox2 = New_Rectangle(pDerivedObj->x+400,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width+400,
                                        pDerivedObj->y + pDerivedObj->height);
    pDerivedObj->hitbox3 = New_Rectangle(pDerivedObj->x+600,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width+600,
                                        pDerivedObj->y + pDerivedObj->height);                                                                        
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Basket_update;
    pObj->Interact = Basket_interact;
    pObj->Draw = Basket_draw;
    pObj->Destroy = Basket_destory;
    return pObj;
}
void Basket_update(Elements *self) {}
void Basket_interact(Elements *self, Elements *tar) {}
void Basket_draw(Elements *self)
{
    Basket *Obj = ((Basket *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
    al_draw_bitmap(Obj->img1, Obj->x+200, Obj->y, 0);
    al_draw_bitmap(Obj->img2, Obj->x+400, Obj->y, 0);
    al_draw_bitmap(Obj->img3, Obj->x+600, Obj->y, 0);
}
void Basket_destory(Elements *self)
{
    Basket *Obj = ((Basket *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
