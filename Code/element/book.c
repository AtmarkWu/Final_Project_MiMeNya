#include "book.h"
#define ButtonNum 3
//回到遊戲畫面、上一頁、下一頁按鈕皆在此管理
//【問題】前後頁的按鈕跟關閉的差距太大？
/*
   [Book function]
*/
Elements *New_Book(int label)
{
    Book *pDerivedObj = (Book *)malloc(sizeof(Book));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->font = al_load_ttf_font("assets/font/GenSenRounded-M.ttc", 24, 0);
    //【設定背景】
    pDerivedObj->background_image = al_load_bitmap("assets/image/Book/book_base.png");

    //【設定按鈕圖案】
    pDerivedObj->button[0] = al_load_bitmap("assets/image/Book/cancel.png"); //回到遊戲畫面
    pDerivedObj->high[0] = al_load_bitmap("assets/image/Book/cancel_H.png");
    pDerivedObj->button_W[0] = al_get_bitmap_width(pDerivedObj->button[0]);
    pDerivedObj->button_H[0] = al_get_bitmap_height(pDerivedObj->button[0]);

    pDerivedObj->button[1] = al_load_bitmap("assets/image/Book/next.png"); //下一頁
    pDerivedObj->high[1] = al_load_bitmap("assets/image/Book/next_H.png"); //下一頁
    pDerivedObj->button_W[1] = al_get_bitmap_width(pDerivedObj->button[1]);
    pDerivedObj->button_H[1] = al_get_bitmap_height(pDerivedObj->button[1]);

    pDerivedObj->button[2] = al_load_bitmap("assets/image/Book/back.png"); //上一頁
    pDerivedObj->high[2] = al_load_bitmap("assets/image/Book/back_H.png"); //上一頁
    pDerivedObj->button_W[2] = al_get_bitmap_width(pDerivedObj->button[2]);
    pDerivedObj->button_H[2] = al_get_bitmap_height(pDerivedObj->button[2]);

    //設定按鈕位置
    int increments = 60;
    pDerivedObj->X[0] = 1150;
    pDerivedObj->Y[0] = increments;
    pDerivedObj->XH[0] = 1145;
    pDerivedObj->YH[0] = increments-10;
    increments += 400;
    for(int i = 1 ; i < ButtonNum ; i++){
        pDerivedObj->X[i] = 1150;
        pDerivedObj->Y[i] = increments;
        pDerivedObj->XH[i] = 1145;
        pDerivedObj->YH[i] = increments-10;
        increments += 230;
    }

    pDerivedObj->cover = al_load_bitmap("assets/image/Book/book_first.png"); //圖鑑封面圖


    //設定按鈕音效
    pDerivedObj->ButtonClick = al_load_sample("assets/sound/button_press_sound.wav");
    al_reserve_samples(20);
    pDerivedObj->Click_sample_instance = al_create_sample_instance(pDerivedObj->ButtonClick);
    al_set_sample_instance_playmode(pDerivedObj->Click_sample_instance, ALLEGRO_PLAYMODE_ONCE);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->Click_sample_instance, al_get_default_mixer());
    //設定音效音量
    al_set_sample_instance_gain(pDerivedObj->Click_sample_instance, 1);

    //設定翻頁音效
    pDerivedObj->PageTurn = al_load_sample("assets/sound/book/turning_page.wav");
    al_reserve_samples(20);
    pDerivedObj->PageTurn_sample_instance = al_create_sample_instance(pDerivedObj->PageTurn);
    al_set_sample_instance_playmode(pDerivedObj->PageTurn_sample_instance, ALLEGRO_PLAYMODE_ONCE);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->PageTurn_sample_instance, al_get_default_mixer());
    //設定音效音量
    al_set_sample_instance_gain(pDerivedObj->PageTurn_sample_instance, 1);

    //翻頁判斷設定
    pDerivedObj->pressD = 0;
    pDerivedObj->pressA = 0;

    //設定字體位置
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;

    pObj->pDerivedObj = pDerivedObj;

    //一進來初始化先把滑鼠點擊狀態清空
    mouse_state[1] = false;

    // setting derived object function
    pObj->Update = Book_update;
    pObj->Interact = Book_interact;
    pObj->Draw = Book_draw;
    pObj->Destroy = Book_destroy;
    return pObj;
}

