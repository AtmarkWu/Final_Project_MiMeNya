#include "buy.h"
#define BUTTON_NUM 2
//顯示詳細購買資訊與確認介面
/*
   [buy function]
*/

Elements *New_Buy(int label)
{
    Buy *pDerivedObj = (Buy *)malloc(sizeof(Buy));
    Elements *pObj = New_Elements(label);
    // setting derived object member    
    pDerivedObj->background_image = al_load_bitmap("assets/image/Shop/BG/BuyBG.png"); 

    //放置對應肉泥圖片
    pDerivedObj->food[0] = al_load_bitmap("assets/image/Shop/item/store_redmeat_H.png");
    pDerivedObj->food[1] = al_load_bitmap("assets/image/Shop/item/store_bluemeat.png");
    pDerivedObj->food[2] = al_load_bitmap("assets/image/Shop/item/store_pinkmeat.png");
    pDerivedObj->food[3] = al_load_bitmap("assets/image/Shop/item/store_greenmeat.png");
    pDerivedObj->food_X = WIDTH/2 - (al_get_bitmap_width(pDerivedObj->food[0])/2);
    pDerivedObj->food_Y = 150;

    //設定按鍵圖片
    pDerivedObj->button[0] = al_load_bitmap("assets/image/Shop/Button/Yes.png"); //購買
    pDerivedObj->hightlight_button[0] = al_load_bitmap("assets/image/Shop/Button/Yes_H.png");
    pDerivedObj->button_W[0] = al_get_bitmap_width(pDerivedObj->button[0]);
    pDerivedObj->button_H[0] = al_get_bitmap_height(pDerivedObj->button[0]);
    pDerivedObj->buttonH_W[0] = al_get_bitmap_width(pDerivedObj->hightlight_button[0]);
    pDerivedObj->buttonH_H[0] = al_get_bitmap_height(pDerivedObj->hightlight_button[0]);

    pDerivedObj->button[1] = al_load_bitmap("assets/image/Shop/Button/No.png"); //不購買
    pDerivedObj->hightlight_button[1] = al_load_bitmap("assets/image/Shop/Button/No_H.png");
    pDerivedObj->button_W[1] = al_get_bitmap_width(pDerivedObj->button[1]);
    pDerivedObj->button_H[1] = al_get_bitmap_height(pDerivedObj->button[1]);
    pDerivedObj->buttonH_W[1] = al_get_bitmap_width(pDerivedObj->hightlight_button[1]);
    pDerivedObj->buttonH_H[1] = al_get_bitmap_height(pDerivedObj->hightlight_button[1]);

    //設置按鈕位置
    int increments = 300;
    for(int i = 0 ; i < BUTTON_NUM ; i++){
        pDerivedObj->X[i] = increments;
        pDerivedObj->Y[i] = 700;
        pDerivedObj->XH[i] = increments-10;
        pDerivedObj->YH[i] = 700;
        increments += 600;
    }
    pDerivedObj->Y[1] += 20; //No按鍵微調

    //設定錢不夠時的圖片
    pDerivedObj->NoMoney = al_load_bitmap("assets/image/Shop/item/NoEnoughMoney.png");
    pDerivedObj->MeatPrice[1] = 10; //設定肉泥價錢
    pDerivedObj->MeatPrice[2] = 50;
    pDerivedObj->MeatPrice[3] = 70;
    pDerivedObj->MeatPrice[4] = 100;

    pDerivedObj->NoEnough = false; //一開始預設為足夠

    //設定按鈕音效
    pDerivedObj->ButtonClick = al_load_sample("assets/sound/button_press_sound.wav");
    al_reserve_samples(20);
    pDerivedObj->Click_sample_instance = al_create_sample_instance(pDerivedObj->ButtonClick);
    al_set_sample_instance_playmode(pDerivedObj->Click_sample_instance, ALLEGRO_PLAYMODE_ONCE);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->Click_sample_instance, al_get_default_mixer());
    //設定音效音量
    al_set_sample_instance_gain(pDerivedObj->Click_sample_instance, 1);

    //設定付錢音效
    pDerivedObj->PayMoney = al_load_sample("assets/sound/shop/money.wav");
    al_reserve_samples(20);
    pDerivedObj->PayMoney_sample_instance = al_create_sample_instance(pDerivedObj->PayMoney);
    al_set_sample_instance_playmode(pDerivedObj->PayMoney_sample_instance, ALLEGRO_PLAYMODE_ONCE);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->PayMoney_sample_instance, al_get_default_mixer());
    //設定音效音量
    al_set_sample_instance_gain(pDerivedObj->PayMoney_sample_instance, 1);

    //設定字體
    pDerivedObj->font = al_load_ttf_font("assets/font/GenSenRounded-M.ttc", 24, 0);
    pDerivedObj->q_x = WIDTH/2;
    pDerivedObj->q_y = HEIGHT/2;


    pDerivedObj->NE_x = 400;
    pDerivedObj->NE_y = 650;
    
    //一進來初始化先把滑鼠點擊狀態清空
    mouse_state[1] = false;

    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = buy_update;
    pObj->Interact = buy_interact;
    pObj->Draw = buy_draw;
    pObj->Destroy = buy_destroy;
    return pObj;
}

