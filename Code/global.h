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

//圖鑑相關變數設定
#define CatTotalKind 4
extern int CatNumber[CatTotalKind]; //該種類貓咪目前持有幾隻
extern bool NewCatOrNot[CatTotalKind]; //該種類貓咪是否為新的貓(true->new；false->old)
extern bool Own[CatTotalKind]; //是否已經持有過該貓咪

//商店相關變數設定
extern int which_food;

#endif
