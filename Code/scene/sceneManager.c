#include "sceneManager.h"
//主選單相關的頁面的.h檔incoude
#include "menu.h"
#include "gamescene.h"
#include "Information.h"
#include "leave.h"
//遊戲內頁面(圖鑑)的.h檔include
#include "book.h"
//商店頁面的.h檔include
#include "shop.h"
#include "Buy.h"

Scene *scene = NULL;
void create_scene(SceneType type)
{
    switch (type)
    {
    case Menu_L:
        scene = New_Menu(Menu_L);
        break;

    case GameScene_L:
        scene = New_GameScene(GameScene_L);
        break;

    //留給設定頁面(Set_L = 2)

    case Information_L:
        scene = New_Info(Information_L);
        break;

    case Quit_L:
        scene = New_Leave(Quit_L);
        break;

    case Book_L:
        scene = New_Book(Book_L);
        break;

    case Shop_L:
        scene = New_Shop(Shop_L);
        break;
    
    case Buy_L:
        scene = New_Buy(Buy_L);
        break;

    //留給訂單頁面(Order_L = 7)

    default:
        break;
    }
}