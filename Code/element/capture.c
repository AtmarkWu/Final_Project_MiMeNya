#include "capture.h"
#include "../shapes/Rectangle.h"
/*
   [Capture function]
*/
Elements *New_Capture(int label)
{
    Capture *pDerivedObj = (Capture *)malloc(sizeof(Capture));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->Catch = al_load_bitmap("assets/image/capture.png");

    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->Catch);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->Catch);
    pDerivedObj->x = mouse.x;
    pDerivedObj->y = mouse.y;
    pDerivedObj->Ready = 0;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    //設定互動物件(貓)
    pObj->inter_obj[pObj->inter_len++] = CatT_L;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Capture_update;
    pObj->Interact = Capture_interact;
    pObj->Draw = Capture_draw;
    pObj->Destroy = Capture_destory;
    return pObj;
}

void Capture_update(Elements *self) {
    Capture *Obj = ((Capture *)(self->pDerivedObj));
    //檢測現在是否開啟捕捉模式
    if(key_state[ALLEGRO_KEY_C]){
        printf("Start Capturing\n");
        Obj->Ready = 1;
    }

    //根據滑鼠位置移動hitbox跟圖片
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, mouse.x - Obj->x);
    hitbox->update_center_y(hitbox, mouse.y - Obj->y);
    Obj->x = mouse.x;
    Obj->y = mouse.y;
}

void Capture_interact(Elements *self, Elements *tar) {
    Capture *Obj = ((Capture *)(self->pDerivedObj));
    catT *tar_obj = ((catT *)(tar->pDerivedObj));
    if(mouse_state[1] && Obj->Ready){ //如果滑鼠按下的當下是開啟捕捉模式
        if(Obj->hitbox->overlap(Obj->hitbox, tar_obj->hitbox)){ //如果貓咪跟項圈的hitbox重疊 -> 抓到貓咪，數量++且貓咪消失
            printf("Catch a Cat!\n");
            CatNumber[0]++; //這邊以索引值0先代替
            Own[0] = true;
            Obj->Ready = 0; //抓完之後，項圈消失
            //在CatT.c裡面會設定讓貓咪消失
        }
        else{ //如果hitbox沒有重疊 -> 項圈消失
            printf("No Cat...\n");
            Obj->Ready = 0;
        }
    }
}

void Capture_draw(Elements *self)
{
    Capture *Obj = ((Capture *)(self->pDerivedObj));
    if(Obj->Ready){ //如果有開啟捕捉模式(按鍵c)
        al_draw_bitmap(Obj->Catch, Obj->x, Obj->y, 0);
    }
    
}
void Capture_destory(Elements *self)
{
    Capture *Obj = ((Capture *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->Catch);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
