#include <allegro5/allegro_primitives.h>
#include "menu.h"
#include <stdbool.h>
#define BUTTON_NUM 4
/*
   [Menu function]
*/

Scene *New_Menu(int label)
{
    Menu *pDerivedObj = (Menu *)malloc(sizeof(Menu));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 12, 0);
    
    pDerivedObj->background_image = al_load_bitmap("assets/image/start.png"); //【設定菜單背景(要跟遊戲視窗設定的大小相等，沒辦法縮放)】

    //【設定按鈕圖案】
    pDerivedObj->button[0] = al_load_bitmap("assets/image/button/startGame_d.png"); //開始
    pDerivedObj->button[1] = al_load_bitmap("assets/image/button/setting_d.png"); //設定
    pDerivedObj->button[2] = al_load_bitmap("assets/image/button/info_d.png"); //說明
    pDerivedObj->button[3] = al_load_bitmap("assets/image/button/quit_d.png"); //離開
    pDerivedObj->hightlight_button[0] = al_load_bitmap("assets/image/button/startGame_high.png");
    pDerivedObj->hightlight_button[1] = al_load_bitmap("assets/image/button/setting_high.png");
    pDerivedObj->hightlight_button[2] = al_load_bitmap("assets/image/button/info_high.png");
    pDerivedObj->hightlight_button[3] = al_load_bitmap("assets/image/button/quit_high.png");
    pDerivedObj->button_W = 200;
    pDerivedObj->button_H = 120;

    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/BGM.mp3");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.3);
    
    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = menu_update;
    pObj->Draw = menu_draw;
    pObj->Destroy = menu_destroy;
    return pObj;
}

void menu_update(Scene *self) //【菜單事件更新】
{
    Menu *Obj = ((Menu *)(self->pDerivedObj));
    DetectButtonOn(self);
    if (mouse_state[1]) //檢查滑鼠左鍵按下的當下是否在按鈕上
    {
        if(Obj->over_button[0]){ //進入遊戲(1)
            printf("Play\n");
            self->scene_end = true;
            window = 1;
        }
        if(Obj->over_button[1]){ //調整設定(2)
            printf("Set\n");
            self->scene_end = true;
            window = -1;//XX
        }
        if(Obj->over_button[2]){ //觀看說明(3)
            printf("read\n");
            self->scene_end = true;
            window = 3;
        }
        if(Obj->over_button[3]){ //關閉遊戲(4)
            //如果滑鼠按下的時候在按鈕上 -> 準備要離開
            printf("Quit\n");
            self->scene_end = true;
            window = 4;
        }
    }
    
    return;
}

void menu_draw(Scene *self) //【菜單內要被畫出的東西】
{
    Menu *Obj = ((Menu *)(self->pDerivedObj));
    printf("in menu: %d\n", al_get_bitmap_width(Obj->background_image));

    al_draw_bitmap(Obj->background_image, 0, 0, 0);
    //【在顯示選單按鈕前，先畫出背景才不會被覆蓋】
    //al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->title_x, Obj->title_y, ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to start");
    //al_draw_rectangle(Obj->title_x - 150, Obj->title_y - 30, Obj->title_x + 150, Obj->title_y + 30, al_map_rgb(255, 255, 255), 0);

    //【畫出四個按鈕】
    int increments = 50;
    for(int i = 0 ; i < BUTTON_NUM ; i++){
        Obj->X[i] = 350;
        Obj->Y[i] = increments;
        al_draw_bitmap(Obj->button[i], Obj->X[i], Obj->Y[i], 0);
        increments += 150;
    }

    DetectButtonOn(self); //畫完正常按鈕後，檢查滑鼠是否停在按鈕上，並更改狀態

    al_play_sample_instance(Obj->sample_instance);
}

void DetectButtonOn(Scene *self){

    Menu *Obj = ((Menu *)(self->pDerivedObj));
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

void menu_destroy(Scene *self)
{
    Menu *Obj = ((Menu *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background_image;
    al_destroy_bitmap(background); //【destory背景圖片(先宣告才能刪除)】
    al_destroy_bitmap(Obj->button[0]);
    al_destroy_bitmap(Obj->button[1]);
    al_destroy_bitmap(Obj->button[2]);
    al_destroy_bitmap(Obj->button[3]);
    al_destroy_bitmap(Obj->hightlight_button[0]);
    al_destroy_bitmap(Obj->hightlight_button[1]);
    al_destroy_bitmap(Obj->hightlight_button[2]);
    al_destroy_bitmap(Obj->hightlight_button[3]);
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    free(Obj);
    free(self);
}
