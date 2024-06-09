#include "gamescene.h"

#define BUTTON_NUM 4
/*
   [GameScene function]
*/
Scene *New_GameScene(int label)
{
    GameScene *pDerivedObj = (GameScene *)malloc(sizeof(GameScene));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    //設定字體
    pDerivedObj->font = al_load_ttf_font("assets/font/GenSenRounded-M.ttc", 16, 0);
    pDerivedObj->title_x = 60;
    pDerivedObj->title_y = 75;
    //設定背景圖片
    pDerivedObj->background = al_load_bitmap("assets/image/BG/gameMainBG.png");
    //設定音樂
    pDerivedObj->BGM = al_load_sample("assets/sound/game_sound/cat_field_BGM-1.mp3");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->BGM);
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    //設定BGM音量
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.5);
    //設定遊戲主畫面的功能鍵&金錢條(先暫時用圖片)
    //圖鑑[0]、商店[1]、訂單[2]、回到主選單[3]
    pDerivedObj->button[0] = al_load_bitmap("assets/image/GameButton/book.png");
    pDerivedObj->highlight[0] = al_load_bitmap("assets/image/GameButton/book_h.png");
    pDerivedObj->button_w[0] = 112;
    pDerivedObj->button_h[0] = 65;

    pDerivedObj->button[1] = al_load_bitmap("assets/image/GameButton/shop.png");
    pDerivedObj->highlight[1] = al_load_bitmap("assets/image/GameButton/shop_h.png");
    pDerivedObj->button_w[1] = 84;
    pDerivedObj->button_h[1] = 83;

    pDerivedObj->button[2] = al_load_bitmap("assets/image/GameButton/order.png");
    pDerivedObj->highlight[2] = al_load_bitmap("assets/image/GameButton/order_h.png");
    pDerivedObj->button_w[2] = 84;
    pDerivedObj->button_h[2] = 111;

    pDerivedObj->button[3] = al_load_bitmap("assets/image/GameButton/back.png");
    pDerivedObj->highlight[3] = al_load_bitmap("assets/image/GameButton/back_h.png");
    pDerivedObj->button_w[3] = 74;
    pDerivedObj->button_h[3] = 69;

    pDerivedObj->Money = al_load_bitmap("assets/image/GameButton/money.png");

    pObj->pDerivedObj = pDerivedObj;

    //一進來初始化先把滑鼠點擊狀態清空
    mouse_state[1] = false;

    //設定遊戲功能頁面(初始化為預設)
    gameFunction = -1;

    // register 遊戲物件
    //_Register_elements(pObj, New_Floor(Floor_L));
    //_Register_elements(pObj, New_Teleport(Teleport_L));
    //_Register_elements(pObj, New_Tree(Tree_L));
    //_Register_elements(pObj, New_Character(Character_L));
    _Register_elements(pObj, New_Basket(Basket_L));
    _Register_elements(pObj, New_Meat(Meat_L));
    _Register_elements(pObj, New_catT(CatT_L));
    _Register_elements(pObj, New_Capture(Capture_L));

    // register 遊戲功能頁面
    //圖鑑
    _Register_elements(pObj, New_Book(Book_L));
    _Register_elements(pObj, New_PageOne(PageOne_L));
    //商店
    _Register_elements(pObj, New_Shop(Shop_L));
    _Register_elements(pObj, New_Buy(Buy_L));
    //訂單
    _Register_elements(pObj, New_OrderControl(OrderControl_L));

    // setting derived object function
    pObj->Update = game_scene_update;
    pObj->Draw = game_scene_draw;
    pObj->Destroy = game_scene_destroy;
    return pObj;
}

