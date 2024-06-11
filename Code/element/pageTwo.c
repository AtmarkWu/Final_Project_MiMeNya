#include "pageTwo.h"
#include "../shapes/Rectangle.h"
#define FrameUD 2
#define MaxCat 100 //同種貓可持有上限
//因為一頁2隻貓，所以這邊的全域變數要往後2個索引值判斷
/*
   [PageTwo function]
*/
Elements *New_PageTwo(int label)
{
    PageTwo *pDerivedObj = (PageTwo *)malloc(sizeof(PageTwo));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    //設定第二頁的預視圖([0]為上方的 | [1]為下方的 || 標籤與索引值同步)
    pDerivedObj->frame[0] = al_load_bitmap("assets/image/Book/content_frame.png");
    pDerivedObj->decFrame[0] = al_load_bitmap("assets/image/Book/content_frame.png");
    pDerivedObj->width[0] = al_get_bitmap_width(pDerivedObj->frame[0]);
    pDerivedObj->height[0] = al_get_bitmap_height(pDerivedObj->frame[0]);
    pDerivedObj->x[0] = 150;
    pDerivedObj->y[0] = 100;
    pDerivedObj->frame[1] = al_load_bitmap("assets/image/Book/content_frame.png");
    pDerivedObj->decFrame[1] = al_load_bitmap("assets/image/Book/content_frame.png");
    pDerivedObj->width[1] = al_get_bitmap_width(pDerivedObj->frame[1]);
    pDerivedObj->height[1] = al_get_bitmap_height(pDerivedObj->frame[1]);
    pDerivedObj->x[1] = 150;
    pDerivedObj->y[1] = pDerivedObj->x[0]+400;

    //其他要顯示在【預視圖】上面的東西(貓咪、資料、是否持有)
    int gap = 100;
    pDerivedObj->NoContent = al_load_bitmap("assets/image/Book/didnt_get.png");
    pDerivedObj->Content[0] = al_load_bitmap("assets/image/Book/book_cat3.png");
    pDerivedObj->C_w[0] = al_get_bitmap_width(pDerivedObj->Content[0]);
    pDerivedObj->C_h[0] = al_get_bitmap_height(pDerivedObj->Content[0]);
    pDerivedObj->Cx[0] = pDerivedObj->x[0]+gap; //第一格的x偏移
    pDerivedObj->Cy[0] = pDerivedObj->y[0]+((pDerivedObj->height[0])/2)-((pDerivedObj->C_h[0])/2); //第一格的y置中
    pDerivedObj->Content[1] = al_load_bitmap("assets/image/Book/book_cat4.png");
    pDerivedObj->C_w[1] = al_get_bitmap_width(pDerivedObj->Content[1]);
    pDerivedObj->C_h[1] = al_get_bitmap_height(pDerivedObj->Content[1]);
    pDerivedObj->Cx[1] = pDerivedObj->x[1]+gap; //第二格的x偏移
    pDerivedObj->Cy[1] = pDerivedObj->y[1]+((pDerivedObj->height[1])/2)-((pDerivedObj->C_h[1])/2); //第二格的y置中
    //標籤設置
    pDerivedObj->LackSign = al_load_bitmap("assets/image/Book/blocked.png");
    pDerivedObj->GetSign[0] = al_load_bitmap("assets/image/Book/book_no3mi.png");
    pDerivedObj->GetSign[1] = al_load_bitmap("assets/image/Book/book_no4mi.png");
    pDerivedObj->NewSign = al_load_bitmap("assets/image/Book/New.png");

    //細節圖背景設定
    pDerivedObj->Detail[0] = al_load_bitmap("assets/image/Book/no3_mi.png");
    pDerivedObj->Detail[1] = al_load_bitmap("assets/image/Book/no4_mi.png");
    pDerivedObj->Open[0] = false; //對應到第一格
    pDerivedObj->Open[1] = false; //對應到第二格

    //其他要顯示在【介紹】上面的東西(貓咪、資料、是否為新獲得)
    //貓咪持有數字體設定
    pDerivedObj->font = al_load_ttf_font("assets/font/GenSenRounded-M.ttc", 48, 0);
    pDerivedObj->titleX = 1000;
    pDerivedObj->titleY = (HEIGHT/2)-65;
    
    //設定New音效
    pDerivedObj->New = al_load_sample("assets/sound/book/New.wav");
    al_reserve_samples(20);
    pDerivedObj->New_sample_instance = al_create_sample_instance(pDerivedObj->New);
    al_set_sample_instance_playmode(pDerivedObj->New_sample_instance, ALLEGRO_PLAYMODE_ONCE);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->New_sample_instance, al_get_default_mixer());
    //設定音效音量
    al_set_sample_instance_gain(pDerivedObj->New_sample_instance, 1);

    //設定按鈕音效
    pDerivedObj->ButtonClick = al_load_sample("assets/sound/button_press_sound.wav");
    al_reserve_samples(20);
    pDerivedObj->Click_sample_instance = al_create_sample_instance(pDerivedObj->ButtonClick);
    al_set_sample_instance_playmode(pDerivedObj->Click_sample_instance, ALLEGRO_PLAYMODE_ONCE);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->Click_sample_instance, al_get_default_mixer());
    //設定音效音量
    al_set_sample_instance_gain(pDerivedObj->Click_sample_instance, 1);

    //設定按鈕音效
    pDerivedObj->Close = al_load_sample("assets/sound/game/No_caught.wav");
    al_reserve_samples(20);
    pDerivedObj->Close_sample_instance = al_create_sample_instance(pDerivedObj->Close);
    al_set_sample_instance_playmode(pDerivedObj->Close_sample_instance, ALLEGRO_PLAYMODE_ONCE);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->Close_sample_instance, al_get_default_mixer());
    //設定音效音量
    al_set_sample_instance_gain(pDerivedObj->Close_sample_instance, 1);

    pDerivedObj->cat_state = 0;

    //一進來初始化先把滑鼠點擊狀態清空
    mouse_state[1] = false;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = PageTwo_update;
    pObj->Interact = PageTwo_interact;
    pObj->Draw = PageTwo_draw;
    pObj->Destroy = PageTwo_destory;
    return pObj;
}

