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
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;
 
    pDerivedObj->background_image = al_load_bitmap("assets/image/sad.png"); //【設定背景】

    //【設定按鈕圖案】
    pDerivedObj->button[0] = al_load_bitmap("assets/image/Menu/MenuBack.png"); //回到菜單
    pDerivedObj->hightlight_button[0] = al_load_bitmap("assets/image/Menu/MenuBack_H.png");
    pDerivedObj->button_W[0] = al_get_bitmap_width(pDerivedObj->button[0]);
    pDerivedObj->button_H[0] = al_get_bitmap_height(pDerivedObj->button[0]);
    pDerivedObj->buttonH_W[0] = al_get_bitmap_width(pDerivedObj->hightlight_button[0]);
    pDerivedObj->buttonH_H[0] = al_get_bitmap_height(pDerivedObj->hightlight_button[0]);

    pDerivedObj->button[1] = al_load_bitmap("assets/image/Menu/Leave.png"); //離開
    pDerivedObj->hightlight_button[1] = al_load_bitmap("assets/image/Menu/Leave_H.png");
    pDerivedObj->button_W[1] = al_get_bitmap_width(pDerivedObj->button[1]);
    pDerivedObj->button_H[1] = al_get_bitmap_height(pDerivedObj->button[1]);
    pDerivedObj->buttonH_W[1] = al_get_bitmap_width(pDerivedObj->hightlight_button[1]);
    pDerivedObj->buttonH_H[1] = al_get_bitmap_height(pDerivedObj->hightlight_button[1]);

    //設定按鈕位置
    int increase = 150;
    int adjust = 0;
    for(int i = 0 ; i < BUTTON_NUM ; i++){
        pDerivedObj->X[i] = increase;
        pDerivedObj->Y[i] = 700+adjust;

        pDerivedObj->XH[i] = increase-10;
        pDerivedObj->YH[i] = 700+adjust;

        increase += 700;
        adjust += 20;
    }

    //設定按鈕音效
    pDerivedObj->ButtonClick = al_load_sample("assets/sound/menu/leave_back_button.wav");
    al_reserve_samples(20);
    pDerivedObj->Click_sample_instance = al_create_sample_instance(pDerivedObj->ButtonClick);
    al_set_sample_instance_playmode(pDerivedObj->Click_sample_instance, ALLEGRO_PLAYMODE_ONCE);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->Click_sample_instance, al_get_default_mixer());
    //設定音效音量
    al_set_sample_instance_gain(pDerivedObj->Click_sample_instance, 1);

    pObj->pDerivedObj = pDerivedObj;

    //一進來初始化先把滑鼠點擊狀態清空
    mouse_state[1] = false;

    pDerivedObj->click = 0;

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
            al_play_sample_instance(Obj->Click_sample_instance);
            printf("From quit back to menu\n");
            Obj->click = 1;
        }
        if(Obj->over_button[1]){ //離開遊戲
            printf("Finish quit\n");
            //讓事件更新回到讀取新的event時，可以跳出主要的game loop
            Obj->click = 1;
        }
    }
    else{
        if(Obj->over_button[0] && Obj->click){ //回到主畫面
            self->scene_end = true;
            window = 0;
        }
        if(Obj->over_button[1] && Obj->click){ //離開遊戲
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

    //依照狀態畫出四個按鈕
    Leave_DetectButtonOn(self);

}

void Leave_DetectButtonOn(Scene *self){

    Leave *Obj = ((Leave *)(self->pDerivedObj));
    for(int i = 0 ; i < BUTTON_NUM ; i++){
        if((mouse.x >= Obj->X[i])&&(mouse.x <= Obj->X[i]+Obj->button_W[i])&&(mouse.y >= Obj->Y[i])&&(mouse.y <= Obj->Y[i]+Obj->button_H[i])){ //如果滑鼠在按鈕範圍內
            al_draw_bitmap(Obj->hightlight_button[i], Obj->XH[i], Obj->YH[i], 0);
            Obj->over_button[i] = true;
        }
        else{
            al_draw_bitmap(Obj->button[i], Obj->X[i], Obj->Y[i], 0);
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
    al_destroy_sample(Obj->ButtonClick);
    al_destroy_sample_instance(Obj->Click_sample_instance);
    free(Obj);
    free(self);
}
