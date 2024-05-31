#include "global.h"
#include "shapes/Shape.h"
#include <stdbool.h>
// variables for global usage
const double FPS = 60.0;
const int WIDTH = 900;
const int HEIGHT = 672;
int window = 0;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_EVENT event;
ALLEGRO_TIMER *fps = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
bool mouse_state[ALLEGRO_MOUSE_MAX_EXTRA_AXES] = {false};
Point mouse;
bool debug_mode = true;

int CloseGame = 0; //預設為不關閉遊戲

//圖鑑相關變數設定
int CatNumber[CatTotalKind] = {0}; //初始的所有種類的貓咪數量=0 -> 可以在這裡調整初值幫持有數debug
bool NewCatOrNot[CatTotalKind] = {true};
//因為初始啥都沒，所以全部都是新的(true->new；false->old)
bool Own[CatTotalKind] = {false}; //一開始都沒有持有過