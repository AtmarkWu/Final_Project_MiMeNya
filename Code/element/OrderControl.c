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
    //Clients
    pDerivedObj->Client[0] = al_load_bitmap("assets/image/Order/Client1.png");
    pDerivedObj->Client[1] = al_load_bitmap("assets/image/Order/Client2.png");

    //回到遊戲主畫面的按鈕設定
    pDerivedObj->button = al_load_bitmap("assets/image/Order/BackIconClose.png");
    pDerivedObj->highlight = al_load_bitmap("assets/image/Order/BackIconOpen.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->button);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->button);
    pDerivedObj->x = 1250;
    pDerivedObj->y = 60;

    //accept button
    pDerivedObj->Accept = al_load_bitmap("assets/image/Order/Accept.png");
    pDerivedObj->Accept_highlight = al_load_bitmap("assets/image/Order/Accept_h.png");
    pDerivedObj->A_Width = al_get_bitmap_width(pDerivedObj->Accept);
    pDerivedObj->A_Height = al_get_bitmap_height(pDerivedObj->Accept);
    pDerivedObj->Accept_X = 400;
    pDerivedObj->Accept_Y = 800;

    //設定按鈕音效
    pDerivedObj->ButtonClick = al_load_sample("assets/sound/button_press_sound.wav");
    al_reserve_samples(20);
    pDerivedObj->Click_sample_instance = al_create_sample_instance(pDerivedObj->ButtonClick);
    al_set_sample_instance_playmode(pDerivedObj->Click_sample_instance, ALLEGRO_PLAYMODE_ONCE);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->Click_sample_instance, al_get_default_mixer());
    //設定音效音量
    al_set_sample_instance_gain(pDerivedObj->Click_sample_instance, 1);

    //設定賺錢音效
    pDerivedObj->Cashin = al_load_sample("assets/sound/shop/money.wav");
    al_reserve_samples(20);
    pDerivedObj->Cashin_sample_instance = al_create_sample_instance(pDerivedObj->Cashin);
    al_set_sample_instance_playmode(pDerivedObj->Cashin_sample_instance, ALLEGRO_PLAYMODE_ONCE);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->Cashin_sample_instance, al_get_default_mixer());
    //設定音效音量
    al_set_sample_instance_gain(pDerivedObj->Cashin_sample_instance, 1);

    //一進來初始化先把滑鼠點擊狀態清空
    mouse_state[1] = false;

    pDerivedObj->click = 0;

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
                al_play_sample_instance(Obj->Click_sample_instance);
                printf("Back to game\n");
                gameFunction = -1; //回到遊戲內畫面
            }

            if(Obj->over_Accept_button){
                if(CatNumber[1]>=1 && client_set == 1){ // 第一單
                    al_play_sample_instance(Obj->Cashin_sample_instance);
                    printf("accept client1\n");
                    Obj->click = 1;
                }
                else if(CatNumber[2]>=1 && client_set == 2){ // 第二單
                    al_play_sample_instance(Obj->Cashin_sample_instance);
                    printf("accept client2\n");
                    Obj->click = 1;
                }
                else{
                    al_play_sample_instance(Obj->Click_sample_instance);
                }
            }
        }
        else{
            if(Obj->over_Accept_button && Obj->click){
                if(CatNumber[1]>=1 && client_set == 1){ // 第一單
                    client_set ++;
                    gameFunction = -1; //回到遊戲內畫面
                    TotalMoney += 100;
                    CatNumber[1] -= 1;
                    TotalOwnCat--;
                }
                else if(CatNumber[2]>=1 && client_set == 2){ // 第二單
                    client_set ++;
                    gameFunction = -1; //回到遊戲內畫面
                    TotalMoney += 150;
                    CatNumber[2] -= 1;
                    TotalOwnCat--;
                }
            }
            Obj->click = 0;
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

        al_draw_bitmap(Obj->Client[client_set-1], 220, 160, 0); //畫出背景

        //畫出按鈕並開啟回主畫面的按鈕感應功能
        //畫出接單按鈕
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
        al_draw_bitmap(Obj->button, Obj->x, Obj->y, 0);
        Obj->over_button = false;
    }

    //accept button
    if((mouse.x >= Obj->Accept_X)&&(mouse.x <= Obj->Accept_X+Obj->A_Width)&&(mouse.y >= Obj->Accept_Y)&&(mouse.y <= Obj->Accept_Y+Obj->A_Height)){ //如果滑鼠在按鈕範圍內
        al_draw_bitmap(Obj->Accept_highlight, Obj->Accept_X-10, Obj->Accept_Y-5, 0);
        Obj->over_Accept_button = true;
    }
    else{
        al_draw_bitmap(Obj->Accept, Obj->Accept_X, Obj->Accept_Y, 0);
        Obj->over_Accept_button = false;
    }
}



void OrderControl_destory(Elements *self)
{
    OrderControl *Obj = ((OrderControl *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
    al_destroy_bitmap(Obj->Client[0]);
    al_destroy_bitmap(Obj->Client[1]);

    al_destroy_bitmap(Obj->button);
    al_destroy_bitmap(Obj->highlight);

    al_destroy_bitmap(Obj->Accept);
    al_destroy_bitmap(Obj->Accept_highlight);

    al_destroy_sample(Obj->ButtonClick);
    al_destroy_sample_instance(Obj->Click_sample_instance);

    al_destroy_sample(Obj->Cashin);
    al_destroy_sample_instance(Obj->Cashin_sample_instance);

    free(Obj);
    free(self);
}
