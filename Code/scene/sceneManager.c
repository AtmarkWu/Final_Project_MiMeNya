#include "sceneManager.h"
#include "menu.h"
#include "gamescene.h"
#include "Information.h"
#include "leave.h"
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
        scene = New_Scene(Book_L);
        break;
    
    //留給商店頁面(Shop_L = 6)

    //留給訂單頁面(Order_L = 7)

    default:
        break;
    }
}