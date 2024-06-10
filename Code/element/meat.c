#include "meat.h"
//#include "../global.h"
#include "../shapes/Circle.h"
#include <allegro5/allegro_primitives.h>
//肉泥拖曳功能，若沒有該種類的肉泥(數量為0)，就無法拖曳
//每拖出去一次，就減少一個肉泥持有數

Elements *New_Meat(int label)
{
    Meat *pDerivedObj = (Meat *)malloc(sizeof(Meat));
    Elements *pObj = New_Elements(label);
    pDerivedObj->img = al_load_bitmap("assets/image/meat.png");
    pDerivedObj->img1 = al_load_bitmap("assets/image/meat.png");
    pDerivedObj->img2 = al_load_bitmap("assets/image/meat.png");
    pDerivedObj->img3 = al_load_bitmap("assets/image/meat.png");
    pDerivedObj->x = mouse.x;
    pDerivedObj->y = mouse.y;
    pDerivedObj->posx = 0;
    pDerivedObj->posy = 0;
    pDerivedObj->r = 10;
    pDerivedObj->in = -1;
    pDerivedObj->click = 0;
    pDerivedObj->deleteFlag = false;
    lenMeat = 0;
    pDerivedObj->currentColor = 0;
    for(int i=0;i<100;i++){
        meatsX[i] = 0;
        meatsY[i] = 0;
        meatType[i] = 0;
    }
    //pDerivedObj->meatX = 0;
    //pDerivedObj->meatY = 0;
    //pDerivedObj->shouldDrawMeat = false;
    pDerivedObj->color = al_map_rgb(255, 0, 0);
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x,
                                     pDerivedObj->y,
                                     pDerivedObj->r);

    pDerivedObj->currentMeat = 0;

    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Basket_L;

    //設定拾起音效
    pDerivedObj->PickUp = al_load_sample("assets/sound/game/pick_up.wav");
    al_reserve_samples(20);
    pDerivedObj->PickUp_sample_instance = al_create_sample_instance(pDerivedObj->PickUp);
    al_set_sample_instance_playmode(pDerivedObj->PickUp_sample_instance, ALLEGRO_PLAYMODE_ONCE);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->PickUp_sample_instance, al_get_default_mixer());
    //設定音效音量
    al_set_sample_instance_gain(pDerivedObj->PickUp_sample_instance, 1);
    
    //設定放下音效
    pDerivedObj->PutDown = al_load_sample("assets/sound/game/put_down.wav");
    al_reserve_samples(20);
    pDerivedObj->PutDown_sample_instance = al_create_sample_instance(pDerivedObj->PutDown);
    al_set_sample_instance_playmode(pDerivedObj->PutDown_sample_instance, ALLEGRO_PLAYMODE_ONCE);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->PutDown_sample_instance, al_get_default_mixer());
    //設定音效音量
    al_set_sample_instance_gain(pDerivedObj->PutDown_sample_instance, 1);

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = Meat_draw;
    pObj->Update = Meat_update;
    pObj->Interact = Meat_interact;
    pObj->Destroy = Meat_destory;
    return pObj;
}
void Meat_update(Elements *self)
{
    if(gameFunction == -1){ //如果現在是遊戲功能開啟，再進行更新
        Meat *Obj = ((Meat *)(self->pDerivedObj));
        Shape *hitbox = Obj->hitbox;
        hitbox->update_center_x(hitbox, mouse.x - Obj->x);
        hitbox->update_center_y(hitbox, mouse.y - Obj->y);
        Obj->x = mouse.x;
        Obj->y = mouse.y;
    }
}
void Meat_interact(Elements *self, Elements *tar)
{
    if(gameFunction == -1){ //如果現在是遊戲功能開啟，再進行互動感應
        Meat *Obj = ((Meat *)(self->pDerivedObj));
        if(!mouse_state[1])
        {
            if (Obj->click){
                al_play_sample_instance(Obj->PutDown_sample_instance);
                meatsX[lenMeat] = mouse.x;
                meatsY[lenMeat] = mouse.y;
                meatType[lenMeat] = Obj->currentColor;
                lenMeat++;
                OwnMeat[Obj->currentMeat]--; //拖曳出去放開後，持有數減一
            }
            Obj->click = 0;
        }
        else if (tar->label == Basket_L)
        {
            Basket *Obj2 = ((Basket *)(tar->pDerivedObj));
            if (Obj->hitbox->overlap(Obj->hitbox, Obj2->hitbox) && mouse_state[1])
            {
                if(OwnMeat[1] != 0){ //如果擁有該種類的肉泥才能拖曳
                    al_play_sample_instance(Obj->PickUp_sample_instance);
                    Obj->click = 1;
                    Obj->color = al_map_rgb(222, 73, 53);
                    Obj->in = Basket_L;
                    Obj->currentColor = 1;
                    Obj->currentMeat = 1;
                }
            }
            if (Obj->hitbox->overlap(Obj->hitbox, Obj2->hitbox1) && mouse_state[1])
            {
                if(OwnMeat[2] != 0){ //如果擁有該種類的肉泥才能拖曳
                    al_play_sample_instance(Obj->PickUp_sample_instance);
                    Obj->click = 1;
                    Obj->color = al_map_rgb(150, 191, 210);
                    Obj->in = Basket_L;
                    Obj->currentColor = 2;
                    Obj->currentMeat = 2;
                }
            }
            if (Obj->hitbox->overlap(Obj->hitbox, Obj2->hitbox2) && mouse_state[1])
            {
                if(OwnMeat[3] != 0){ //如果擁有該種類的肉泥才能拖曳
                    al_play_sample_instance(Obj->PickUp_sample_instance);
                    Obj->click = 1;
                    Obj->color = al_map_rgb(250, 164, 147);
                    Obj->in = Basket_L;
                    Obj->currentColor = 3;
                    Obj->currentMeat = 3;     
                }
            }
            if (Obj->hitbox->overlap(Obj->hitbox, Obj2->hitbox3) && mouse_state[1])
            {
                if(OwnMeat[4] != 0){ //如果擁有該種類的肉泥才能拖曳
                    al_play_sample_instance(Obj->PickUp_sample_instance);
                    Obj->click = 1;
                    Obj->color = al_map_rgb(96, 152, 151);
                    Obj->in = Basket_L;
                    Obj->currentColor = 4;
                    Obj->currentMeat = 4;
                }
            }

        }
    }

}

