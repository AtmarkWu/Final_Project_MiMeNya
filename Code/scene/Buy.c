#include <allegro5/allegro_primitives.h>
#include "Buy.h"
#include <stdbool.h>
#define BUTTON_NUM 2
/*
   [buy function]
*/

Scene *New_Buy(int label)
{
    Buy *pDerivedObj = (Buy *)malloc(sizeof(Buy));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 20, 0);
    
    pDerivedObj->background_image = al_load_bitmap("assets/image/Shop/BG/BuyBG.png"); 

    //放置對應肉泥圖片
    pDerivedObj->food[0] = al_load_bitmap("assets/image/Shop/item/Meat1-3.png");
    pDerivedObj->food[1] = al_load_bitmap("assets/image/Shop/item/Meat2-3.png");
    pDerivedObj->food[2] = al_load_bitmap("assets/image/Shop/item/Meat3-3.png");
    pDerivedObj->food_X = 350;
    pDerivedObj->food_Y = 120;


    //設定按鍵圖片
    pDerivedObj->button[0] = al_load_bitmap("assets/image/Shop/Button/yes.png"); //meat1
    pDerivedObj->button[1] = al_load_bitmap("assets/image/Shop/Button/no.png"); //meat2
    
    pDerivedObj->hightlight_button[0] = al_load_bitmap("assets/image/Shop/Button/yes_h.png");
    pDerivedObj->hightlight_button[1] = al_load_bitmap("assets/image/Shop/Button/no_h.png");
    
    pDerivedObj->button_W = 200;
    pDerivedObj->button_H = 100;

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
    pObj->Update = buy_update;
    pObj->Draw = buy_draw;
    pObj->Destroy = buy_destroy;
    return pObj;
}

void buy_update(Scene *self) //【菜單事件更新】
{
    Buy *Obj = ((Buy *)(self->pDerivedObj));
    Buy_DetectButtonOn(self);
    if (mouse_state[1]) //檢查滑鼠左鍵按下的當下是否在按鈕上
    {
        if(Obj->over_button[0]){ //Meat1頁面
            printf("Yes\n");
            self->scene_end = true;
            window = 6;
        }
        if(Obj->over_button[1]){ //Meat2頁面
            printf("No\n");
            self->scene_end = true;
            window = 6;
        }
    }
    
    return;
}

void buy_draw(Scene *self) //【要被畫出的東西】
{
    Buy *Obj = ((Buy *)(self->pDerivedObj));
    printf("in buy window: %d\n", al_get_bitmap_width(Obj->background_image));

    al_draw_bitmap(Obj->background_image, 0, 0, 0);
    
    printf("which_food = %d\n", which_food);

    //畫出對應肉泥
    switch (which_food)
    {
        case 1:
            al_draw_bitmap(Obj->food[0], Obj->food_X, Obj->food_Y, 0);
            break;
        case 2:
            al_draw_bitmap(Obj->food[1], Obj->food_X, Obj->food_Y, 0);
            break;
        case 3:
            al_draw_bitmap(Obj->food[2], Obj->food_X, Obj->food_Y, 0);
            break;

        default:
            break;
    }

    al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->title_x, Obj->title_y+30, ALLEGRO_ALIGN_CENTER, "Are u sure to buy this food?");

    //【畫出2個按鈕】
    int increments = 150;
    for(int i = 0 ; i < BUTTON_NUM ; i++){
        Obj->X[i] = increments;
        Obj->Y[i] = 450;
        al_draw_bitmap(Obj->button[i], Obj->X[i], Obj->Y[i], 0);
        increments += 350;
    }

    Buy_DetectButtonOn(self); //畫完正常按鈕後，檢查滑鼠是否停在按鈕上，並更改狀態

    al_play_sample_instance(Obj->sample_instance);
}

void Buy_DetectButtonOn(Scene *self){

    Buy *Obj = ((Buy *)(self->pDerivedObj));
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
}

void buy_destroy(Scene *self)
{
    Buy *Obj = ((Buy *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background_image;
    al_destroy_bitmap(background); //【destory背景圖片(先宣告才能刪除)】

    al_destroy_bitmap(Obj->food[0]);
    al_destroy_bitmap(Obj->food[1]);
    al_destroy_bitmap(Obj->food[2]);

    al_destroy_bitmap(Obj->button[0]);
    al_destroy_bitmap(Obj->button[1]);
    
    al_destroy_bitmap(Obj->hightlight_button[0]);
    al_destroy_bitmap(Obj->hightlight_button[1]);
    

    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);

    free(Obj);
    free(self);
}