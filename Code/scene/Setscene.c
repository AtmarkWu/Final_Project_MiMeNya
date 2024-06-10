#include <allegro5/allegro_primitives.h>
#include "Setscene.h"
#include <stdbool.h>
#define MODENUM 3
/*
   [Setting function]
*/
Scene *New_Setting(int label)
{
    Setting *pDerivedObj = (Setting *)malloc(sizeof(Setting));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/GenSenRounded-M.ttc", 24, 0);
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;

    pDerivedObj->background_image = al_load_bitmap("assets/image/SetTest.png"); //設定背景

    //【設定按鈕圖案】
    pDerivedObj->button[0] = al_load_bitmap("assets/image/Menu/On.png"); //On
    pDerivedObj->hightlight_button[0] = al_load_bitmap("assets/image/Menu/On_H.png");
    pDerivedObj->button_W[0] = al_get_bitmap_width(pDerivedObj->button[0]);
    pDerivedObj->button_H[0] = al_get_bitmap_height(pDerivedObj->button[0]);
    pDerivedObj->buttonH_W[0] = al_get_bitmap_width(pDerivedObj->hightlight_button[0]);
    pDerivedObj->buttonH_H[0] = al_get_bitmap_height(pDerivedObj->hightlight_button[0]);

    pDerivedObj->button[1] = al_load_bitmap("assets/image/Menu/Off.png"); //Off
    pDerivedObj->hightlight_button[1] = al_load_bitmap("assets/image/Menu/Off_H.png");
    pDerivedObj->button_W[1] = al_get_bitmap_width(pDerivedObj->button[1]);
    pDerivedObj->button_H[1] = al_get_bitmap_height(pDerivedObj->button[1]);
    pDerivedObj->buttonH_W[1] = al_get_bitmap_width(pDerivedObj->hightlight_button[1]);
    pDerivedObj->buttonH_H[1] = al_get_bitmap_height(pDerivedObj->hightlight_button[1]);

    pDerivedObj->backbutton = al_load_bitmap("assets/image/Menu/BackIconClose.png"); //back
    pDerivedObj->highlight_backbutton = al_load_bitmap("assets/image/Menu/BackIconOpen.png");
    pDerivedObj->backbutton_W = al_get_bitmap_width(pDerivedObj->backbutton);
    pDerivedObj->backbutton_H = al_get_bitmap_height(pDerivedObj->backbutton);
    pDerivedObj->backbuttonH_W = al_get_bitmap_width(pDerivedObj->highlight_backbutton);
    pDerivedObj->backbuttonH_H = al_get_bitmap_height(pDerivedObj->highlight_backbutton);

    //設定按鈕放置位置(3種模式所以3個)
    int increase = 150;
    for(int i = 0 ; i < MODENUM ; i++){
        pDerivedObj->X[i] = 800;
        pDerivedObj->Y[i] = increase;
        pDerivedObj->XH[i] = 800;
        pDerivedObj->YH[i] = increase-10;

        increase += 300;
    }
    //回到菜單的按鈕位置設定
    pDerivedObj->backX = 1250;
    pDerivedObj->backY = 50;
    pDerivedObj->backXH = 1250;
    pDerivedObj->backYH = 50;

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
    pObj->Update = Setting_update;
    pObj->Draw = Setting_draw;
    pObj->Destroy = Setting_destroy;
    return pObj;
}

