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


    case Information_L:
        scene = New_Info(Information_L);
        break;

    case Quit_L:
        scene = New_Leave(Quit_L);

    default:
        break;
    }
}