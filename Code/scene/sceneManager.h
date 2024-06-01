#ifndef SCENEMANAGER_H_INCLUDED
#define SCENEMANAGER_H_INCLUDED
#include "scene.h"
extern Scene *scene;
typedef enum SceneType
{
    //遊戲主選單相關頁面
    Menu_L = 0,
    GameScene_L = 1,
    Set_L = 2,
    Information_L = 3,
    Quit_L = 4,

    //遊戲主畫面相關頁面
    Book_L = 5,

    //商店相關頁面
    Shop_L = 6,
    Buy_L = 7,

    //訂單相關頁面
    Order_L = 8
    
} SceneType;
void create_scene(SceneType);

#endif