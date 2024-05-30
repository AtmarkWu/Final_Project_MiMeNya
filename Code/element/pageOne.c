#include "pageOne.h"
#include "../shapes/Rectangle.h"
#define FrameUD 2
/*
   [PageOne function]
*/
Elements *New_PageOne(int label)
{
    PageOne *pDerivedObj = (PageOne *)malloc(sizeof(PageOne));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    //設定第一頁的預視圖([0]為上方的 | [1]為下方的 || 標籤與索引值同步)
    pDerivedObj->frame[0] = al_load_bitmap("assets/image/BookButton/frame.png");
    pDerivedObj->decFrame[0] = al_load_bitmap("assets/image/BookButton/frame_dec.png");
    pDerivedObj->width[0] = al_get_bitmap_width(pDerivedObj->frame[0]);
    pDerivedObj->height[0] = al_get_bitmap_height(pDerivedObj->frame[0]);
    pDerivedObj->x[0] = 80;
    pDerivedObj->y[0] = 50;
    pDerivedObj->frame[1] = al_load_bitmap("assets/image/BookButton/frame.png");
    pDerivedObj->decFrame[1] = al_load_bitmap("assets/image/BookButton/frame_dec.png");
    pDerivedObj->width[1] = al_get_bitmap_width(pDerivedObj->frame[1]);
    pDerivedObj->height[1] = al_get_bitmap_height(pDerivedObj->frame[1]);
    pDerivedObj->x[1] = 80;
    pDerivedObj->y[1] = pDerivedObj->x[0]+250;

    //其他要顯示在【預視圖】上面的東西(貓咪、資料、是否持有)
    int gap = 65;
    pDerivedObj->NoContent = al_load_bitmap("assets/image/BookButton/NO.png");
    pDerivedObj->Content[0] = al_load_bitmap("assets/image/BookButton/cat1.png");
    pDerivedObj->C_w[0] = al_get_bitmap_width(pDerivedObj->Content[0]);
    pDerivedObj->C_h[0] = al_get_bitmap_height(pDerivedObj->Content[0]);
    pDerivedObj->Cx[0] = pDerivedObj->x[0]+gap; //第一格的x偏移
    pDerivedObj->Cy[0] = pDerivedObj->y[0]+((pDerivedObj->height[0])/2)-((pDerivedObj->C_h[0])/2); //第一格的y置中
    pDerivedObj->Content[1] = al_load_bitmap("assets/image/BookButton/cat2.png");
    pDerivedObj->C_w[1] = al_get_bitmap_width(pDerivedObj->Content[1]);
    pDerivedObj->C_h[1] = al_get_bitmap_height(pDerivedObj->Content[1]);
    pDerivedObj->Cx[1] = pDerivedObj->x[1]+gap; //第二格的x偏移
    pDerivedObj->Cy[1] = pDerivedObj->y[1]+((pDerivedObj->height[1])/2)-((pDerivedObj->C_h[1])/2); //第二格的y置中
    //標籤設置
    pDerivedObj->LackSign = al_load_bitmap("assets/image/BookButton/lack.png");
    pDerivedObj->GetSign = al_load_bitmap("assets/image/BookButton/get.png");
    pDerivedObj->NewSign = al_load_bitmap("assets/image/BookButton/Type_new.png");

    //細節圖背景設定
    pDerivedObj->Detail = al_load_bitmap("assets/image/BookButton/detail.png");
    pDerivedObj->Open[0] = false; //對應到第一格
    pDerivedObj->Open[1] = false; //對應到第二格

    //其他要顯示在【介紹】上面的東西(貓咪、資料、是否為新獲得)
    int posX = 160;
    int posY = 250;
    pDerivedObj->D_content[0] = al_load_bitmap("assets/image/BookButton/cat1_d.png");
    pDerivedObj->D_w[0] = al_get_bitmap_width(pDerivedObj->D_content[0]);
    pDerivedObj->D_h[0] = al_get_bitmap_height(pDerivedObj->D_content[0]);
    pDerivedObj->Dx[0] = posX+30;
    pDerivedObj->Dy[0] = posY;
    pDerivedObj->D_content[1] = al_load_bitmap("assets/image/BookButton/cat2_d.png");
    pDerivedObj->D_w[1] = al_get_bitmap_width(pDerivedObj->D_content[1]);
    pDerivedObj->D_h[1] = al_get_bitmap_height(pDerivedObj->D_content[1]);
    pDerivedObj->Dx[1] = posX;
    pDerivedObj->Dy[1] = posY;

    
    //一進來初始化先把滑鼠點擊狀態清空
    mouse_state[1] = false;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = PageOne_update;
    pObj->Interact = PageOne_interact;
    pObj->Draw = PageOne_draw;
    pObj->Destroy = PageOne_destory;
    return pObj;
}

