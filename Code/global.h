#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#include <stdio.h>
#include <allegro5/allegro.h>
#define GAME_TERMINATE -1
#include "shapes/Point.h"
#define debug(x)                                                            \
    if (x)                                                                  \
    {                                                                       \
        printf("check at line number %d in file %s\n", __LINE__, __FILE__); \
    }
#define MAX_ELEMENT 100
#define min(x, y) ((x) > (y) ? (y) : (x))
#define max(x, y) ((x) < (y) ? (y) : (x))
// note that you can't assign initial value for extern variable!
extern const double FPS;
extern const int WIDTH;
extern const int HEIGHT;
extern int window;
extern bool key_state[ALLEGRO_KEY_MAX];
extern bool mouse_state[ALLEGRO_MOUSE_MAX_EXTRA_AXES];
extern Point mouse;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_EVENT event;
extern ALLEGRO_TIMER *fps;
extern bool debug_mode;

extern int CloseGame;

extern bool ModeCondition[3]; //紀錄每個模式是On或Off

//貓咪抓捕功能相關變數
extern bool catchIT;

//遊戲視窗內的功能按鍵切換(0:圖鑑|1:商店|2:訂單|3:離開畫面|-1:預設，為遊戲視窗)
extern int gameFunction;

//圖鑑相關變數設定
#define CatTotalKind 4
#define BookPage 4
extern int CatNumber[CatTotalKind]; //該種類貓咪目前持有幾隻
extern bool NewCatOrNot[CatTotalKind]; //該種類貓咪是否為新的貓(true->new；false->old)
extern bool Own[CatTotalKind]; //是否已經持有過該貓咪
extern int TotalOwnCat; //for離開遊戲的結尾彩蛋用
extern int Page; //圖鑑頁數控制

//商店相關變數設定(點進去哪個肉泥的購買介面)
extern int which_food;

//金錢系統與肉泥持有相關
#define MeatKind 5 //配合which_food，從1開始才是肉泥
#define MaxMoney 7 //最多7位數
extern int TotalMoney; //當前持有總金額
extern int OwnMeat[MeatKind]; //四種肉泥各自的持有數，從1開始才是肉泥

extern int client_set;

#endif