void game_scene_update(Scene *self)
{
    GameScene *Obj = ((GameScene*)(self->pDerivedObj));
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
                //printf("-> Interact with %d\n", inter_label);
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

    //遊戲內主功能(需要當下是"gameFunction == -1)
    if(gameFunction == -1){
        //撥放bgm
        al_play_sample_instance(Obj->sample_instance);

        //感測各功能按鈕狀態，並切換功能
        Game_DetectButtonOn(self);
        if(mouse_state[1]){ //當按鈕按下且在遊戲介面時
            if(Obj->over_button[0]){ //進入圖鑑[0]
                printf("In to Book\n");
                gameFunction = 0;
            }
            if(Obj->over_button[1]){ //進入商店[1]
                printf("In to Shop\n");
                al_stop_sample_instance(Obj->sample_instance);
                gameFunction = 1;
            }
            if(Obj->over_button[2]){ //進入訂單管理頁面[2]
                printf("In to Order\n");
                //不切換頁面，而是利用全域變數操控跳出來的畫面，同時截斷底下頁面的感應功能
                gameFunction = 2;
            }

            // if(Obj->over_button[3]){ //關閉遊戲(4)
            //     //如果滑鼠按下的時候在按鈕上 -> 準備要離開
            //     printf("Quit\n");
            //     self->scene_end = true;
            //     window = 4;
            // }
        }
    }
}

void game_scene_draw(Scene *self)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    GameScene *gs = ((GameScene *)(self->pDerivedObj));
    printf("in game: %d, gameFunction = %d\n", al_get_bitmap_width(gs->background), gameFunction);
    printf("Current Money: %d\n", TotalMoney);

    al_draw_bitmap(gs->background, 0, 0, 0);

    //畫出遊戲物件
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }

    if(gameFunction == -1){ //如果當前狀態是在遊戲畫面內，再畫出遊戲主畫面需要的物件
        //畫出功能按鈕
        int increments = 445;
        for(int i = 0 ; i < BUTTON_NUM ; i++){
            gs->X[i] = increments;
            gs->Y[i] = 30;
            al_draw_bitmap(gs->button[i], gs->X[i], gs->Y[i], 0);
            increments += 120;
        }

        Game_DetectButtonOn(self);

        //畫出金錢條&上面的數字(固定)
        al_draw_bitmap(gs->Money, 40, 20, 0);
        HowManyMoneyIHaveGAMESCENE(self);
    }

    
}

void Game_DetectButtonOn(Scene *self){
    GameScene *Obj = ((GameScene *)(self->pDerivedObj));
    for(int i = 0 ; i < BUTTON_NUM ; i++){
        if((mouse.x >= Obj->X[i])&&(mouse.x <= Obj->X[i]+Obj->button_w[i])&&(mouse.y >= Obj->Y[i])&&(mouse.y <= Obj->Y[i]+Obj->button_h[i])){ //如果滑鼠在按鈕範圍內
            al_draw_bitmap(Obj->highlight[i], Obj->X[i]-10, Obj->Y[i]-5, 0);
            Obj->over_button[i] = true;
        }
        else{
            Obj->over_button[i] = false;
        }
    }
}

void HowManyMoneyIHaveGAMESCENE(Scene *self){ //逐字拆解目前錢錢數字，並畫出來
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
            PrintMoneyGAMESCENE(self, Number[i], gap);
            gap += 10; //增加x座標往後畫
        }
    }
    else{
        PrintMoneyGAMESCENE(self, 0, gap);
    }

}

void PrintMoneyGAMESCENE(Scene *self, int num, int gap){ //依照現在的數字是啥就印出誰
    GameScene *Obj = ((GameScene *)(self->pDerivedObj));
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

void game_scene_destroy(Scene *self)
{
    GameScene *Obj = ((GameScene *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
    al_destroy_sample(Obj->BGM);
    al_destroy_sample_instance(Obj->sample_instance);
    //刪除字體
    al_destroy_font(Obj->font);
    //刪除按鈕&暫時的金錢條
    al_destroy_bitmap(Obj->button[0]);
    al_destroy_bitmap(Obj->button[1]);
    al_destroy_bitmap(Obj->button[2]);
    al_destroy_bitmap(Obj->button[3]);
    al_destroy_bitmap(Obj->highlight[0]);
    al_destroy_bitmap(Obj->highlight[1]);
    al_destroy_bitmap(Obj->highlight[2]);
    al_destroy_bitmap(Obj->highlight[3]);
    al_destroy_bitmap(Obj->Money);
    //刪除遊戲內元素(各功能的頁面、貓、肉泥等等)
    ElementVec allEle = _Get_all_elements(self);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    free(Obj);
    free(self);
}