//if mouse_button_down -> draw
void Meat_draw(Elements *self)
{
    if(gameFunction == -1){ //如果現在是遊戲功能，再畫出肉泥
        Meat *Obj = ((Meat *)(self->pDerivedObj));
        if(Obj->click == 1 && mouse_state[1])
        {
            al_draw_circle(Obj->x, Obj->y, Obj->r, Obj->color, 10);
        }
        for(int i=0;i<lenMeat;i++){
            //al_draw_bitmap(Obj->img1, Obj->meatsX[i], Obj->meatsY[i], 0);
            if(meatType[i] == 1 || meatType[i] == 2 || meatType[i] == 3 || meatType[i] == 4){
                al_draw_bitmap(Obj->img, meatsX[i]-35, meatsY[i]-10, 0);
            }
        }
    }
}
void Meat_destory(Elements *self)
{
    Meat *Obj = ((Meat *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    al_destroy_bitmap(Obj->img1);
    al_destroy_bitmap(Obj->img2);
    al_destroy_bitmap(Obj->img3);

    al_destroy_sample(Obj->PickUp);
    al_destroy_sample_instance(Obj->PickUp_sample_instance);

    al_destroy_sample(Obj->PutDown);
    al_destroy_sample_instance(Obj->PutDown_sample_instance);

    free(Obj->hitbox);
    free(Obj);
    free(self);
}