void buy_update(Elements *self) //事件更新
{
    if(gameFunction == 1 && which_food != 0){
        Buy *Obj = ((Buy *)(self->pDerivedObj));
        Buy_DetectButtonOn(self);
        if (mouse_state[1]) //檢查滑鼠左鍵按下的當下是否在按鈕上
        {
            if(Obj->over_button[0]){ //YES按鈕
                printf("Yes\n");
                if(TotalMoney < Obj->MeatPrice[which_food]){ //如果錢不夠
                    Obj->NoEnough = true;
                }
                else{ //錢如果足夠才會扣錢，並回到商店頁面
                    al_play_sample_instance(Obj->PayMoney_sample_instance);
                    TotalMoney -= Obj->MeatPrice[which_food];
                    OwnMeat[which_food] += 1; //增加該肉泥的持有數
                    Obj->NoEnough = false;
                    //復原狀態，讓下一次可以先顯示肉泥，按過YES發現不夠錢再顯示
                    which_food = 0; //買完回到商店頁面
                }
            }
            if(Obj->over_button[1]){ //NO按鈕
                al_play_sample_instance(Obj->Click_sample_instance);
                printf("No\n");
                Obj->NoEnough = false;
                //復原狀態，讓下一次可以先顯示肉泥，按過YES發現不夠錢再顯示
                which_food = 0; //買完回到商店頁面
            }
        }        
    }


}

void buy_interact(Elements *self, Elements *tar){

}

void buy_draw(Elements *self) //【要被畫出的東西】
{
    if(gameFunction == 1 && which_food != 0){
        Buy *Obj = ((Buy *)(self->pDerivedObj));
        printf("in buy window: %d\n", al_get_bitmap_width(Obj->background_image));

        al_draw_bitmap(Obj->background_image, 0, 0, 0);
        
        printf("which_food = %d\n", which_food);

        //畫出對應肉泥
        if(Obj->NoEnough){ //如果有按過YES但是錢不夠
            al_draw_bitmap(Obj->NoMoney, WIDTH/2-(al_get_bitmap_width(Obj->NoMoney)/2), 120, 0);
            al_draw_text(Obj->font, al_map_rgb(255, 0, 0), Obj->NE_x, Obj->NE_y, ALLEGRO_ALIGN_CENTER, "Sorry, No Enough Money :(");
        }
        else{ //如果有按過YES且錢夠or沒按過YES
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
                case 4:
                    al_draw_bitmap(Obj->food[3], Obj->food_X, Obj->food_Y, 0);
                    break;

                default:
                    break;
            }
        }

        Buy_DetectButtonOn(self); //畫完正常按鈕後，檢查滑鼠是否停在按鈕上，並更改狀態        
    }

}

void Buy_DetectButtonOn(Elements *self){
    Buy *Obj = ((Buy *)(self->pDerivedObj));
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

void buy_destroy(Elements *self)
{
    Buy *Obj = ((Buy *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background_image;
    al_destroy_bitmap(background); //【destory背景圖片(先宣告才能刪除)】

    al_destroy_bitmap(Obj->food[0]);
    al_destroy_bitmap(Obj->food[1]);
    al_destroy_bitmap(Obj->food[2]);
    al_destroy_bitmap(Obj->food[3]);

    al_destroy_bitmap(Obj->button[0]);
    al_destroy_bitmap(Obj->button[1]);
    
    al_destroy_bitmap(Obj->hightlight_button[0]);
    al_destroy_bitmap(Obj->hightlight_button[1]);
    
    al_destroy_bitmap(Obj->NoMoney);

    al_destroy_sample(Obj->PayMoney);
    al_destroy_sample_instance(Obj->PayMoney_sample_instance);
    al_destroy_sample(Obj->ButtonClick);
    al_destroy_sample_instance(Obj->Click_sample_instance);

    al_destroy_font(Obj->font);

    free(Obj);
    free(self);
}