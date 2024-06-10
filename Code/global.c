#include "global.h"
#include "shapes/Shape.h"
#include <stdbool.h>
// variables for global usage
const double FPS = 60.0;
const int WIDTH = 1440;
const int HEIGHT = 1080;
int window = 0;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_EVENT event;
ALLEGRO_TIMER *fps = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
bool mouse_state[ALLEGRO_MOUSE_MAX_EXTRA_AXES] = {false};
Point mouse;
bool debug_mode = true;

int CloseGame = 0; //預設為不關閉遊戲

//遊戲設定相關變數
bool ModeCondition[3] = {false}; //紀錄每個模式是On或Off

//貓咪抓捕功能相關變數
bool catchIT = false;

//遊戲視窗內的功能按鍵切換(0:圖鑑|1:商店|2:訂單|3:離開畫面|-1:預設，為遊戲視窗)
int gameFunction = -1;

//圖鑑紀錄相關變數設定
int CatNumber[CatTotalKind] = {0}; //初始的所有種類的貓咪數量=0 -> 可以在這裡調整初值幫持有數debug
bool NewCatOrNot[CatTotalKind] = {true}; //因為初始啥都沒，所以全部都是新的(true->new；false->old)
bool Own[CatTotalKind] = {false}; //一開始都沒有持有過
int TotalOwnCat = 0; //for離開遊戲的結尾彩蛋用
//圖鑑顯示變數設定(1~5:pageOne|6~10:pageTwo......)
int Page = 0;

//商店相關變數設定
int which_food = 0;

//金錢系統與肉泥持有相關
int TotalMoney = 0; //目前持有總金額(初始先設定為0，之後debug)
int OwnMeat[MeatKind] = {0}; //目前擁有的四種肉泥各自的數量//配合which_food，從1開始才是肉泥

//肉泥與貓咪生成
int meatsX[100], meatsY[100], meatType[100], posx[100];
int lenMeat;

int client_set = 1;