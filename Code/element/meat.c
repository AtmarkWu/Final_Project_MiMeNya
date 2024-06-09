#include "meat.h"
#include "../global.h"
#include "../shapes/Circle.h"
#include <allegro5/allegro_primitives.h>
//肉泥拖曳功能，若沒有該種類的肉泥(數量為0)，就無法拖曳
//每拖出去一次，就減少一個肉泥持有數

Elements *New_Meat(int label)
{
    Meat *pDerivedObj = (Meat *)malloc(sizeof(Meat));
    Elements *pObj = New_Elements(label);
    pDerivedObj->img = al_load_bitmap("assets/image/meat_pink.png");
    pDerivedObj->img1 = al_load_bitmap("assets/image/meat_red.png");
    pDerivedObj->img2 = al_load_bitmap("assets/image/meat_green.png");
    pDerivedObj->img3 = al_load_bitmap("assets/image/meat_blue.png");
    pDerivedObj->x = mouse.x;
    pDerivedObj->y = mouse.y;
    pDerivedObj->posx = 0;
    pDerivedObj->posy = 0;
    pDerivedObj->r = 10;
    pDerivedObj->in = -1;
    pDerivedObj->click = 0;
    pDerivedObj->lenMeat = 0;
    pDerivedObj->currentColor = 0;
    for(int i=0;i<100;i++){
        pDerivedObj->meatsX[i] = 0;
        pDerivedObj->meatsY[i] = 0;
        pDerivedObj->meatType[i] = 0;
    }
    //pDerivedObj->meatX = 0;
    //pDerivedObj->meatY = 0;
    //pDerivedObj->shouldDrawMeat = false;
    pDerivedObj->color = al_map_rgb(255, 0, 0);
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x,
                                     pDerivedObj->y,
                                     pDerivedObj->r);

    pDerivedObj->currentMeat = 0;

    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Basket_L;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = Meat_draw;
    pObj->Update = Meat_update;
    pObj->Interact = Meat_interact;
    pObj->Destroy = Meat_destory;
    return pObj;
}
void Meat_update(Elements *self)
{
    if(gameFunction == -1){ //如果現在是遊戲功能開啟，再進行更新
        Meat *Obj = ((Meat *)(self->pDerivedObj));
        Shape *hitbox = Obj->hitbox;
        hitbox->update_center_x(hitbox, mouse.x - Obj->x);
        hitbox->update_center_y(hitbox, mouse.y - Obj->y);
        Obj->x = mouse.x;
        Obj->y = mouse.y;
    }
}
void Meat_interact(Elements *self, Elements *tar)
{
    if(gameFunction == -1){ //如果現在是遊戲功能開啟，再進行互動感應
        Meat *Obj = ((Meat *)(self->pDerivedObj));
        if(!mouse_state[1])
        {
            if (Obj->click){
                Obj->meatsX[Obj->lenMeat] = mouse.x;
                Obj->meatsY[Obj->lenMeat] = mouse.y;
                Obj->meatType[Obj->lenMeat] = Obj->currentColor;
                Obj->lenMeat++;
                OwnMeat[Obj->currentMeat]--; //拖曳出去放開後，持有數減一
            }
            Obj->click = 0;
        }
        else if (tar->label == Basket_L)
        {
            Basket *Obj2 = ((Basket *)(tar->pDerivedObj));
            if (Obj->hitbox->overlap(Obj->hitbox, Obj2->hitbox) && mouse_state[1])
            {
                if(OwnMeat[1] != 0){ //如果擁有該種類的肉泥才能拖曳
                    Obj->click = 1;
                    Obj->color = al_map_rgb(250, 164, 147);
                    Obj->in = Basket_L;
                    Obj->currentColor = 1;
                    Obj->currentMeat = 1;
                }
            }
            if (Obj->hitbox->overlap(Obj->hitbox, Obj2->hitbox1) && mouse_state[1])
            {
                if(OwnMeat[2] != 0){ //如果擁有該種類的肉泥才能拖曳
                    Obj->click = 1;
                    Obj->color = al_map_rgb(222, 73, 53);
                    Obj->in = Basket_L;
                    Obj->currentColor = 2;
                    Obj->currentMeat = 2;
                }
            }
            if (Obj->hitbox->overlap(Obj->hitbox, Obj2->hitbox2) && mouse_state[1])
            {
                if(OwnMeat[3] != 0){ //如果擁有該種類的肉泥才能拖曳
                    Obj->click = 1;
                    Obj->color = al_map_rgb(96, 152, 151);
                    Obj->in = Basket_L;
                    Obj->currentColor = 3;
                    Obj->currentMeat = 3;     
                }
            }
            if (Obj->hitbox->overlap(Obj->hitbox, Obj2->hitbox3) && mouse_state[1])
            {
                if(OwnMeat[4] != 0){ //如果擁有該種類的肉泥才能拖曳
                    Obj->click = 1;
                    Obj->color = al_map_rgb(150, 191, 210);
                    Obj->in = Basket_L;
                    Obj->currentColor = 4;
                    Obj->currentMeat = 4;
                }
            }

        }
    }

}

//if mouse_button_down -> draw
void Meat_draw(Elements *self)
{
    if(gameFunction == -1){ //如果現在是遊戲功能，再畫出肉泥
        Meat *Obj = ((Meat *)(self->pDerivedObj));
        if(Obj->click == 1 && mouse_state[1])
        {
            al_draw_circle(Obj->x, Obj->y, Obj->r, Obj->color, 10);
        }
        for(int i=0;i<Obj->lenMeat;i++){
            //al_draw_bitmap(Obj->img1, Obj->meatsX[i], Obj->meatsY[i], 0);
            switch (Obj->meatType[i])   
            {
            case 1:
                al_draw_bitmap(Obj->img, Obj->meatsX[i], Obj->meatsY[i]-45, 0);
                break;
            case 2:
                al_draw_bitmap(Obj->img1, Obj->meatsX[i], Obj->meatsY[i]-45, 0);
                break;
            case 3:
                al_draw_bitmap(Obj->img2, Obj->meatsX[i], Obj->meatsY[i]-45, 0);
                break;
            case 4:
                al_draw_bitmap(Obj->img3, Obj->meatsX[i], Obj->meatsY[i]-45, 0);
                break;
            default:
                break;
            }
        }
    }
}
void Meat_destory(Elements *self)
{
    Meat *Obj = ((Meat *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    al_destroy_bitmap(Obj->img1);
    al_destroy_bitmap(Obj->img2);
    al_destroy_bitmap(Obj->img3);

    free(Obj->hitbox);
    free(Obj);
    free(self);
}