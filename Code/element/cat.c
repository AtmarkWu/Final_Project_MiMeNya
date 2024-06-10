#include "cat.h"
//#include "../global.h"
#include "../shapes/Circle.h"
#include "meat.h"
#include <allegro5/allegro_primitives.h>

Elements *New_Cat(int label)
{
    Cat *pDerivedObj = (Cat *)malloc(sizeof(Cat));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/cat_no1.png");
    pDerivedObj->img1 = al_load_bitmap("assets/image/cat_no2.png");
    pDerivedObj->img2 = al_load_bitmap("assets/image/cat_no3.png");
    pDerivedObj->img3 = al_load_bitmap("assets/image/cat_no4.png");
    pDerivedObj->img4 = al_load_bitmap("assets/image/sleep_no1.png");
    pDerivedObj->img5 = al_load_bitmap("assets/image/sleep_no2.png");
    pDerivedObj->img6 = al_load_bitmap("assets/image/sleep_no3.png");
    pDerivedObj->img7 = al_load_bitmap("assets/image/sleep_no4.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 0;
    pDerivedObj->y = 0;
    for(int i = 0; i < 100; i++){
        posx[i] = 1440;
    }
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2,
                                     pDerivedObj->y + pDerivedObj->height / 2,
                                     min(pDerivedObj->width, pDerivedObj->height) / 2);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Meat_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Cat_update;
    pObj->Interact = Cat_interact;
    pObj->Draw = Cat_draw;
    pObj->Destroy = Cat_destory;

    return pObj;
}
void Cat_update(Elements *self)
{
    //Cat *Obj = ((Cat *)(self->pDerivedObj));
    for(int i = 0; i < lenMeat; i++){
        if(posx[i] > meatsX[i]) posx[i] -= 5;
        else if(posx[i] <= meatsX[i]) {
            posx[i] = meatsX[i];
        }
    }
}

void Cat_interact(Elements *self, Elements *tar)
{
    //Cat *ct = ((Cat *)(self->pDerivedObj));
}

//if mouse_button_down -> draw
void Cat_draw(Elements *self)
{
    Cat *Obj = ((Cat *)(self->pDerivedObj));
    for(int i=0;i<lenMeat;i++){
        switch (meatType[i])   
        {
        case 1:
            //al_draw_bitmap(Obj->img, posx[i], meatsY[i]-45, 0);
            if(posx[i] != meatsX[i]) al_draw_bitmap(Obj->img, posx[i], meatsY[i]-45, 0);
            else {meatType[i] = 5;}
            break;

        case 2:
            if(posx[i] != meatsX[i]) al_draw_bitmap(Obj->img1, posx[i], meatsY[i]-45, 0);
            else {meatType[i] = 6;}
            break;

        case 3:
            if(posx[i] != meatsX[i]) al_draw_bitmap(Obj->img2, posx[i], meatsY[i]-45, 0);
            else {meatType[i] = 7;}
            break;

        case 4:
            if(posx[i] != meatsX[i]) al_draw_bitmap(Obj->img3, posx[i], meatsY[i]-45, 0);
            else {meatType[i] = 8;}
            break;

        case 5:
            al_draw_bitmap(Obj->img4, posx[i], meatsY[i]-45, 0);
            break;

        case 6:
            al_draw_bitmap(Obj->img5, posx[i], meatsY[i]-45, 0);
            break;

        case 7:
            al_draw_bitmap(Obj->img6, posx[i], meatsY[i]-45, 0);
            break;

        case 8:
            al_draw_bitmap(Obj->img7, posx[i], meatsY[i]-45, 0);
            break;

        default:
            break;
        }
    }
}
void Cat_destory(Elements *self)
{
    Cat *Obj = ((Cat *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    al_destroy_bitmap(Obj->img1);
    al_destroy_bitmap(Obj->img2);
    al_destroy_bitmap(Obj->img3);
    al_destroy_bitmap(Obj->img4);
    al_destroy_bitmap(Obj->img5);
    al_destroy_bitmap(Obj->img6);
    al_destroy_bitmap(Obj->img7);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}