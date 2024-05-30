#include <allegro5/allegro_primitives.h>
#include "leave.h"
#include <stdbool.h>
#define BUTTON_NUM 2
/*
   [Leave function]
*/

Scene *New_Leave(int label)
{
    Leave *pDerivedObj = (Leave *)malloc(sizeof(Leave));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/XiaolaiMonoSC-Regular.ttf", 24, 0);
    
    pDerivedObj->background_image = al_load_bitmap("assets/image/sad.png"); //【設定背景】

    //【設定按鈕圖案】
    pDerivedObj->button[0] = al_load_bitmap("assets/image/button/back.png"); //開始
    pDerivedObj->button[1] = al_load_bitmap("assets/image/button/leave.png"); //設定
    pDerivedObj->hightlight_button[0] = al_load_bitmap("assets/image/button/back_high.png");
    pDerivedObj->hightlight_button[1] = al_load_bitmap("assets/image/button/leave_high.png");
    pDerivedObj->button_W = 200;
    pDerivedObj->button_H = 120;

    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;

    pObj->pDerivedObj = pDerivedObj;

    //一進來初始化先把滑鼠點擊狀態清空
    mouse_state[1] = false;

    // setting derived object function
    pObj->Update = Leave_update;
    pObj->Draw = Leave_draw;
    pObj->Destroy = Leave_destroy;
    return pObj;
}

void Leave_update(Scene *self) //【菜單事件更新】
{
    Leave *Obj = ((Leave *)(self->pDerivedObj));
    Leave_DetectButtonOn(self);
    if (mouse_state[1]) //檢查滑鼠左鍵按下的當下是否在按鈕上
    {
        if(Obj->over_button[0]){ //回到主畫面
            printf("From quit back to menu\n");
            self->scene_end = true;
            window = 0;
        }
        if(Obj->over_button[1]){ //離開遊戲
            printf("Finish quit\n");
            CloseGame = 1;
            //讓事件更新回到讀取新的event時，可以跳出主要的game loop
        }
    }

    return;
}

void Leave_draw(Scene *self) //【菜單內要被畫出的東西】
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    Leave *Obj = ((Leave *)(self->pDerivedObj));
    printf("in leave: %d\n", al_get_bitmap_width(Obj->background_image));

    al_draw_bitmap(Obj->background_image, 0, 0, 0);
    //【在顯示選單按鈕前，先畫出背景才不會被覆蓋】

    al_draw_filled_rectangle(Obj->title_x - 300, Obj->title_y - 50, Obj->title_x + 300, Obj->title_y + 50, al_map_rgb(255, 255, 255));
    al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->title_x, Obj->title_y, ALLEGRO_ALIGN_CENTRE, "Are you sure you are going to leave?");

    //【畫出兩個按鈕】
    int increments = 100;
    for(int i = 0 ; i < BUTTON_NUM ; i++){
        Obj->X[i] = increments;
        Obj->Y[i] = 500;
        al_draw_bitmap(Obj->button[i], Obj->X[i], Obj->Y[i], 0);
        increments += 500;
    }

    Leave_DetectButtonOn(self); //畫完正常按鈕後，檢查滑鼠是否停在按鈕上，並更改狀態

}

void Leave_DetectButtonOn(Scene *self){

    Leave *Obj = ((Leave *)(self->pDerivedObj));
    for(int i = 0 ; i < BUTTON_NUM ; i++){
        if((mouse.x >= Obj->X[i])&&(mouse.x <= Obj->X[i]+Obj->button_W)&&(mouse.y >= Obj->Y[i])&&(mouse.y <= Obj->Y[i]+Obj->button_H)){ //如果滑鼠在按鈕範圍內
            al_draw_bitmap(Obj->hightlight_button[i], Obj->X[i], Obj->Y[i], 0);
            Obj->over_button[i] = true;
        }
        else{
            Obj->over_button[i] = false;
        }
    }
}

void Leave_destroy(Scene *self)
{
    Leave *Obj = ((Leave *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background_image;
    al_destroy_bitmap(background); //【destory背景圖片(先宣告才能刪除)】
    al_destroy_bitmap(Obj->button[0]);
    al_destroy_bitmap(Obj->button[1]);
    al_destroy_bitmap(Obj->hightlight_button[0]);
    al_destroy_bitmap(Obj->hightlight_button[1]);
    al_destroy_font(Obj->font);
    free(Obj);
    free(self);
}
