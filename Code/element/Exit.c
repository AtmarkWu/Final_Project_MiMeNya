#include "Exit.h"
//#define ButtonNum 3
//回到遊戲畫面、上一頁、下一頁按鈕皆在此管理
/*
   [Exit function]
*/
Elements *New_Exit(int label)
{
    Exit *pDerivedObj = (Exit *)malloc(sizeof(Exit));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->image[0] = al_load_bitmap("assets/image/Ending/1.png");
    pDerivedObj->image[1] = al_load_bitmap("assets/image/Ending/2.png");
    pDerivedObj->image[2] = al_load_bitmap("assets/image/Ending/3.png");
    pDerivedObj->image[3] = al_load_bitmap("assets/image/Ending/4.png");
    pDerivedObj->image[4] = al_load_bitmap("assets/image/Ending/5.png");
    pDerivedObj->image[5] = al_load_bitmap("assets/image/Ending/6.png");
    pDerivedObj->image[6] = al_load_bitmap("assets/image/Ending/7.png");
    pDerivedObj->image[7] = al_load_bitmap("assets/image/Ending/8.png");
    pDerivedObj->image[8] = al_load_bitmap("assets/image/Ending/9.png");
    pDerivedObj->image[9] = al_load_bitmap("assets/image/Ending/10.png");
    pDerivedObj->image[10] = al_load_bitmap("assets/image/Ending/11.png");
    pDerivedObj->image[11] = al_load_bitmap("assets/image/Ending/12.png");
    pDerivedObj->image[12] = al_load_bitmap("assets/image/Ending/13.png");
    pDerivedObj->image[13] = al_load_bitmap("assets/image/Ending/14.png");
    pDerivedObj->image[14] = al_load_bitmap("assets/image/Ending/15.png");
    pDerivedObj->image[15] = al_load_bitmap("assets/image/Ending/16.png");
    pDerivedObj->image[16] = al_load_bitmap("assets/image/Ending/17.png");
    pDerivedObj->image[17] = al_load_bitmap("assets/image/Ending/18.png");
    pDerivedObj->image[18] = al_load_bitmap("assets/image/Ending/19.png");
    pDerivedObj->image[19] = al_load_bitmap("assets/image/Ending/20.png");
    pDerivedObj->image[20] = al_load_bitmap("assets/image/Ending/21.png");
    pDerivedObj->image[21] = al_load_bitmap("assets/image/Ending/22.png");
    pDerivedObj->image[22] = al_load_bitmap("assets/image/Ending/23.png");
    pDerivedObj->image[23] = al_load_bitmap("assets/image/Ending/24.png");
    pDerivedObj->image[24] = al_load_bitmap("assets/image/Ending/25.png");
    pDerivedObj->image[25] = al_load_bitmap("assets/image/Ending/26.png");
    pDerivedObj->image[26] = al_load_bitmap("assets/image/Ending/27.png");
    pDerivedObj->image[27] = al_load_bitmap("assets/image/Ending/28.png");
    pDerivedObj->image[28] = al_load_bitmap("assets/image/Ending/29.png");
    pDerivedObj->image[29] = al_load_bitmap("assets/image/Ending/30.png");
    pDerivedObj->image[30] = al_load_bitmap("assets/image/Ending/31.png");
    pDerivedObj->image[31] = al_load_bitmap("assets/image/Ending/32.png");
    pDerivedObj->image[32] = al_load_bitmap("assets/image/Ending/33.png");
    pDerivedObj->image[33] = al_load_bitmap("assets/image/Ending/34.png");
    pDerivedObj->image[34] = al_load_bitmap("assets/image/Ending/35.png");
    pDerivedObj->image[35] = al_load_bitmap("assets/image/Ending/36.png");
    pDerivedObj->image[36] = al_load_bitmap("assets/image/Ending/37.png");
    pDerivedObj->image[37] = al_load_bitmap("assets/image/Ending/38.png");
    pDerivedObj->image[38] = al_load_bitmap("assets/image/Ending/39.png");
    pDerivedObj->image[39] = al_load_bitmap("assets/image/Ending/40.png");
    pDerivedObj->image[40] = al_load_bitmap("assets/image/Ending/41.png");
    pDerivedObj->image[41] = al_load_bitmap("assets/image/Ending/42.png");
    pDerivedObj->image[42] = al_load_bitmap("assets/image/Ending/43.png");
    pDerivedObj->image[43] = al_load_bitmap("assets/image/Ending/44.png");
    pDerivedObj->image[44] = al_load_bitmap("assets/image/Ending/45.png");
    pDerivedObj->image[45] = al_load_bitmap("assets/image/Ending/46.png");
    pDerivedObj->image[46] = al_load_bitmap("assets/image/Ending/47.png");
    pDerivedObj->image[47] = al_load_bitmap("assets/image/Ending/48.png");

    //設定按鈕音效
    pDerivedObj->ButtonClick = al_load_sample("assets/sound/button_press_sound.wav");
    al_reserve_samples(20);
    pDerivedObj->Click_sample_instance = al_create_sample_instance(pDerivedObj->ButtonClick);
    al_set_sample_instance_playmode(pDerivedObj->Click_sample_instance, ALLEGRO_PLAYMODE_ONCE);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->Click_sample_instance, al_get_default_mixer());
    //設定音效音量
    al_set_sample_instance_gain(pDerivedObj->Click_sample_instance, 1);

    pDerivedObj->click = 0;
    pDerivedObj->FakeTimer = 0;
    pDerivedObj->currentFrame = 0;

    pObj->pDerivedObj = pDerivedObj;

    //一進來初始化先把滑鼠點擊狀態清空
    mouse_state[1] = false;

    // setting derived object function
    pObj->Update = Exit_update;
    pObj->Interact = Exit_interact;
    pObj->Draw = Exit_draw;
    pObj->Destroy = Exit_destroy;
    return pObj;
}