void PageTwo_update(Elements *self) {
    //PageTwo *Obj = ((PageTwo *)(self->pDerivedObj));

    if(gameFunction == 0 && Page == 2){ //如果在圖鑑功能內且頁數為2
        //滑鼠點擊事件更新
        if(mouse_state[1]){
            SeeDetail2(self);
        }        
    }

}

void PageTwo_interact(Elements *self, Elements *tar) {
}

void SeeDetail2(Elements *self){
    PageTwo *Obj = ((PageTwo *)(self->pDerivedObj));
    for(int i = 0 ; i < FrameUD ; i++){
        if((mouse.x >= Obj->x[i])&&(mouse.x <= Obj->x[i]+Obj->width[i])&&(mouse.y >= Obj->y[i])&&(mouse.y <= Obj->y[i]+Obj->height[i])){ //如果滑鼠在預視圖範圍內
            Obj->Open[i] = true;
            Obj->current_open = i; //設定打開的標籤為第i個
            printf("Open!\n");
            if(Obj->cat_state == 1){
                al_play_sample_instance(Obj->New_sample_instance);
                Obj->cat_state = 0;
            }else{
                al_play_sample_instance(Obj->Click_sample_instance);
            }
        }
        else{ //如果在滑鼠點擊的當下不是在預視圖內，且介紹是被打開的，就關起來
            if(Obj->Open[i] == true){
                al_play_sample_instance(Obj->Close_sample_instance);
                Obj->Open[i] = false;
                Obj->current_open = -1; //如果沒有任何介紹被打開，就設為-1
                printf("Close\n");
            }
        }
    }
}

void PageTwo_draw(Elements *self)
{
    if(gameFunction == 0 && Page == 2){ //如果在圖鑑功能內且頁數為2
        PageTwo *Obj = ((PageTwo *)(self->pDerivedObj));
        int gap = 250;
        //畫出預視圖框框
        for(int i = 0 ; i < FrameUD ; i++){
            al_draw_bitmap(Obj->decFrame[i], Obj->x[i], Obj->y[i], 0);
            //畫出要顯示在上面的貓咪縮圖、資訊等等
            if(Own[i+3]){ //如果是已經擁有的貓 -> 顯示縮圖(因為是第二頁，所以往後2格)
                al_draw_bitmap(Obj->Content[i], Obj->Cx[i], Obj->Cy[i], 0);
                
                if(NewCatOrNot[i+3]){ //如果是新獲得的貓 -> 顯示New
                    al_draw_bitmap(Obj->NewSign, Obj->Cx[i]+gap-50, Obj->Cy[i]+10, 0);
                    Obj->cat_state = 1;
                }
                else{ //如果不是新獲得的 -> 顯示get
                    al_draw_bitmap(Obj->GetSign[i], Obj->Cx[i]+gap, Obj->Cy[i]+80, 0);
                }
            }
            else{ //否則顯示未知&缺少
                al_draw_bitmap(Obj->NoContent, Obj->Cx[i], Obj->Cy[i], 0);
                al_draw_bitmap(Obj->LackSign, Obj->Cx[i]+gap, Obj->Cy[i]+80, 0);
            }
        }

        //根據Open跟current_open決定是否畫出介紹圖
        for(int i = 0 ; i < FrameUD ; i++){
            //如果介紹有被打開且標籤對應正確，而且該貓咪已獲得過
            if(Obj->Open[i] && Obj->current_open == i && Own[i+3]){ 
                //畫出該細節圖應該要有的內容(主圖、貓咪、介紹、持有數等等)
                al_draw_bitmap(Obj->Detail[i], 0, 0, 0);
                //呼叫函式畫出持有數
                HowManyCatIHave2(self, CatNumber[i+3]);
                //printf("---> %d\n", CatNumber[0]);
                if(NewCatOrNot[i+3]){ //如果該貓咪是新的 -> 點進來後已經看過內容(不再是新的)
                    // -> 在預視圖要改成顯示get
                    NewCatOrNot[i+3] = false;
                }
            }
        }


    }

}

