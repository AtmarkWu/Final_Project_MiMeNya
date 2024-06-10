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
    //字體設定(未使用)
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 12, 0);
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;
    
    pDerivedObj->background_image = al_load_bitmap("assets/image/start.png"); //【設定菜單背景(要跟遊戲視窗設定的大小相等，沒辦法縮放)】

    //【設定按鈕圖案】
    pDerivedObj->button[0] = al_load_bitmap("assets/image/Menu/Start.png"); //開始
    pDerivedObj->hightlight_button[0] = al_load_bitmap("assets/image/Menu/Start_H.png");
    pDerivedObj->button_W[0] = al_get_bitmap_width(pDerivedObj->button[0]);
    pDerivedObj->button_H[0] = al_get_bitmap_height(pDerivedObj->button[0]);
    pDerivedObj->buttonH_W[0] = al_get_bitmap_width(pDerivedObj->hightlight_button[0]);
    pDerivedObj->buttonH_H[0] = al_get_bitmap_height(pDerivedObj->hightlight_button[0]);


    pDerivedObj->button[1] = al_load_bitmap("assets/image/Menu/Setting.png"); //設定
    pDerivedObj->hightlight_button[1] = al_load_bitmap("assets/image/Menu/Setting_H.png");
    pDerivedObj->button_W[1] = al_get_bitmap_width(pDerivedObj->button[1]);
    pDerivedObj->button_H[1] = al_get_bitmap_height(pDerivedObj->button[1]);
    pDerivedObj->buttonH_W[1] = al_get_bitmap_width(pDerivedObj->hightlight_button[1]);
    pDerivedObj->buttonH_H[1] = al_get_bitmap_height(pDerivedObj->hightlight_button[1]);

    pDerivedObj->button[2] = al_load_bitmap("assets/image/Menu/About.png"); //說明
    pDerivedObj->hightlight_button[2] = al_load_bitmap("assets/image/Menu/About_H.png");    
    pDerivedObj->button_W[2] = al_get_bitmap_width(pDerivedObj->button[2]);
    pDerivedObj->button_H[2] = al_get_bitmap_height(pDerivedObj->button[2]);
    pDerivedObj->buttonH_W[2] = al_get_bitmap_width(pDerivedObj->hightlight_button[2]);
    pDerivedObj->buttonH_H[2] = al_get_bitmap_height(pDerivedObj->hightlight_button[2]);

    pDerivedObj->button[3] = al_load_bitmap("assets/image/Menu/Quit.png"); //離開
    pDerivedObj->hightlight_button[3] = al_load_bitmap("assets/image/Menu/Quit_H.png");
    pDerivedObj->button_W[3] = al_get_bitmap_width(pDerivedObj->button[3]);
    pDerivedObj->button_H[3] = al_get_bitmap_height(pDerivedObj->button[3]);
    pDerivedObj->buttonH_W[3] = al_get_bitmap_width(pDerivedObj->hightlight_button[3]);
    pDerivedObj->buttonH_H[3] = al_get_bitmap_height(pDerivedObj->hightlight_button[3]);

    //設定按鈕放置位置
    int increase = 330;
    for(int i = 0 ; i < BUTTON_NUM ; i++){
        pDerivedObj->X[i] = (WIDTH/2) - (pDerivedObj->button_W[i]/2); //X軸置中放置
        pDerivedObj->Y[i] = increase;

        pDerivedObj->XH[i] = (WIDTH/2) - (pDerivedObj->buttonH_W[i]/2); //X軸置中放置
        pDerivedObj->YH[i] = increase-5;

        increase += 180;
    }

    //設定按鈕音效
    pDerivedObj->ButtonClick = al_load_sample("assets/sound/button_press_sound.wav");
    al_reserve_samples(20);
    pDerivedObj->Click_sample_instance = al_create_sample_instance(pDerivedObj->ButtonClick);
    al_set_sample_instance_playmode(pDerivedObj->Click_sample_instance, ALLEGRO_PLAYMODE_ONCE);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->Click_sample_instance, al_get_default_mixer());
    //設定音效音量
    al_set_sample_instance_gain(pDerivedObj->Click_sample_instance, 1);

    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/menu/menu.wav");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_ONCE);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.3);
    al_play_sample_instance(pDerivedObj->sample_instance); //放在這裡的話，在還沒有跳轉頁面之前，只會發出一次聲音
    pObj->pDerivedObj = pDerivedObj;

    //一進來初始化先把滑鼠點擊狀態清空
    mouse_state[1] = false;

    pDerivedObj->click = 0;

    pDerivedObj->timerF = 0; //時間歸零

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
    if (mouse_state[1] && (window == 0)) //檢查滑鼠左鍵按下的當下是否在按鈕上(且在主選單的介面)
    {
        if(Obj->over_button[0]){ //進入遊戲(1)
            al_play_sample_instance(Obj->Click_sample_instance);
            printf("Play\n");
            Obj->click = 1;
        }
        if(Obj->over_button[1]){ //調整設定(2)
            al_play_sample_instance(Obj->Click_sample_instance);
            printf("Set\n");
            Obj->click = 1;
        }
        if(Obj->over_button[2]){ //觀看說明(3)
            al_play_sample_instance(Obj->Click_sample_instance);
            printf("read\n");
            Obj->click = 1;
        }
        if(Obj->over_button[3]){ //關閉遊戲(4)
            //如果滑鼠按下的時候在按鈕上 -> 準備要離開
            al_play_sample_instance(Obj->Click_sample_instance);
            printf("Quit\n");
            Obj->click = 1;
        }
    }
    else{
        if(Obj->over_button[0] && Obj->click){ //進入遊戲(1)
            self->scene_end = true;
            window = 1;
        }
        if(Obj->over_button[1] && Obj->click){ //調整設定(2)
            self->scene_end = true;
            window = 2;
        }
        if(Obj->over_button[2] && Obj->click){ //觀看說明(3)
            self->scene_end = true;
            window = 3;
        }
        if(Obj->over_button[3] && Obj->click){ //關閉遊戲(4)
            self->scene_end = true;
            window = 4;
        }
    }
    
    return;
}

void menu_draw(Scene *self) //【菜單內要被畫出的東西】
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    Menu *Obj = ((Menu *)(self->pDerivedObj));
    printf("in menu: %d\n", al_get_bitmap_width(Obj->background_image));

    al_draw_bitmap(Obj->background_image, 0, 0, 0);

    //依照狀態畫出四個按鈕
    DetectButtonOn(self);

}

void DetectButtonOn(Scene *self){ //檢查滑鼠是否停在按鈕上，並畫出對應狀態的圖案

    Menu *Obj = ((Menu *)(self->pDerivedObj));
    for(int i = 0 ; i < BUTTON_NUM ; i++){
        if((mouse.x >= Obj->X[i])&&(mouse.x <= Obj->X[i]+Obj->button_W[i])&&(mouse.y >= Obj->Y[i])&&(mouse.y <= Obj->Y[i]+Obj->button_H[i])){ //如果滑鼠在按鈕範圍內 -> 畫出highlight樣式
            al_draw_bitmap(Obj->hightlight_button[i], Obj->XH[i], Obj->YH[i], 0);
            Obj->over_button[i] = true;
        }
        else{ //如果滑鼠不在按鈕範圍內 -> 畫出普通樣式
            al_draw_bitmap(Obj->button[i], Obj->X[i], Obj->Y[i], 0);
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
    al_destroy_sample(Obj->ButtonClick);
    al_destroy_sample_instance(Obj->Click_sample_instance);
    free(Obj);
    free(self);
}