void Exit_update(Elements *self) //【事件更新】
{
    //Exit *Obj = ((Exit *)(self->pDerivedObj));

    // if(gameFunction == 3){
    //     //按鈕事件偵測
    //     if (mouse_state[1]) //檢查滑鼠左鍵按下的當下是否在按鈕上
    //     {

    //     }
    // }

}

void Exit_interact(Elements *self, Elements *tar){

}

void Exit_draw(Elements *self) //【菜單內要被畫出的東西】
{
    if(gameFunction == 3){
        al_clear_to_color(al_map_rgb(0, 0, 0));
        Exit *Obj = ((Exit *)(self->pDerivedObj));
        //printf("in Exit: %d\n", al_get_bitmap_width(Obj->background_image));

        if(Obj->FakeTimer != 24 && Obj->currentFrame <= 47){
            if(Obj->currentFrame == 0){ //畫出上一張銜接
                al_clear_to_color(al_map_rgb(0, 0, 0));
            }
            else{
                al_draw_bitmap(Obj->image[Obj->currentFrame-1], 0, 0, 0);
            }
            
            al_draw_bitmap(Obj->image[Obj->currentFrame], 0, 0, 0);
        }
        else{
            Obj->currentFrame++;
            Obj->FakeTimer = 0;
        }
        Obj->FakeTimer++;
        
        if(Obj->currentFrame > 47){
            CloseGame = 1;
        }

        //Exit_DetectButtonOn(self); //畫完正常按鈕後，檢查滑鼠是否停在按鈕上，並更改狀態

        //ExitTurnPage(self); //檢查玩家是否翻頁
    }

}


// int ExitTurnPage(Elements *self){
    
// }

void Exit_destroy(Elements *self)
{
    Exit *Obj = ((Exit *)(self->pDerivedObj));
    //ALLEGRO_BITMAP *background = Obj->image;
    //al_destroy_bitmap(background); //【destory背景圖片(先宣告才能刪除)】
    for(int i = 0 ; i < 48 ; i++){
        al_destroy_bitmap(Obj->image[i]);
    }

    al_destroy_sample(Obj->ButtonClick);
    al_destroy_sample_instance(Obj->Click_sample_instance);

    free(Obj);
    free(self);
}