void Book_update(Elements *self) //【事件更新】
{
    Book *Obj = ((Book *)(self->pDerivedObj));

    if(gameFunction == 0){
        //按鈕事件偵測
        Book_DetectButtonOn(self);
        if (mouse_state[1]) //檢查滑鼠左鍵按下的當下是否在按鈕上
        {
            if(Obj->over_button){ //回到遊戲內畫面
                al_play_sample_instance(Obj->Click_sample_instance);
                printf("back to game\n");
                gameFunction = -1;
            }
        }    
        //鍵盤事件偵測(換頁功能)
        int dir = BookTurnPage(self); //接收方向，看是往前一頁還是往後一頁
        if(dir == 1){
            printf("forward\n");
            Page++; //往後一頁
        }
        else if(dir == 2){
            printf("backward\n");
            Page--; //往前(倒退)一頁
        }
        else{
            printf("no dir\n");
        }
        
        if(Page < 0){ //如果發現Page變數變成小於0，則強制設定為0
            Page = 0;
        }
        printf("-> Page = %d\n", Page);
    }

}

void Book_interact(Elements *self, Elements *tar){

}

void Book_draw(Elements *self) //【菜單內要被畫出的東西】
{
    if(gameFunction == 0){
        al_clear_to_color(al_map_rgb(0, 0, 0));
        Book *Obj = ((Book *)(self->pDerivedObj));
        printf("in Book: %d\n", al_get_bitmap_width(Obj->background_image));

        al_draw_bitmap(Obj->background_image, 0, 0, 0); //【先畫出背景才不會被覆蓋】

        //繪製封面裝飾
        if(Page == 0){ //如果在封面頁再畫出來
            al_draw_bitmap(Obj->cover, 0, 0, 0);
        }

        for(int i = 0 ; i < ButtonNum ; i++){
            al_draw_bitmap(Obj->button[i], Obj->X[i], Obj->Y[i], 0);
        }
        Book_DetectButtonOn(self); //畫完正常按鈕後，檢查滑鼠是否停在按鈕上，並更改狀態

        BookTurnPage(self); //檢查玩家是否翻頁
    }

}

void Book_DetectButtonOn(Elements *self){ //針對返回遊戲頁面鍵
    Book *Obj = ((Book *)(self->pDerivedObj));
    //float scale = 1.25;
    if((mouse.x >= Obj->X[0])&&(mouse.x <= Obj->X[0]+Obj->button_W[0])&&(mouse.y >= Obj->Y[0])&&(mouse.y <= Obj->Y[0]+Obj->button_H[0])){ //如果滑鼠在按鈕範圍內
        al_draw_bitmap(Obj->high[0], Obj->XH[0], Obj->YH[0], 0);
        Obj->over_button = true;
    }
    else{
        al_draw_bitmap(Obj->button[0], Obj->X[0], Obj->Y[0], 0);
        Obj->over_button = false;
    }
}

int BookTurnPage(Elements *self){
    Book *Obj = ((Book *)(self->pDerivedObj));
    //float scale = 1.25;
    int returnV = 0;
    if(key_state[ALLEGRO_KEY_D] && Obj->pressA == 0){ //如果按下D
        al_play_sample_instance(Obj->PageTurn_sample_instance);
        al_draw_bitmap(Obj->high[1], Obj->XH[1], Obj->YH[1], 0);
        Obj->pressD = 1;
        returnV = 0;
    }
    else{ //如果現在這個瞬間沒有按下D而且上一刻是按住D的狀態，再進行翻頁的動作
        if(Obj->pressD){
            al_play_sample_instance(Obj->PageTurn_sample_instance);
            Obj->pressD = 0;
            returnV = 1;
        }
        
    }
    
    if(key_state[ALLEGRO_KEY_A] && Obj->pressD == 0){ //如果按下A且前面沒有按下D
        al_play_sample_instance(Obj->PageTurn_sample_instance);
        al_draw_bitmap(Obj->high[2], Obj->XH[2], Obj->YH[2], 0);
        Obj->pressA = 1;
        returnV = 0;
    } //如果現在這個瞬間沒有按下D而且上一刻是按住D的狀態，再進行翻頁的動作
    else if(!key_state[ALLEGRO_KEY_A] && Obj->pressD == 0){
        if(Obj->pressA){
            al_play_sample_instance(Obj->PageTurn_sample_instance);
            Obj->pressA = 0;
            returnV = 2;
        }
    }

    return returnV;
}

void Book_destroy(Elements *self)
{
    Book *Obj = ((Book *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background_image;
    al_destroy_bitmap(background); //【destory背景圖片(先宣告才能刪除)】
    al_destroy_bitmap(Obj->button[0]);
    al_destroy_bitmap(Obj->button[1]);
    al_destroy_bitmap(Obj->button[2]);
    al_destroy_font(Obj->font);

    al_destroy_sample(Obj->ButtonClick);
    al_destroy_sample_instance(Obj->Click_sample_instance);
    al_destroy_sample(Obj->PageTurn);
    al_destroy_sample_instance(Obj->PageTurn_sample_instance);

    al_destroy_bitmap(Obj->cover);

    free(Obj);
    free(self);
}
