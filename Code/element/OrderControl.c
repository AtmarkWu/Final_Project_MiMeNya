#include "OrderControl.h"
#include "../shapes/Rectangle.h"
/*
   [OrderControl function]
*/
Elements *New_OrderControl(int label)
{
    OrderControl *pDerivedObj = (OrderControl *)malloc(sizeof(OrderControl));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    //設定背景圖片
    pDerivedObj->background = al_load_bitmap("assets/image/Order/orderBG.png");

    //回到遊戲主畫面的按鈕設定
    pDerivedObj->button = al_load_bitmap("assets/image/GameButton/back.png");
    pDerivedObj->highlight = al_load_bitmap("assets/image/GameButton/back_h.png");
    pDerivedObj->width = 74;
    pDerivedObj->height = 69;

    

    //一進來初始化先把滑鼠點擊狀態清空
    mouse_state[1] = false;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = OrderControl_update;
    pObj->Interact = OrderControl_interact;
    pObj->Draw = OrderControl_draw;
    pObj->Destroy = OrderControl_destory;
    return pObj;
}

void OrderControl_update(Elements *self) {
    if(gameFunction == 2){ //如果是現在是開啟訂單功能，再去做裡面的相關感應
        OrderControl *Obj = ((OrderControl *)(self->pDerivedObj));
        Order_DetectButtonOn(self);
        //滑鼠點擊事件更新
        if(mouse_state[1]){
            if(Obj->over_button){
                printf("Back to game\n");
                gameFunction = -1; //回到遊戲內畫面
            }
        }
    }


}

void OrderControl_interact(Elements *self, Elements *tar) {
}

void OrderControl_draw(Elements *self)
{
    if(gameFunction == 2){ //如果現在gameFunction是訂單功能開啟
        OrderControl *Obj = ((OrderControl *)(self->pDerivedObj));
        al_draw_bitmap(Obj->background, 0, 0, 0); //畫出背景
        printf("in order function: %d, gameFunction = %d\n", al_get_bitmap_width(Obj->background), gameFunction);

        //畫出按鈕並開啟回主畫面的按鈕感應功能
        Obj->x = 800;
        Obj->y = 30;
        al_draw_bitmap(Obj->button, Obj->x, Obj->y, 0);

        Order_DetectButtonOn(self);
    }
    
}

//內部OrderControl要使用的函式
void Order_DetectButtonOn(Elements *self){
    OrderControl *Obj = ((OrderControl *)(self->pDerivedObj));
    if((mouse.x >= Obj->x)&&(mouse.x <= Obj->x+Obj->width)&&(mouse.y >= Obj->y)&&(mouse.y <= Obj->y+Obj->height)){ //如果滑鼠在按鈕範圍內
        al_draw_bitmap(Obj->highlight, Obj->x-10, Obj->y-5, 0);
        Obj->over_button = true;
    }
    else{
        Obj->over_button = false;
    }
}



void OrderControl_destory(Elements *self)
{
    OrderControl *Obj = ((OrderControl *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);

    al_destroy_bitmap(Obj->button);
    al_destroy_bitmap(Obj->highlight);


    free(Obj);
    free(self);
}
