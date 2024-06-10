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
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;

    pDerivedObj->background_image = al_load_bitmap("assets/image/info.png"); //設定背景

    //【設定按鈕圖案】
    pDerivedObj->button = al_load_bitmap("assets/image/Menu/BackIconClose.png"); //回到菜單按鈕
    pDerivedObj->hightlight_button = al_load_bitmap("assets/image/Menu/BackIconOpen.png");
    pDerivedObj->button_W = al_get_bitmap_width(pDerivedObj->button);
    pDerivedObj->button_H = al_get_bitmap_height(pDerivedObj->button);
    pDerivedObj->buttonH_W = al_get_bitmap_width(pDerivedObj->hightlight_button);
    pDerivedObj->buttonH_H = al_get_bitmap_height(pDerivedObj->hightlight_button);

    //設定按鈕放置位置
    pDerivedObj->X = 1250;
    pDerivedObj->Y = 50;
    pDerivedObj->XH = 1245;
    pDerivedObj->YH = 50;

    //設定按鈕音效
    pDerivedObj->ButtonClick = al_load_sample("assets/sound/button_press_sound.wav");
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
            al_play_sample_instance(Obj->Click_sample_instance);
            printf("back to menu\n");
            Obj->click = 1;
        }
    }
    else{
         if(Obj->over_button && Obj->click){ //回到主選單(0)
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

    Info_DetectButtonOn(self); //畫完正常按鈕後，檢查滑鼠是否停在按鈕上，並更改狀態
}

void Info_DetectButtonOn(Scene *self){
    Info *Obj = ((Info *)(self->pDerivedObj));
    if((mouse.x >= Obj->X)&&(mouse.x <= Obj->X+Obj->button_W)&&(mouse.y >= Obj->Y)&&(mouse.y <= Obj->Y+Obj->button_H)){ //如果滑鼠在按鈕範圍內
        al_draw_bitmap(Obj->hightlight_button, Obj->XH, Obj->YH, 0);
        Obj->over_button = true;
    }
    else{
        al_draw_bitmap(Obj->button, Obj->X, Obj->Y, 0);
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
    al_destroy_sample_instance(Obj->Click_sample_instance);
    al_destroy_sample(Obj->ButtonClick);
    free(Obj);
    free(self);
}
