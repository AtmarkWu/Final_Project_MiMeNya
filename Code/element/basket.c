#include "basket.h"
#include "../shapes/Rectangle.h"
#include "../shapes/Circle.h"
#include <allegro5/allegro_primitives.h>
//畫出籃子&目前該肉泥持有數
/*
   [Basket function]
*/
Elements *New_Basket(int label)
{
    Basket *pDerivedObj = (Basket *)malloc(sizeof(Basket));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/basket_red.png");
    pDerivedObj->img1 = al_load_bitmap("assets/image/basket_blue.png");
    pDerivedObj->img2 = al_load_bitmap("assets/image/basket_pink.png");
    pDerivedObj->img3 = al_load_bitmap("assets/image/basket_green.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 170;
    pDerivedObj->y = HEIGHT - pDerivedObj->height-50;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    pDerivedObj->hitbox1 = New_Rectangle(pDerivedObj->x+300,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width+300,
                                        pDerivedObj->y + pDerivedObj->height);
    pDerivedObj->hitbox2 = New_Rectangle(pDerivedObj->x+600,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width+600,
                                        pDerivedObj->y + pDerivedObj->height);
    pDerivedObj->hitbox3 = New_Rectangle(pDerivedObj->x+900,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width+900,
                                        pDerivedObj->y + pDerivedObj->height);                                                                        
    pDerivedObj->r = 30;

    //肉泥持有數字體設定
    pDerivedObj->font = al_load_ttf_font("assets/font/GenSenRounded-M.ttc", 20, 0);

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Basket_update;
    pObj->Interact = Basket_interact;
    pObj->Draw = Basket_draw;
    pObj->Destroy = Basket_destory;
    return pObj;
}
void Basket_update(Elements *self) {}
void Basket_interact(Elements *self, Elements *tar) {}

void Basket_draw(Elements *self)
{
    Basket *Obj = ((Basket *)(self->pDerivedObj));
    int circleX, circley;
    circleX = Obj->x+al_get_bitmap_width(Obj->img)/2;
    circley = Obj->y+120;
    int adjust = 10; //for持有數數字位置微調

    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
    al_draw_filled_circle(circleX, circley, Obj->r, al_map_rgb(255, 255, 255));
    HowManyMeatIHave(self, circleX, circley-adjust, 1);

    al_draw_bitmap(Obj->img1, Obj->x+300, Obj->y, 0);
    al_draw_filled_circle(circleX+300, circley, Obj->r, al_map_rgb(255, 255, 255));
    HowManyMeatIHave(self, circleX+300, circley-adjust, 2);

    al_draw_bitmap(Obj->img2, Obj->x+600, Obj->y, 0);
    al_draw_filled_circle(circleX+600, circley, Obj->r, al_map_rgb(255, 255, 255));
    HowManyMeatIHave(self, circleX+600, circley-adjust, 3);

    al_draw_bitmap(Obj->img3, Obj->x+900, Obj->y, 0);
    al_draw_filled_circle(circleX+900, circley, Obj->r, al_map_rgb(255, 255, 255));
    HowManyMeatIHave(self, circleX+900, circley-adjust, 4);

}

void HowManyMeatIHave(Elements *self, int posX, int posY, int kind){
    //逐字拆解目前肉泥持有數，並畫出來
    int Number[3] = {0}; //最多3位數的陣列(100個肉泥為上限)
    int temp = OwnMeat[kind];
    int index = 0;
    int gap = 0;
    if(temp > 0){
        while(temp != 0){
            Number[index] = temp % 10;
            temp /= 10;
            index++;
        }
        for(int i = index-1 ; i >= 0 ; i--){ //到著跑，即可畫出從最小位~最高位
            PrintMeat(self, Number[i], gap, posX, posY);
            gap += 10; //增加x座標往後畫
        }
    }
    else{
        PrintMeat(self, 0, gap, posX, posY);
    }

}

void PrintMeat(Elements *self, int num, int gap, int posX, int posY){
    //依照現在的數字是啥就印出誰
    Basket *Obj = ((Basket *)(self->pDerivedObj));
    switch(num){
        case 0:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), posX+gap, posY, ALLEGRO_ALIGN_CENTER, "0");
            break;
        case 1:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), posX+gap, posY, ALLEGRO_ALIGN_CENTER, "1");
            break;
        case 2:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), posX+gap, posY, ALLEGRO_ALIGN_CENTER, "2");
            break;
        case 3:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), posX+gap, posY, ALLEGRO_ALIGN_CENTER, "3");
            break;
        case 4:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), posX+gap, posY, ALLEGRO_ALIGN_CENTER, "4");
            break;
        case 5:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), posX+gap, posY, ALLEGRO_ALIGN_CENTER, "5");
            break;
        case 6:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), posX+gap, posY, ALLEGRO_ALIGN_CENTER, "6");
            break;
        case 7:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), posX+gap, posY, ALLEGRO_ALIGN_CENTER, "7");
            break;
        case 8:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), posX+gap, posY, ALLEGRO_ALIGN_CENTER, "8");
            break;
        case 9:
            al_draw_text(Obj->font, al_map_rgb(0, 0, 0), posX+gap, posY, ALLEGRO_ALIGN_CENTER, "9");
            break;
        default:
            break;
    }
}

void Basket_destory(Elements *self)
{
    Basket *Obj = ((Basket *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    al_destroy_bitmap(Obj->img1);
    al_destroy_bitmap(Obj->img2);
    al_destroy_bitmap(Obj->img3);
    free(Obj->hitbox);
    free(Obj->hitbox1);
    free(Obj->hitbox2);
    free(Obj->hitbox3);

    al_destroy_font(Obj->font);

    free(Obj);
    free(self);
}
