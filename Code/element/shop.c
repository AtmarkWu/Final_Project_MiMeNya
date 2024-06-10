#include "shop.h"
#define BUTTON_NUM 4
//顯示金錢、肉泥
/*
   [Shop function]
*/

Elements *New_Shop(int label)
{
    Shop *pDerivedObj = (Shop *)malloc(sizeof(Shop));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->background_image = al_load_bitmap("assets/image/Shop/BG/store_BGwithBoss.png"); //設定商店背景

    //【設定4種肉泥圖案】
    pDerivedObj->button[0] = al_load_bitmap("assets/image/Shop/item/store_redmeat.png"); //meat1
    pDerivedObj->button[1] = al_load_bitmap("assets/image/Shop/item/store_bluemeat.png"); //meat2
    pDerivedObj->button[2] = al_load_bitmap("assets/image/Shop/item/store_pinkmeat.png"); //meat3
    pDerivedObj->button[3] = al_load_bitmap("assets/image/Shop/item/store_greenmeat.png");//meat4

    pDerivedObj->hightlight_button[0] = al_load_bitmap("assets/image/Shop/item/store_redmeat_H.png"); //暫時沒有highlight
    pDerivedObj->hightlight_button[1] = al_load_bitmap("assets/image/Shop/item/store_bluemeat_H.png");
    pDerivedObj->hightlight_button[2] = al_load_bitmap("assets/image/Shop/item/store_pinkmeat_H.png");
    pDerivedObj->hightlight_button[3] = al_load_bitmap("assets/image/Shop/item/store_greenmeat_H.png");

    pDerivedObj->button_W = al_get_bitmap_width(pDerivedObj->button[0]);
    pDerivedObj->button_H = al_get_bitmap_height(pDerivedObj->button[0]);
    pDerivedObj->buttonH_W = al_get_bitmap_width(pDerivedObj->hightlight_button[0]);
    pDerivedObj->buttonH_H = al_get_bitmap_height(pDerivedObj->hightlight_button[0]);

    //設定肉泥選擇按鈕位置(上->右->下->左)
    int plusX = 680;
    int plusY = 200;
    for(int i = 0 ; i < BUTTON_NUM ; i++){
        pDerivedObj->X[i] = plusX;
        pDerivedObj->Y[i] = plusY;
        pDerivedObj->XH[i] = plusX-20;
        pDerivedObj->YH[i] = plusY-20;

        plusX += 350;
        if(i == 1){
            plusY += 350;
            plusX = 680;
        }
    }

    //back to gamescene
    pDerivedObj->back_button = al_load_bitmap("assets/image/Shop/Button/BackIconClose.png"); 
    pDerivedObj->highlight_back_button = al_load_bitmap("assets/image/Shop/Button/BackIconOpen.png"); 
    pDerivedObj->back_button_W = al_get_bitmap_width(pDerivedObj->back_button);
    pDerivedObj->back_button_H = al_get_bitmap_height(pDerivedObj->back_button);

    //設定回到遊戲的按鈕位置
    pDerivedObj->back_button_X = 1300;
    pDerivedObj->back_button_Y = 80;

    pDerivedObj->Money = al_load_bitmap("assets/image/Shop/item/MoneyIcon.png");

    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/shop/ShopBGM.wav");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.5);

    //設定按鈕音效
    pDerivedObj->ButtonClick = al_load_sample("assets/sound/button_press_sound.wav");
    al_reserve_samples(20);
    pDerivedObj->Click_sample_instance = al_create_sample_instance(pDerivedObj->ButtonClick);
    al_set_sample_instance_playmode(pDerivedObj->Click_sample_instance, ALLEGRO_PLAYMODE_ONCE);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->Click_sample_instance, al_get_default_mixer());
    //設定音效音量
    al_set_sample_instance_gain(pDerivedObj->Click_sample_instance, 1);

    //字體設定
    pDerivedObj->font = al_load_ttf_font("assets/font/GenSenRounded-M.ttc", 32, 0);
    pDerivedObj->title_x = 400;
    pDerivedObj->title_y = 60;

    //chatBox
    pDerivedObj->chatBox[0] = al_load_bitmap("assets/image/Shop/chatBox/chatBox1.png"); 
    pDerivedObj->chatBox[1] = al_load_bitmap("assets/image/Shop/chatBox/chatBox2.png"); 
    pDerivedObj->chatBox[2] = al_load_bitmap("assets/image/Shop/chatBox/chatBox3.png"); 
    pDerivedObj->shopkeeper_W = al_get_bitmap_width(pDerivedObj->chatBox[0]);
    pDerivedObj->shopkeeper_H = al_get_bitmap_height(pDerivedObj->chatBox[0]);
    pDerivedObj->shopkeeper_X = 50;
    pDerivedObj->shopkeeper_Y = 350;
    pDerivedObj->chatNumber = 1;
    pDerivedObj->click = 0;
    
    //一進來初始化先把滑鼠點擊狀態清空
    mouse_state[1] = false;

    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Update = shop_update;
    pObj->Interact = shop_interact;
    pObj->Draw = shop_draw;
    pObj->Destroy = shop_destroy;
    return pObj;
}