void Setting_update(Scene *self) //【事件更新】
{
    Setting *Obj = ((Setting *)(self->pDerivedObj));
    Setting_DetectButtonOn(self);
    if (mouse_state[1]) //檢查滑鼠左鍵按下的當下是否在按鈕上
    {
        if(Obj->over_button[0]){ //開啟第一模式，其他兩個模式自動關閉
            al_play_sample_instance(Obj->Click_sample_instance);
            ModeCondition[0] = true;
            ModeCondition[1] = false;
            ModeCondition[2] = false;
        }
        if(Obj->over_button[1]){ //開啟第二模式，其他兩個模式自動關閉
            al_play_sample_instance(Obj->Click_sample_instance);
            ModeCondition[0] = false;
            ModeCondition[1] = true;
            ModeCondition[2] = false;
        }
        if(Obj->over_button[2]){ //開啟第三模式，其他兩個模式自動關閉
            al_play_sample_instance(Obj->Click_sample_instance);
            ModeCondition[0] = false;
            ModeCondition[1] = false;
            ModeCondition[2] = true;
        }

        if(Obj->over_backbutton){
            al_play_sample_instance(Obj->Click_sample_instance);
            printf("Back to menu\n");
            Obj->click = 1;
        }
    }
    else{
        if(Obj->over_backbutton && Obj->click){
            self->scene_end = true;
            window = 0;
        }
    }
    
    return;
}

void Setting_draw(Scene *self) //【菜單內要被畫出的東西】
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    Setting *Obj = ((Setting *)(self->pDerivedObj));
    printf("in Setting: %d\n", al_get_bitmap_width(Obj->background_image));

    al_draw_bitmap(Obj->background_image, 0, 0, 0); //【先畫出背景才不會被覆蓋】


    Setting_DetectButtonOn(self); //畫完正常按鈕後，檢查滑鼠是否停在按鈕上，並更改狀態
}

void Setting_DetectButtonOn(Scene *self){
    Setting *Obj = ((Setting *)(self->pDerivedObj));
    for(int i = 0 ; i < MODENUM ; i++){
        if((mouse.x >= Obj->X[i])&&(mouse.x <= Obj->X[i]+Obj->button_W[i])&&(mouse.y >= Obj->Y[i])&&(mouse.y <= Obj->Y[i]+Obj->button_H[i])){ //如果滑鼠在按鈕範圍內
            if(ModeCondition[i]){ //根據這個模式的狀態是on/off來決定畫出來的按鈕
                //是On -> 畫出On的highlight樣式
                al_draw_bitmap(Obj->hightlight_button[0], Obj->XH[i], Obj->YH[i], 0);
                Obj->over_button[i] = true;
            }
            else{
                //是Off -> 畫出Off的highlight樣式
                al_draw_bitmap(Obj->hightlight_button[1], Obj->XH[i], Obj->YH[i], 0);
                Obj->over_button[i] = true;
            }
        }
        else{
            if(ModeCondition[i]){ //根據這個模式的狀態是on/off來決定畫出來的按鈕
                //是On -> 畫出On的highlight樣式
                al_draw_bitmap(Obj->button[0], Obj->X[i], Obj->Y[i], 0);
                Obj->over_button[i] = false;
            }
            else{
                //是Off -> 畫出Off的highlight樣式
                al_draw_bitmap(Obj->button[1], Obj->X[i], Obj->Y[i], 0);
                Obj->over_button[i] = false;
            }
        }
    }

    if((mouse.x >= Obj->backX)&&(mouse.x <= Obj->backX+Obj->backbutton_W)&&(mouse.y >= Obj->backY)&&(mouse.y <= Obj->backY+Obj->backbutton_H)){ //如果滑鼠在按鈕範圍內
        al_draw_bitmap(Obj->highlight_backbutton, Obj->backXH, Obj->backYH, 0);
        Obj->over_backbutton = true;
    }
    else{
        al_draw_bitmap(Obj->backbutton, Obj->backX, Obj->backY, 0);
        Obj->over_backbutton = false;
    }

}

void Setting_destroy(Scene *self)
{
    Setting *Obj = ((Setting *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background_image;
    al_destroy_bitmap(background); //【destory背景圖片(先宣告才能刪除)】
    al_destroy_bitmap(Obj->button[0]);
    al_destroy_bitmap(Obj->hightlight_button[0]);
    al_destroy_bitmap(Obj->button[1]);
    al_destroy_bitmap(Obj->hightlight_button[1]);
    al_destroy_bitmap(Obj->backbutton);
    al_destroy_bitmap(Obj->highlight_backbutton);
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->ButtonClick);
    al_destroy_sample_instance(Obj->Click_sample_instance);
    free(Obj);
    free(self);
}
