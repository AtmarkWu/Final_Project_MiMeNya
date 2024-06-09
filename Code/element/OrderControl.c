#include "OrderControl.h"
#include "../shapes/Rectangle.h"
/*
   [OrderControl function]
*/
Elements *New_OrderControl(int label)
{
    OrderControl *pDerivedObj = (OrderControl *)malloc(sizeof(OrderControl));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    //設定背景圖片
    pDerivedObj->background = al_load_bitmap("assets/image/Order/orderBG.png");

    //回到遊戲主畫面的按鈕設定
    pDerivedObj->button = al_load_bitmap("assets/image/GameButton/back.png");
    pDerivedObj->highlight = al_load_bitmap("assets/image/GameButton/back_h.png");
    pDerivedObj->width = 74;
    pDerivedObj->height = 69;

    
    //一進來初始化先把滑鼠點擊狀態清空
    mouse_state[1] = false;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = OrderControl_update;
    pObj->Interact = OrderControl_interact;
    pObj->Draw = OrderControl_draw;
    pObj->Destroy = OrderControl_destory;
    return pObj;
}

void OrderControl_update(Elements *self) {
    if(gameFunction == 2){ //如果是現在是開啟訂單功能，再去做裡面的相關感應
        OrderControl *Obj = ((OrderControl *)(self->pDerivedObj));
        Order_DetectButtonOn(self);
        //滑鼠點擊事件更新
        if(mouse_state[1]){
            if(Obj->over_button){
                printf("Back to game\n");
                gameFunction = -1; //回到遊戲內畫面
            }
        }
    }


}

void OrderControl_interact(Elements *self, Elements *tar) {
}

// void SeeDetail(Elements *self){
//     OrderControl *Obj = ((OrderControl *)(self->pDerivedObj));
//     for(int i = 0 ; i < FrameUD ; i++){
//         if((mouse.x >= Obj->x[i])&&(mouse.x <= Obj->x[i]+Obj->width[i])&&(mouse.y >= Obj->y[i])&&(mouse.y <= Obj->y[i]+Obj->height[i])){ //如果滑鼠在預視圖範圍內
//             Obj->Open[i] = true;
//             Obj->current_open = i; //設定打開的標籤為第i個
//             printf("Open!\n");
//         }
//         else{ //如果在滑鼠點擊的當下不是在預視圖內，且介紹是被打開的，就關起來
//             if(Obj->Open[i] == true){
//                 Obj->Open[i] = false;
//                 Obj->current_open = -1; //如果沒有任何介紹被打開，就設為-1
//                 printf("Close\n");
//             }
//         }
//     }
// }

void OrderControl_draw(Elements *self)
{
    if(gameFunction == 2){ //如果現在gameFunction是訂單功能開啟
        OrderControl *Obj = ((OrderControl *)(self->pDerivedObj));
        al_draw_bitmap(Obj->background, 0, 0, 0); //畫出背景
        printf("in order function: %d, gameFunction = %d\n", al_get_bitmap_width(Obj->background), gameFunction);

        //畫出按鈕並開啟回主畫面的按鈕感應功能
        Obj->x = 800;
        Obj->y = 30;
        al_draw_bitmap(Obj->button, Obj->x, Obj->y, 0);

        Order_DetectButtonOn(self);
    }
    
}

//內部OrderControl要使用的函式
void Order_DetectButtonOn(Elements *self){
    OrderControl *Obj = ((OrderControl *)(self->pDerivedObj));
    if((mouse.x >= Obj->x)&&(mouse.x <= Obj->x+Obj->width)&&(mouse.y >= Obj->y)&&(mouse.y <= Obj->y+Obj->height)){ //如果滑鼠在按鈕範圍內
        al_draw_bitmap(Obj->highlight, Obj->x-10, Obj->y-5, 0);
        Obj->over_button = true;
    }
    else{
        Obj->over_button = false;
    }
}

// void HowManyCatIHave(Elements *self, int Cat_n){ //逐字拆解目前數字，並畫出來
//     //printf("Draw Number\n");
//     int Number[MaxCat] = {0};
//     int NumberLen = 0;
//     int ten = 1;
//     int index = 0;
//     int gap = 0;
//     while(ten <= Cat_n){
//         ten *= 10;
//         NumberLen++;
//     }
//     while(Cat_n != 0){
//         Number[index] = Cat_n % 10;
//         Cat_n /= 10;
//         index++;
//     }
//     for(int i = NumberLen-1 ; i >= 0 ; i--){ //到著跑，即可畫出從最小位~最高位
//         PrintNumber(self, Number[i], gap);
//         //printf("--> print: %d\n", Number[i]);
//         gap += 30; //增加x座標往後畫
//     }
// }

// void PrintNumber(Elements *self, int num, int gap){ //依照現在的數字是啥就印出誰
//     OrderControl *Obj = ((OrderControl *)(self->pDerivedObj));
//     //printf("--> current num is %d\n", num);
//     switch(num){
//         case 0:
//             al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->titleX+gap, Obj->titleY, ALLEGRO_ALIGN_CENTER, "0");
//             break;
//         case 1:
//             al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->titleX+gap, Obj->titleY, ALLEGRO_ALIGN_CENTER, "1");
//             break;
//         case 2:
//             al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->titleX+gap, Obj->titleY, ALLEGRO_ALIGN_CENTER, "2");
//             break;
//         case 3:
//             al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->titleX+gap, Obj->titleY, ALLEGRO_ALIGN_CENTER, "3");
//             break;
//         case 4:
//             al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->titleX+gap, Obj->titleY, ALLEGRO_ALIGN_CENTER, "4");
//             break;
//         case 5:
//             al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->titleX+gap, Obj->titleY, ALLEGRO_ALIGN_CENTER, "5");
//             break;
//         case 6:
//             al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->titleX+gap, Obj->titleY, ALLEGRO_ALIGN_CENTER, "6");
//             break;
//         case 7:
//             al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->titleX+gap, Obj->titleY, ALLEGRO_ALIGN_CENTER, "7");
//             break;
//         case 8:
//             al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->titleX+gap, Obj->titleY, ALLEGRO_ALIGN_CENTER, "8");
//             break;
//         case 9:
//             al_draw_text(Obj->font, al_map_rgb(0, 0, 0), Obj->titleX+gap, Obj->titleY, ALLEGRO_ALIGN_CENTER, "9");
//             break;
//         default:
//             break;
//     }
// }

void OrderControl_destory(Elements *self)
{
    OrderControl *Obj = ((OrderControl *)(self->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);

    al_destroy_bitmap(Obj->button);
    al_destroy_bitmap(Obj->highlight);


    free(Obj);
    free(self);
}
