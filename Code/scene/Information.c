#include <allegro5/allegro_primitives.h>
#include "Information.h"
#include <stdbool.h>
/*
   [Info function]
*/
Scene *New_Info(int label)
{
    Info *pDerivedObj = (Info *)malloc(sizeof(Info));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/GenSenRounded-M.ttc", 24, 0);
    pDerivedObj->background_image = al_load_bitmap("assets/image/info.png"); //【設定背景(要跟遊戲視窗設定的大小相等，沒辦法縮放)】

    //【設定按鈕圖案】
    pDerivedObj->button = al_load_bitmap("assets/image/button_test.png"); //開始
    pDerivedObj->hightlight_button = al_load_bitmap("assets/image/button_test.png");
    pDerivedObj->button_W = 120;
    pDerivedObj->button_H = 120;

    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/BGM.mp3"); //未改，待加入新音樂

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
    pObj->Update = Info_update;
    pObj->Draw = Info_draw;
    pObj->Destroy = Info_destroy;
    return pObj;
}

void Info_update(Scene *self) //【事件更新】
{
    Info *Obj = ((Info *)(self->pDerivedObj));
    Info_DetectButtonOn(self);
    if (mouse_state[1]) //檢查滑鼠左鍵按下的當下是否在按鈕上
    {
        if(Obj->over_button){ //回到主選單(0)
            printf("back to menu\n");
            self->scene_end = true;
            window = 0;
        }
    }
    
    return;
}

void Info_draw(Scene *self) //【菜單內要被畫出的東西】
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    Info *Obj = ((Info *)(self->pDerivedObj));
    printf("in Info: %d\n", al_get_bitmap_width(Obj->background_image));

    al_draw_bitmap(Obj->background_image, 0, 0, 0); //【先畫出背景才不會被覆蓋】

    al_draw_filled_rectangle(Obj->title_x - 200, Obj->title_y - 250, Obj->title_x + 200, Obj->title_y + 250, al_map_rgb(250, 235, 215));
    al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->title_x, Obj->title_y-30, ALLEGRO_ALIGN_CENTER, "This is the cutest game");
    al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->title_x, Obj->title_y+30, ALLEGRO_ALIGN_CENTER, "IN THE WORLD !");
    al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->title_x, Obj->title_y+100, ALLEGRO_ALIGN_CENTER, "咪");

    //【畫出按鈕】
    int increments = 30;
    Obj->X[0] = 750;
    Obj->Y[0] = increments;
    al_draw_bitmap(Obj->button, Obj->X[0], Obj->Y[0], 0);
    
    Info_DetectButtonOn(self); //畫完正常按鈕後，檢查滑鼠是否停在按鈕上，並更改狀態

    al_play_sample_instance(Obj->sample_instance);
}

void Info_DetectButtonOn(Scene *self){
    Info *Obj = ((Info *)(self->pDerivedObj));
    if((mouse.x >= Obj->X[0])&&(mouse.x <= Obj->X[0]+Obj->button_W)&&(mouse.y >= Obj->Y[0])&&(mouse.y <= Obj->Y[0]+Obj->button_H)){ //如果滑鼠在按鈕範圍內
        al_draw_bitmap(Obj->hightlight_button, Obj->X[0], Obj->Y[0], ALLEGRO_FLIP_VERTICAL);
        Obj->over_button = true;
    }
    else{
        Obj->over_button = false;
    }
}

void Info_destroy(Scene *self)
{
    Info *Obj = ((Info *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background_image;
    al_destroy_bitmap(background); //【destory背景圖片(先宣告才能刪除)】
    al_destroy_bitmap(Obj->button);
    al_destroy_bitmap(Obj->hightlight_button);
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    free(Obj);
    free(self);
}