void shop_update(Elements *self) //事件更新
{
    Shop *Obj = ((Shop *)(self->pDerivedObj));
    if(gameFunction == 1){
        al_play_sample_instance(Obj->sample_instance);

        Shop *Obj = ((Shop *)(self->pDerivedObj));
        Shop_DetectButtonOn(self);
        if (mouse_state[1]) //檢查滑鼠左鍵按下的當下是否在按鈕上
        {
            if(Obj->over_button[0]){ //Meat1頁面
                al_play_sample_instance(Obj->Click_sample_instance);
                printf("Meat1\n");
                which_food = 1;//記錄當前選擇
            }
            if(Obj->over_button[1]){ //Meat2頁面
                al_play_sample_instance(Obj->Click_sample_instance);
                printf("Meat2\n");
                which_food = 2;//記錄當前選擇
            }
            if(Obj->over_button[2]){ //Meat3頁面
                al_play_sample_instance(Obj->Click_sample_instance);
                printf("Meat3\n");
                which_food = 3;//記錄當前選擇
            }
            if(Obj->over_button[3]){ //Meat4頁面
                al_play_sample_instance(Obj->Click_sample_instance);
                printf("Meat4\n");
                which_food = 4;//記錄當前選擇
            }
            if(Obj->over_back_button){//回到gamescene
                al_play_sample_instance(Obj->Click_sample_instance);
                printf("Back to game\n");
                al_stop_sample_instance(Obj->sample_instance);
                gameFunction = -1;
            }

            if(Obj->over_shopkeeper){
                printf("new chat\n");
                printf("chatNumber = %d\n", Obj->chatNumber);
                Obj->click = 1;
            }
        }
        else{
            if(Obj->over_shopkeeper && Obj->click){
                printf("lift mouse\n");
                Obj->chatNumber++;
                if(Obj->chatNumber==3){
                    Obj->chatNumber %= 3;
                }
                Obj->click = 0;
            }
        }

    }

    
}

void shop_interact(Elements *self, Elements *tar){

}

void shop_draw(Elements *self) //要被畫出的東西
{
    if(gameFunction == 1){
        Shop *Obj = ((Shop *)(self->pDerivedObj));
        printf("in shop: %d\n", al_get_bitmap_width(Obj->background_image));
        printf("Current Money: %d\n", TotalMoney);
        
        al_draw_bitmap(Obj->background_image, 0, 0, 0);

        //【畫出4個按鈕 & back】
        Shop_DetectButtonOn(self); //畫完正常按鈕後，檢查滑鼠是否停在按鈕上，並更改狀態

        //chatBox
        Obj->chatBox_X = 50;
        Obj->chatBox_Y = 650;
        al_draw_bitmap(Obj->chatBox[Obj->chatNumber], Obj->chatBox_X, Obj->chatBox_Y, 0);
        Touch_Shopkeeper(self); //有無碰到老闆

        //畫出金錢條&上面的數字
        al_draw_bitmap(Obj->Money, 40, 20, 0);
        HowManyMoneyIHave(self);
    }

}

void Touch_Shopkeeper(Elements *self){

    Shop *Obj = ((Shop *)(self->pDerivedObj));
    if((mouse.x >= Obj->shopkeeper_X)&&(mouse.x <= Obj->shopkeeper_X+Obj->shopkeeper_W)&&(mouse.y >= Obj->shopkeeper_Y)&&(mouse.y <= Obj->shopkeeper_Y+Obj->shopkeeper_H)){ //如果滑鼠在按鈕範圍內
        printf("on shopkeeper\n");
        Obj->over_shopkeeper = true;
    }
    else{
        Obj->over_shopkeeper = false;
    }
}

