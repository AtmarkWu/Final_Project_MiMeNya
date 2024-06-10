#include "capture.h"
#include "../shapes/Rectangle.h"
/*
   [Capture function]
*/
Elements *New_Capture(int label)
{
    Capture *pDerivedObj = (Capture *)malloc(sizeof(Capture));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->Catch = al_load_bitmap("assets/image/capture.png");

    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->Catch);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->Catch);
    pDerivedObj->x = mouse.x;
    pDerivedObj->y = mouse.y;
    pDerivedObj->Ready = 0;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);

    //設定捕捉音效
    pDerivedObj->Capture = al_load_sample("assets/sound/game/Key_C.wav");
    al_reserve_samples(20);
    pDerivedObj->Capture_sample_instance = al_create_sample_instance(pDerivedObj->Capture);
    al_set_sample_instance_playmode(pDerivedObj->Capture_sample_instance, ALLEGRO_PLAYMODE_ONCE);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->Capture_sample_instance, al_get_default_mixer());
    //設定音效音量
    al_set_sample_instance_gain(pDerivedObj->Capture_sample_instance, 1);

    //設定關閉套環音效
    pDerivedObj->Nothing = al_load_sample("assets/sound/game/No_caught.wav");
    al_reserve_samples(20);
    pDerivedObj->Nothing_sample_instance = al_create_sample_instance(pDerivedObj->Nothing);
    al_set_sample_instance_playmode(pDerivedObj->Nothing_sample_instance, ALLEGRO_PLAYMODE_ONCE);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->Nothing_sample_instance, al_get_default_mixer());
    //設定音效音量
    al_set_sample_instance_gain(pDerivedObj->Nothing_sample_instance, 1);

    //設定關閉套環音效
    pDerivedObj->Gotcha = al_load_sample("assets/sound/game/Gotcha.wav");
    al_reserve_samples(20);
    pDerivedObj->Gotcha_sample_instance = al_create_sample_instance(pDerivedObj->Gotcha);
    al_set_sample_instance_playmode(pDerivedObj->Gotcha_sample_instance, ALLEGRO_PLAYMODE_ONCE);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->Gotcha_sample_instance, al_get_default_mixer());
    //設定音效音量
    al_set_sample_instance_gain(pDerivedObj->Gotcha_sample_instance, 1);

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Capture_update;
    pObj->Interact = Capture_interact;
    pObj->Draw = Capture_draw;
    pObj->Destroy = Capture_destory;
    return pObj;
}

void Capture_update(Elements *self) {
    if(gameFunction == -1){
        Capture *Obj = ((Capture *)(self->pDerivedObj));
        //檢測現在是否開啟捕捉模式
        if(key_state[ALLEGRO_KEY_C] && Obj->Ready == 0){
            al_play_sample_instance(Obj->Capture_sample_instance);
            printf("Start Capturing\n");
            Obj->Ready = 1;
        }
        else if(key_state[ALLEGRO_KEY_X] && Obj->Ready){
            //如果按下C的時候是開啟捕捉模式 -> 再按一次關閉
            al_play_sample_instance(Obj->Nothing_sample_instance);
            Obj->Ready = 0;
        }

        //根據滑鼠位置移動hitbox跟圖片
        Shape *hitbox = Obj->hitbox;
        hitbox->update_center_x(hitbox, mouse.x - Obj->x);
        hitbox->update_center_y(hitbox, mouse.y - Obj->y);
        Obj->x = mouse.x;
        Obj->y = mouse.y;

        //如果抓到貓咪，就關閉捕捉模式(項圈消失)
        if(catchIT){
            printf("Catch a Cat!\n");
            al_play_sample_instance(Obj->Gotcha_sample_instance);
            Obj->Ready = 0;
            catchIT = false; //復原抓取狀態
        }
    }
}

void Capture_interact(Elements *self, Elements *tar) {

}

void Capture_draw(Elements *self)
{
    if(gameFunction == -1){
        Capture *Obj = ((Capture *)(self->pDerivedObj));
        if(Obj->Ready){ //如果有開啟捕捉模式(按鍵c)
            al_draw_bitmap(Obj->Catch, Obj->x, Obj->y, 0);
        }
    }
    
}
void Capture_destory(Elements *self)
{
    Capture *Obj = ((Capture *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->Catch);
    free(Obj->hitbox);
    al_destroy_sample(Obj->Capture);
    al_destroy_sample_instance(Obj->Capture_sample_instance);
    al_destroy_sample(Obj->Nothing);
    al_destroy_sample_instance(Obj->Nothing_sample_instance);
    al_destroy_sample(Obj->Gotcha);
    al_destroy_sample_instance(Obj->Gotcha_sample_instance);
    free(Obj);
    free(self);
}
