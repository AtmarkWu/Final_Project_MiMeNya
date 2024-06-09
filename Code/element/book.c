#include "book.h"
#define ButtonNum 3
//回到遊戲畫面、上一頁、下一頁按鈕皆在此管理
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
    pDerivedObj->background_image = al_load_bitmap("assets/image/BookButton/BookBG.png");

    //【設定按鈕圖案】
    pDerivedObj->button[0] = al_load_bitmap("assets/image/BookButton/exit.png"); //回到遊戲畫面
    pDerivedObj->button_W[0] = al_get_bitmap_width(pDerivedObj->button[0]);
    pDerivedObj->button_H[0] = al_get_bitmap_height(pDerivedObj->button[0]);
    pDerivedObj->button[1] = al_load_bitmap("assets/image/BookButton/Next.png"); //下一頁
    pDerivedObj->button_W[1] = al_get_bitmap_width(pDerivedObj->button[1]);
    pDerivedObj->button_H[1] = al_get_bitmap_height(pDerivedObj->button[1]);
    pDerivedObj->button[2] = al_load_bitmap("assets/image/BookButton/previous.png"); //上一頁
    pDerivedObj->button_W[2] = al_get_bitmap_width(pDerivedObj->button[2]);
    pDerivedObj->button_H[2] = al_get_bitmap_height(pDerivedObj->button[2]);

    pDerivedObj->cover = al_load_bitmap("assets/image/BookButton/cover.png"); //圖鑑封面圖

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

        //先畫按鈕再畫遊戲物件，才不會在顯示介紹圖時被蓋掉
        int increments = 30;
        Obj->X[0] = 750;
        Obj->Y[0] = increments;
        increments += 250;
        al_draw_bitmap(Obj->button[0], Obj->X[0], Obj->Y[0], 0);
        for(int i = 1 ; i < ButtonNum ; i++){
            Obj->X[i] = 750;
            Obj->Y[i] = increments;
            al_draw_bitmap(Obj->button[i], Obj->X[i], Obj->Y[i], 0);
            increments += 130;
        }

        //繪製封面裝飾
        if(Page == 0){ //如果在封面頁再畫出來
            al_draw_bitmap(Obj->cover, 50, 30, 0);
        }
        
        Book_DetectButtonOn(self); //畫完正常按鈕後，檢查滑鼠是否停在按鈕上，並更改狀態

        BookTurnPage(self); //檢查玩家是否翻頁
    }

}

void Book_DetectButtonOn(Elements *self){ //針對返回遊戲頁面鍵
    Book *Obj = ((Book *)(self->pDerivedObj));
    float scale = 1.25;
    if((mouse.x >= Obj->X[0])&&(mouse.x <= Obj->X[0]+Obj->button_W[0])&&(mouse.y >= Obj->Y[0])&&(mouse.y <= Obj->Y[0]+Obj->button_H[0])){ //如果滑鼠在按鈕範圍內
        al_draw_scaled_bitmap(Obj->button[0], 0, 0, Obj->button_W[0], Obj->button_H[0], Obj->X[0]-15, Obj->Y[0]-5,  Obj->button_W[0]*scale, Obj->button_H[0]*scale, 0);
        Obj->over_button = true;
    }
    else{
        Obj->over_button = false;
    }
}

int BookTurnPage(Elements *self){
    Book *Obj = ((Book *)(self->pDerivedObj));
    float scale = 1.25;
    int returnV = 0;
    if(key_state[ALLEGRO_KEY_D]){ //如果按下D
        al_draw_scaled_bitmap(Obj->button[1], 0, 0, Obj->button_W[1], Obj->button_H[1], Obj->X[1]-15, Obj->Y[1]-5,  Obj->button_W[1]*scale, Obj->button_H[1]*scale, 0);
        Obj->pressD = 1;
        returnV = 0;
    }
    else{ //如果現在這個瞬間沒有按下D而且上一刻是按住D的狀態，再進行翻頁的動作
        if(Obj->pressD){
            Obj->pressD = 0;
            returnV = 1;
        }
    }
    
    if(key_state[ALLEGRO_KEY_A] && Obj->pressD == 0){ //如果按下A且前面沒有按下D
        al_draw_scaled_bitmap(Obj->button[2], 0, 0, Obj->button_W[2], Obj->button_H[2], Obj->X[2]-15, Obj->Y[2]-5,  Obj->button_W[2]*scale, Obj->button_H[2]*scale, 0);
        Obj->pressA = 1;
        returnV = 0;
    } //如果現在這個瞬間沒有按下D而且上一刻是按住D的狀態，再進行翻頁的動作
    else if(!key_state[ALLEGRO_KEY_A] && Obj->pressD == 0){
        if(Obj->pressA){
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

    al_destroy_bitmap(Obj->cover);

    free(Obj);
    free(self);
}