void Shop_DetectButtonOn(Elements *self){

    Shop *Obj = ((Shop *)(self->pDerivedObj));
    //for選擇四種肉泥的按鈕
    for(int i = 0 ; i < BUTTON_NUM ; i++){
        if((mouse.x >= Obj->X[i])&&(mouse.x <= Obj->X[i]+Obj->button_W)&&(mouse.y >= Obj->Y[i])&&(mouse.y <= Obj->Y[i]+Obj->button_H)){ //如果滑鼠在按鈕範圍內
            al_draw_bitmap(Obj->hightlight_button[i], Obj->XH[i], Obj->YH[i], 0);
            printf("on button[%d]\n", i);
            Obj->over_button[i] = true;
        }
        else{
            al_draw_bitmap(Obj->button[i], Obj->X[i], Obj->Y[i], 0);
            Obj->over_button[i] = false;
        }
    }

    //for回到遊戲的按鈕
    if((mouse.x >= Obj->back_button_X)&&(mouse.x <= Obj->back_button_X+Obj->back_button_W)&&(mouse.y >= Obj->back_button_Y)&&(mouse.y <= Obj->back_button_Y+Obj->back_button_H)){ //如果滑鼠在按鈕範圍內
        al_draw_bitmap(Obj->highlight_back_button, Obj->back_button_X-10, Obj->back_button_Y-10, 0);
        Obj->over_back_button = true;
    }
    else{
        al_draw_bitmap(Obj->back_button, Obj->back_button_X, Obj->back_button_Y, 0);
        Obj->over_back_button = false;
    }
}

void HowManyMoneyIHave(Elements *self){ //逐字拆解目前錢錢數字，並畫出來
    int Number[MaxMoney] = {0}; //最多7位數的陣列
    int temp = TotalMoney;
    int index = 0;
    int gap = 0;
    if(temp > 0){
        while(temp != 0){
            Number[index] = temp % 10;
            temp /= 10;
            index++;
        }
        for(int i = index-1 ; i >= 0 ; i--){ //到著跑，即可畫出從最小位~最高位
            PrintMoney(self, Number[i], gap);
            gap += 20; //增加x座標往後畫
        }
    }
    else{ //如果是0，就只印出0
        PrintMoney(self, 0, gap);
    }
}

void PrintMoney(Elements *self, int num, int gap){ //依照現在的數字是啥就印出誰
    Shop *Obj = ((Shop *)(self->pDerivedObj));
    switch(num){
        case 0:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->title_x+gap, Obj->title_y, ALLEGRO_ALIGN_CENTER, "0");
            break;
        case 1:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->title_x+gap, Obj->title_y, ALLEGRO_ALIGN_CENTER, "1");
            break;
        case 2:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->title_x+gap, Obj->title_y, ALLEGRO_ALIGN_CENTER, "2");
            break;
        case 3:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->title_x+gap, Obj->title_y, ALLEGRO_ALIGN_CENTER, "3");
            break;
        case 4:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->title_x+gap, Obj->title_y, ALLEGRO_ALIGN_CENTER, "4");
            break;
        case 5:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->title_x+gap, Obj->title_y, ALLEGRO_ALIGN_CENTER, "5");
            break;
        case 6:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->title_x+gap, Obj->title_y, ALLEGRO_ALIGN_CENTER, "6");
            break;
        case 7:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->title_x+gap, Obj->title_y, ALLEGRO_ALIGN_CENTER, "7");
            break;
        case 8:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->title_x+gap, Obj->title_y, ALLEGRO_ALIGN_CENTER, "8");
            break;
        case 9:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->title_x+gap, Obj->title_y, ALLEGRO_ALIGN_CENTER, "9");
            break;
        default:
            break;
    }
}


void shop_destroy(Elements *self)
{
    Shop *Obj = ((Shop *)(self->pDerivedObj));
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

    al_destroy_bitmap(Obj->chatBox[0]);
    al_destroy_bitmap(Obj->chatBox[1]);
    al_destroy_bitmap(Obj->chatBox[2]);

    al_destroy_bitmap(Obj->back_button);
    al_destroy_bitmap(Obj->highlight_back_button);

    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    al_destroy_bitmap(Obj->Money);
    al_destroy_sample(Obj->ButtonClick);
    al_destroy_sample_instance(Obj->Click_sample_instance);

    free(Obj);
    free(self);
}