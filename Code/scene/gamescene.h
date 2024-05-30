#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED
#include "scene.h"
#include "../element/element.h"
#include "../element/charater.h"
#include "../element/floor.h"
#include "../element/teleport.h"
#include "../element/projectile.h"

#include "../element/basket.h"
#include "../element/meat.h"
#include "../element/CatT.h"
#include "../element/capture.h"

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [game scene object]
*/
typedef enum EleType
{
    Floor_L,
    Teleport_L,
    Character_L,
    Projectile_L,
    Basket_L,
    Meat_L,
    CatT_L,
    Capture_L
} EleType;

typedef struct _GameScene
{
    //設定字體
    ALLEGRO_FONT *font;
    //背景圖片
    ALLEGRO_BITMAP *background;
    //背景音樂
    ALLEGRO_SAMPLE *BGM;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    //各選單按鈕(圖鑑[0]、商店[1]、訂單[2]、回到主選單[3])
    ALLEGRO_BITMAP *button[4];
    ALLEGRO_BITMAP *highlight[4]; //滑鼠在按鈕上會改變外觀作為提示(額外繪製)
    bool over_button[4]; //【該按鈕是否與滑鼠位置重疊】
    int X[8], Y[8]; //【按鈕各自XY座標】
    int button_w[8], button_h[8]; //【按鈕各自長寬】
    //暫時使用的金錢條圖片
    ALLEGRO_BITMAP *Money;
    

} GameScene;

Scene *New_GameScene(int label);
void game_scene_update(Scene *self);
void game_scene_draw(Scene *self);
void game_scene_destroy(Scene *self);

void Game_DetectButtonOn(Scene *self);

#endif
