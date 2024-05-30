#include <allegro5/allegro_primitives.h>
#include "book.h"
#include <stdbool.h>
#define ButtonNum 3
//回到遊戲畫面、上一頁、下一頁按鈕皆在此管理
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
    pDerivedObj->button[0] = al_load_bitmap("assets/image/BookButton/exit.png"); //回到遊戲畫面
    pDerivedObj->button_W[0] = al_get_bitmap_width(pDerivedObj->button[0]);
    pDerivedObj->button_H[0] = al_get_bitmap_height(pDerivedObj->button[0]);
    pDerivedObj->button[1] = al_load_bitmap("assets/image/BookButton/Next.png"); //下一頁
    pDerivedObj->button_W[1] = al_get_bitmap_width(pDerivedObj->button[1]);
    pDerivedObj->button_H[1] = al_get_bitmap_height(pDerivedObj->button[1]);
    pDerivedObj->button[2] = al_load_bitmap("assets/image/BookButton/previous.png"); //上一頁
    pDerivedObj->button_W[2] = al_get_bitmap_width(pDerivedObj->button[2]);
    pDerivedObj->button_H[2] = al_get_bitmap_height(pDerivedObj->button[2]);

    //【設定音樂】
    pDerivedObj->song = al_load_sample("assets/sound/GameSceneBGM.mp3"); //未改，待加入新音樂
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.3);
    //設定字體位置
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;

    pObj->pDerivedObj = pDerivedObj;

    //一進來初始化先把滑鼠點擊狀態清空
    mouse_state[1] = false;

    // register 遊戲物件
    _Register_elements(pObj, New_PageOne(Page1Up_L));

    // setting derived object function
    pObj->Update = Book_update;
    pObj->Draw = Book_draw;
    pObj->Destroy = Book_destroy;
    return pObj;
}

void Book_update(Scene *self) //【事件更新】
{
    Book *Obj = ((Book *)(self->pDerivedObj));

    // update every element
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        allEle.arr[i]->Update(allEle.arr[i]);
    }

    // run interact for every element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        // run every interact object
        for (int j = 0; j < ele->inter_len; j++)
        {
            int inter_label = ele->inter_obj[j];
            ElementVec labelEle = _Get_label_elements(self, inter_label);
            for (int i = 0; i < labelEle.len; i++)
            {
                ele->Interact(ele, labelEle.arr[i]);
            }
        }
    }

    // remove element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->dele)
            _Remove_elements(self, ele);
    }

    //按鈕事件偵測
    Book_DetectButtonOn(self);
    if (mouse_state[1]) //檢查滑鼠左鍵按下的當下是否在按鈕上
    {
        if(Obj->over_button){ //回到遊戲內畫面
            printf("back to game\n");
            self->scene_end = true;
            window = 1;
        }
    }

    //鍵盤事件偵測(換頁功能)
    int dir = BookTurnPage(self); //接收方向，看是往前一頁還是往後一頁
    if(dir == 1){
        printf("forward\n");
    }
    else if(dir == 2){
        printf("backward\n");
    }
    else{
        printf("no dir\n");
    }
    
    return;
}

void Book_draw(Scene *self) //【菜單內要被畫出的東西】
{
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

    //畫出遊戲物件
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
    
    Book_DetectButtonOn(self); //畫完正常按鈕後，檢查滑鼠是否停在按鈕上，並更改狀態

    BookTurnPage(self); //檢查玩家是否翻頁

    al_play_sample_instance(Obj->sample_instance);
}

void Book_DetectButtonOn(Scene *self){ //針對返回遊戲頁面鍵
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

int BookTurnPage(Scene *self){
    Book *Obj = ((Book *)(self->pDerivedObj));
    float scale = 1.25;
    if(key_state[ALLEGRO_KEY_D]){
        al_draw_scaled_bitmap(Obj->button[1], 0, 0, Obj->button_W[1], Obj->button_H[1], Obj->X[1]-15, Obj->Y[1]-5,  Obj->button_W[1]*scale, Obj->button_H[1]*scale, 0);
        return 1;
    }
    else if(key_state[ALLEGRO_KEY_A]){ //如果按下A
        al_draw_scaled_bitmap(Obj->button[2], 0, 0, Obj->button_W[2], Obj->button_H[2], Obj->X[2]-15, Obj->Y[2]-5,  Obj->button_W[2]*scale, Obj->button_H[2]*scale, 0);
        return 2;
    }
    else{
        return 3;
    }
}

void Book_destroy(Scene *self)
{
    Book *Obj = ((Book *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background_image;
    al_destroy_bitmap(background); //【destory背景圖片(先宣告才能刪除)】
    al_destroy_bitmap(Obj->button[0]);
    al_destroy_bitmap(Obj->button[1]);
    al_destroy_bitmap(Obj->button[2]);
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    //刪除遊戲內元素
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    free(Obj);
    free(self);
}
