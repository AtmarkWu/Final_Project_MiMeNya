#include <allegro5/allegro_primitives.h>
#include "book.h"
#include <stdbool.h>
/*
   [Book function]
*/
Scene *New_Book(int label)
{
    Book *pDerivedObj = (Book *)malloc(sizeof(Book));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/GenSenRounded-M.ttc", 24, 0);
    //【設定背景】
    pDerivedObj->background_image = al_load_bitmap("assets/image/BookButton/BookBG.png");

    //【設定按鈕圖案】
    pDerivedObj->button = al_load_bitmap("assets/image/button_test.png"); //回到遊戲
    pDerivedObj->hightlight_button = al_load_bitmap("assets/image/button_test.png");
    pDerivedObj->button_W = 120;
    pDerivedObj->button_H = 120;

    //【設定音樂】
    pDerivedObj->song = al_load_sample("assets/sound/GameSceneBGM.mp3"); //未改，待加入新音樂
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

    // register 遊戲物件
    //_Register_elements(pObj, New_Basket(Bas_L));


    // setting derived object function
    pObj->Update = Book_update;
    pObj->Draw = Book_draw;
    pObj->Destroy = Book_destroy;
    return pObj;
}

void Book_update(Scene *self) //【事件更新】
{
    Book *Obj = ((Book *)(self->pDerivedObj));

    // // update every element
    // ElementVec allEle = _Get_all_elements(self);
    // for (int i = 0; i < allEle.len; i++)
    // {
    //     allEle.arr[i]->Update(allEle.arr[i]);
    // }

    // // run interact for every element
    // for (int i = 0; i < allEle.len; i++)
    // {
    //     Elements *ele = allEle.arr[i];
    //     // run every interact object
    //     for (int j = 0; j < ele->inter_len; j++)
    //     {
    //         int inter_label = ele->inter_obj[j];
    //         ElementVec labelEle = _Get_label_elements(self, inter_label);
    //         for (int i = 0; i < labelEle.len; i++)
    //         {
    //             ele->Interact(ele, labelEle.arr[i]);
    //         }
    //     }
    // }

    // // remove element
    // for (int i = 0; i < allEle.len; i++)
    // {
    //     Elements *ele = allEle.arr[i];
    //     if (ele->dele)
    //         _Remove_elements(self, ele);
    // }

    //按鈕事件偵測
    Book_DetectButtonOn(self);
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

void Book_draw(Scene *self) //【菜單內要被畫出的東西】
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    Book *Obj = ((Book *)(self->pDerivedObj));
    printf("in Book: %d\n", al_get_bitmap_width(Obj->background_image));

    al_draw_bitmap(Obj->background_image, 0, 0, 0); //【先畫出背景才不會被覆蓋】

    al_draw_filled_rectangle(Obj->title_x - 200, Obj->title_y - 250, Obj->title_x + 200, Obj->title_y + 250, al_map_rgb(250, 235, 215));
    al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->title_x, Obj->title_y-30, ALLEGRO_ALIGN_CENTER, "This is the cutest game");
    al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->title_x, Obj->title_y+30, ALLEGRO_ALIGN_CENTER, "IN THE WORLD !");
    al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->title_x, Obj->title_y+100, ALLEGRO_ALIGN_CENTER, "咪");

    // //畫出遊戲物件
    // ElementVec allEle = _Get_all_elements(self);
    // for (int i = 0; i < allEle.len; i++)
    // {
    //     Elements *ele = allEle.arr[i];
    //     ele->Draw(ele);
    // }

    //【畫出按鈕】
    int increments = 30;
    Obj->X[0] = 750;
    Obj->Y[0] = increments;
    al_draw_bitmap(Obj->button, Obj->X[0], Obj->Y[0], 0);
    
    Book_DetectButtonOn(self); //畫完正常按鈕後，檢查滑鼠是否停在按鈕上，並更改狀態

    al_play_sample_instance(Obj->sample_instance);
}

void Book_DetectButtonOn(Scene *self){
    Book *Obj = ((Book *)(self->pDerivedObj));
    if((mouse.x >= Obj->X[0])&&(mouse.x <= Obj->X[0]+Obj->button_W)&&(mouse.y >= Obj->Y[0])&&(mouse.y <= Obj->Y[0]+Obj->button_H)){ //如果滑鼠在按鈕範圍內
        al_draw_bitmap(Obj->hightlight_button, Obj->X[0], Obj->Y[0], ALLEGRO_FLIP_VERTICAL);
        Obj->over_button = true;
    }
    else{
        Obj->over_button = false;
    }
}

void Book_destroy(Scene *self)
{
    Book *Obj = ((Book *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background_image;
    al_destroy_bitmap(background); //【destory背景圖片(先宣告才能刪除)】
    al_destroy_bitmap(Obj->button);
    al_destroy_bitmap(Obj->hightlight_button);
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    // //刪除遊戲內元素
    // ElementVec allEle = _Get_all_elements(self);
    // for (int i = 0; i < allEle.len; i++)
    // {
    //     Elements *ele = allEle.arr[i];
    //     ele->Destroy(ele);
    // }
    free(Obj);
    free(self);
}
