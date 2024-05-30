#include "CatT.h"
#include "../shapes/Rectangle.h"
#include <allegro5/allegro_primitives.h>

Elements *New_catT(int label)
{
    catT *pDerivedObj = (catT *)malloc(sizeof(catT));
    Elements *pObj = New_Elements(label);
    //設定貓咪圖片位置(尚未加入移動功能)
    pDerivedObj->cat = al_load_bitmap("assets/image/BookButton/cat1_d.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->cat);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->cat);
    pDerivedObj->x = WIDTH/2;
    pDerivedObj->y = (HEIGHT/2)-50;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    pDerivedObj->Caught = false; //一開始預設為【沒被抓】
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Capture_L;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = catT_draw;
    pObj->Update = catT_update;
    pObj->Interact = catT_interact;
    pObj->Destroy = catT_destory;
    return pObj;
}

void catT_update(Elements *self)
{
    catT *Obj = ((catT *)(self->pDerivedObj));
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, Obj->x - Obj->x);
    hitbox->update_center_y(hitbox, Obj->y - Obj->y);
    Obj->x = Obj->x;
    Obj->y = Obj->y;
}

void catT_interact(Elements *self, Elements *tar)
{
    catT *Obj = ((catT *)(self->pDerivedObj));
    Capture *tar_obj = ((Capture *)(tar->pDerivedObj));
    if(mouse_state[1] && tar_obj->Ready){ //如果滑鼠按下的當下是開啟捕捉模式
        if(Obj->hitbox->overlap(Obj->hitbox, tar_obj->hitbox)){ //如果貓咪跟項圈的hitbox重疊 -> 抓到貓咪，數量++且貓咪消失
            printf("Cat: Oh No!\n");
            self->dele = true;
        }
        //如果hitbox沒有重疊 -> 在capture.c會設定項圈消失
    }

}

void catT_draw(Elements *self)
{
    // catT *Obj = ((catT *)(self->pDerivedObj));
    // if(Obj->click == 1 && mouse_state[1])
    // {
    //     catT *Obj = ((catT *)(self->pDerivedObj));
    //     al_draw_circle(Obj->x, Obj->y, Obj->r, Obj->color, 10);
    // }
    // for(int i=0;i<Obj->lencatT;i++){
    //     //al_draw_bitmap(Obj->img1, Obj->catTsX[i], Obj->catTsY[i], 0);
    //     switch (Obj->catTType[i])   
    //     {
    //     case 1:
    //         al_draw_bitmap(Obj->img, Obj->catTsX[i], Obj->catTsY[i]-45, 0);
    //         break;
    //     case 2:
    //         al_draw_bitmap(Obj->img1, Obj->catTsX[i], Obj->catTsY[i]-45, 0);
    //         break;
    //     case 3:
    //         al_draw_bitmap(Obj->img2, Obj->catTsX[i], Obj->catTsY[i]-45, 0);
    //         break;
    //     case 4:
    //         al_draw_bitmap(Obj->img3, Obj->catTsX[i], Obj->catTsY[i]-45, 0);
    //         break;
    //     default:
    //         break;
    //     }
    // }
    catT *Obj = ((catT *)(self->pDerivedObj));
    al_draw_bitmap(Obj->cat, Obj->x, Obj->y, 0);
}
void catT_destory(Elements *self)
{
    catT *Obj = ((catT *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->cat);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}