void HowManyCatIHave2(Elements *self, int Cat_n){ //逐字拆解目前數字，並畫出來
    //printf("Draw Number\n");
    int Number[MaxCat] = {0};
    int NumberLen = 0;
    int ten = 1;
    int index = 0;
    int gap = 0;
    if(Cat_n > 0){
        while(ten <= Cat_n){
            ten *= 10;
            NumberLen++;
        }
        while(Cat_n != 0){
            Number[index] = Cat_n % 10;
            Cat_n /= 10;
            index++;
        }
        for(int i = NumberLen-1 ; i >= 0 ; i--){ //到著跑，即可畫出從最小位~最高位
            PrintNumber2(self, Number[i], gap);
            //printf("--> print: %d\n", Number[i]);
            gap += 30; //增加x座標往後畫
        }        
    }
    else{
        PrintNumber2(self, 0, gap);
    }

}

void PrintNumber2(Elements *self, int num, int gap){ //依照現在的數字是啥就印出誰
    PageTwo *Obj = ((PageTwo *)(self->pDerivedObj));
    //printf("--> current num is %d\n", num);
    switch(num){
        case 0:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->titleX+gap, Obj->titleY, ALLEGRO_ALIGN_CENTER, "0");
            break;
        case 1:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->titleX+gap, Obj->titleY, ALLEGRO_ALIGN_CENTER, "1");
            break;
        case 2:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->titleX+gap, Obj->titleY, ALLEGRO_ALIGN_CENTER, "2");
            break;
        case 3:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->titleX+gap, Obj->titleY, ALLEGRO_ALIGN_CENTER, "3");
            break;
        case 4:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->titleX+gap, Obj->titleY, ALLEGRO_ALIGN_CENTER, "4");
            break;
        case 5:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->titleX+gap, Obj->titleY, ALLEGRO_ALIGN_CENTER, "5");
            break;
        case 6:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->titleX+gap, Obj->titleY, ALLEGRO_ALIGN_CENTER, "6");
            break;
        case 7:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->titleX+gap, Obj->titleY, ALLEGRO_ALIGN_CENTER, "7");
            break;
        case 8:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->titleX+gap, Obj->titleY, ALLEGRO_ALIGN_CENTER, "8");
            break;
        case 9:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->titleX+gap, Obj->titleY, ALLEGRO_ALIGN_CENTER, "9");
            break;
        default:
            break;
    }
}

void PageTwo_destory(Elements *self)
{
    PageTwo *Obj = ((PageTwo *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->frame[0]);
    al_destroy_bitmap(Obj->frame[1]);
    al_destroy_bitmap(Obj->decFrame[0]);
    al_destroy_bitmap(Obj->decFrame[1]);
    //清除【預視圖】上資訊圖片
    al_destroy_bitmap(Obj->NoContent);
    al_destroy_bitmap(Obj->Content[0]);
    al_destroy_bitmap(Obj->Content[1]);
    al_destroy_bitmap(Obj->LackSign);
    al_destroy_bitmap(Obj->GetSign[0]);
    al_destroy_bitmap(Obj->GetSign[1]);
    al_destroy_bitmap(Obj->NewSign);
    //清除【介紹】上資訊圖片&字體
    al_destroy_bitmap(Obj->Detail[0]);
    al_destroy_bitmap(Obj->Detail[1]);
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->New);
    al_destroy_sample_instance(Obj->New_sample_instance);
    al_destroy_sample(Obj->ButtonClick);
    al_destroy_sample_instance(Obj->Click_sample_instance);
    al_destroy_sample(Obj->Close);
    al_destroy_sample_instance(Obj->Close_sample_instance);
    free(Obj);
    free(self);
}