void PageOne_update(Elements *self) {
    //PageOne *Obj = ((PageOne *)(self->pDerivedObj));

    //滑鼠點擊事件更新
    if(mouse_state[1]){
        SeeDetail(self);
    }

}

void PageOne_interact(Elements *self, Elements *tar) {
}

void SeeDetail(Elements *self){
    PageOne *Obj = ((PageOne *)(self->pDerivedObj));
    for(int i = 0 ; i < FrameUD ; i++){
        if((mouse.x >= Obj->x[i])&&(mouse.x <= Obj->x[i]+Obj->width[i])&&(mouse.y >= Obj->y[i])&&(mouse.y <= Obj->y[i]+Obj->height[i])){ //如果滑鼠在預視圖範圍內
            Obj->Open[i] = true;
            Obj->current_open = i; //設定打開的標籤為第i個
            printf("Open!\n");
        }
        else{ //如果在滑鼠點擊的當下不是在預視圖內，且介紹是被打開的，就關起來
            if(Obj->Open[i] == true){
                Obj->Open[i] = false;
                Obj->current_open = -1; //如果沒有任何介紹被打開，就設為-1
                printf("Close\n");
            }
        }
    }
}

void PageOne_draw(Elements *self)
{
    PageOne *Obj = ((PageOne *)(self->pDerivedObj));
    int gap = 200;
    //畫出預視圖框框
    for(int i = 0 ; i < FrameUD ; i++){
        al_draw_bitmap(Obj->decFrame[i], Obj->x[i]-55, Obj->y[i]-20, 0);
        //畫出要顯示在上面的貓咪縮圖、資訊等等
        if(Own[i]){ //如果是已經擁有的貓 -> 顯示縮圖
            al_draw_bitmap(Obj->Content[i], Obj->Cx[i], Obj->Cy[i], 0);
            if(NewCatOrNot[0]){ //如果是新獲得的貓 -> 顯示New
                al_draw_bitmap(Obj->NewSign, Obj->Cx[i]+gap, Obj->Cy[i], 0);
            }
            else{ //如果不是新獲得的 -> 顯示get
                al_draw_bitmap(Obj->GetSign, Obj->Cx[i]+gap, Obj->Cy[i], 0);
            }
        }
        else{ //否則顯示未知&缺少
            al_draw_bitmap(Obj->NoContent, Obj->Cx[i], Obj->Cy[i], 0);
            al_draw_bitmap(Obj->LackSign, Obj->Cx[i]+gap, Obj->Cy[i], 0);
        }
    }

    //根據Open跟current_open決定是否畫出介紹圖
    for(int i = 0 ; i < FrameUD ; i++){
        //如果介紹有被打開且標籤對應正確，而且該貓咪已獲得過
        if(Obj->Open[i] && Obj->current_open == i && Own[i]){ 
            //畫出該細節圖應該要有的內容(主圖、貓咪、介紹、持有數等等)
            al_draw_bitmap(Obj->Detail, 0, 0, 0);
            al_draw_bitmap(Obj->D_content[i], Obj->Dx[i], Obj->Dy[i], 0);
            if(NewCatOrNot[0]){ //如果該貓咪是新的 -> 點進來後已經看過內容(不再是新的)
                // -> 在預視圖要改成顯示get
                NewCatOrNot[0] = false;
            }
        }
    }
}

void PageOne_destory(Elements *self)
{
    PageOne *Obj = ((PageOne *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->frame[0]);
    al_destroy_bitmap(Obj->frame[1]);
    al_destroy_bitmap(Obj->decFrame[0]);
    al_destroy_bitmap(Obj->decFrame[1]);
    //清除【預視圖】上資訊圖片
    al_destroy_bitmap(Obj->NoContent);
    al_destroy_bitmap(Obj->Content[0]);
    al_destroy_bitmap(Obj->Content[1]);
    al_destroy_bitmap(Obj->LackSign);
    al_destroy_bitmap(Obj->GetSign);
    al_destroy_bitmap(Obj->NewSign);
    //清除【介紹】上資訊圖片
    al_destroy_bitmap(Obj->D_content[0]);
    al_destroy_bitmap(Obj->D_content[1]);
    al_destroy_bitmap(Obj->Detail);
    free(Obj);
    free(self);
}
