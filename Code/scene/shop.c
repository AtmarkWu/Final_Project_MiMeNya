#include <allegro5/allegro_primitives.h>
#include "shop.h"
#include <stdbool.h>
#define BUTTON_NUM 3
/*
   [Shop function]
*/

Scene *New_Shop(int label)
{
    Shop *pDerivedObj = (Shop *)malloc(sizeof(Shop));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 12, 0);
    
    pDerivedObj->background_image = al_load_bitmap("assets/image/Shop/BG/shopBG.png"); //設定商店背景

    //【設定3種肉泥圖案】
    pDerivedObj->button[0] = al_load_bitmap("assets/image/Shop/item/Meat1-3.png"); //meat1
    pDerivedObj->button[1] = al_load_bitmap("assets/image/Shop/item/Meat2-3.png"); //meat2
    pDerivedObj->button[2] = al_load_bitmap("assets/image/Shop/item/Meat3-3.png"); //meat3
    // pDerivedObj->button[3] = al_load_bitmap("assets/image/button/quit_d.png");//meat4
    pDerivedObj->hightlight_button[0] = al_load_bitmap("assets/image/Shop/item/Meat1-3_high.png");
    pDerivedObj->hightlight_button[1] = al_load_bitmap("assets/image/Shop/item/Meat2-3_high.png");
    pDerivedObj->hightlight_button[2] = al_load_bitmap("assets/image/Shop/item/Meat3-3_high.png");
    // pDerivedObj->hightlight_button[3] = al_load_bitmap("assets/image/button/quit_high.png");
    pDerivedObj->button_W = 200;
    pDerivedObj->button_H = 200;

    //back to gamescene
    pDerivedObj->back_button = al_load_bitmap("assets/image/GameButton/back.png"); 
    pDerivedObj->highlight_back_button = al_load_bitmap("assets/image/GameButton/back_h.png"); 
    pDerivedObj->back_button_W = 120;
    pDerivedObj->back_button_H = 120;

    pDerivedObj->Money = al_load_bitmap("assets/image/GameButton/money.png");

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
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 1);
    
    //一進來初始化先把滑鼠點擊狀態清空
    mouse_state[1] = false;

    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = shop_update;
    pObj->Draw = shop_draw;
    pObj->Destroy = shop_destroy;
    return pObj;
}

void shop_update(Scene *self) //【菜單事件更新】
{
    Shop *Obj = ((Shop *)(self->pDerivedObj));
    Shop_DetectButtonOn(self);
    if (mouse_state[1]) //檢查滑鼠左鍵按下的當下是否在按鈕上
    {
        if(Obj->over_button[0]){ //Meat1頁面
            printf("Meat1\n");
            which_food = 1;//記錄當前選擇
            printf("Chose food1\n");
            self->scene_end = true;
            window = 7;
        }
        if(Obj->over_button[1]){ //Meat2頁面
            printf("Meat2\n");
            which_food = 2;//記錄當前選擇
            printf("Chose food2\n");
            self->scene_end = true;
            window = 7;
        }
        if(Obj->over_button[2]){ //Meat3頁面
            printf("Meat3\n");
            which_food = 3;//記錄當前選擇
            printf("Chose food3\n");
            self->scene_end = true;
            window = 7;
        }
        // if(Obj->over_button[3]){ //Meat4頁面
        //     printf("Meat4\n");
        //     which_food = 4;//記錄當前選擇
        //     self->scene_end = true;
        //     window = 7;
        // }

        if(Obj->over_back_button){//回到gamescene
            printf("Back to game\n");
            self->scene_end = true;
            window = 1;

        }
    }
    
    return;
}

void shop_draw(Scene *self) //【菜單內要被畫出的東西】
{
    Shop *Obj = ((Shop *)(self->pDerivedObj));
    printf("in shop: %d\n", al_get_bitmap_width(Obj->background_image));

    al_draw_bitmap(Obj->background_image, 0, 0, 0);
    //【在顯示選單按鈕前，先畫出背景才不會被覆蓋】
    //al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->title_x, Obj->title_y, ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to start");
    //al_draw_rectangle(Obj->title_x - 150, Obj->title_y - 30, Obj->title_x + 150, Obj->title_y + 30, al_map_rgb(255, 255, 255), 0);

    //【畫出3個按鈕】
    int increments = 50;
    for(int i = 0 ; i < BUTTON_NUM ; i++){
        Obj->X[i] = increments;
        Obj->Y[i] = 450;
        al_draw_bitmap(Obj->button[i], Obj->X[i], Obj->Y[i], 0);
        increments += 300;
    }
    //【畫出Back按鈕】
    Obj->back_button_X = 805;
    Obj->back_button_Y = 30;
    al_draw_bitmap(Obj->back_button, Obj->back_button_X, Obj->back_button_Y, 0);

    //畫出金錢條&上面的數字(固定)
    al_draw_bitmap(Obj->Money, 40, 20, 0);
    // int money = 10000;
    al_draw_text(Obj->font, al_map_rgb(0, 0, 0), 50, 75, ALLEGRO_ALIGN_LEFT, "10000");

    Shop_DetectButtonOn(self); //畫完正常按鈕後，檢查滑鼠是否停在按鈕上，並更改狀態

    al_play_sample_instance(Obj->sample_instance);
}

void Shop_DetectButtonOn(Scene *self){

    Shop *Obj = ((Shop *)(self->pDerivedObj));
    for(int i = 0 ; i < BUTTON_NUM ; i++){
        if((mouse.x >= Obj->X[i])&&(mouse.x <= Obj->X[i]+Obj->button_W)&&(mouse.y >= Obj->Y[i])&&(mouse.y <= Obj->Y[i]+Obj->button_H)){ //如果滑鼠在按鈕範圍內
            al_draw_bitmap(Obj->hightlight_button[i], Obj->X[i]-15, Obj->Y[i]-10, 0);
            printf("on button[%d]\n", i);
            Obj->over_button[i] = true;
        }
        else{
            Obj->over_button[i] = false;
        }
    }

    if((mouse.x >= Obj->back_button_X)&&(mouse.x <= Obj->back_button_X+Obj->back_button_W)&&(mouse.y >= Obj->back_button_Y)&&(mouse.y <= Obj->back_button_Y+Obj->back_button_H)){ //如果滑鼠在按鈕範圍內
            al_draw_bitmap(Obj->highlight_back_button, Obj->back_button_X-10, Obj->back_button_Y, 0);
            Obj->over_back_button = true;
    }
    else{
        Obj->over_back_button = false;
    }
}

void shop_destroy(Scene *self)
{
    Shop *Obj = ((Shop *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background_image;
    al_destroy_bitmap(background); //【destory背景圖片(先宣告才能刪除)】
    al_destroy_bitmap(Obj->button[0]);
    al_destroy_bitmap(Obj->button[1]);
    al_destroy_bitmap(Obj->button[2]);
    // al_destroy_bitmap(Obj->button[3]);
    al_destroy_bitmap(Obj->hightlight_button[0]);
    al_destroy_bitmap(Obj->hightlight_button[1]);
    al_destroy_bitmap(Obj->hightlight_button[2]);
    // al_destroy_bitmap(Obj->hightlight_button[3]);

    al_destroy_bitmap(Obj->back_button);
    al_destroy_bitmap(Obj->highlight_back_button);

    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    al_destroy_bitmap(Obj->Money);

    free(Obj);
    free(self);
}