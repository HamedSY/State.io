#ifndef __GLOBALS_H__
#define __GLOBALS_H__


typedef struct City {
	int x1;
	int x2;
	int y1;
	int y2;
	int theta;
	int flag;
	int soldiers_num;
	int isSendingSol;
	int number;
} City;

typedef struct Coordination {
	double x;
	double y;
} Coordination;


const int SCREEN_WIDTH = 1000 , SCREEN_HEIGHT = 600;
const int FPS = 60;
const int CENTER_R = 15 , SOLDIER_R = 3;
const int COLOR_SOLDIERS_MAX_NUM = 60;
const int ORDINARY_SOLDIERS_MAX_NUM = 10;
const int AI_ATTACKING_FREQUENCY = 100;

SDL_Color BLACK = { 0 , 0 , 0 , 255 };
SDL_Color WHITE = { 255 , 255 , 255 , 255 };
SDL_Color YELLOW = { 255 , 231 , 47 , 255 };
SDL_Color ORANGE = { 255 , 178 , 0 , 255 };
SDL_Color LIGHT_BLUE = { 0 , 103 , 217 , 255 };
SDL_Color DARK_BLUE = { 0 , 24 , 168 , 255 };
SDL_Color LIGHT_PURPLE = { 149 , 50 , 170 , 255 };
SDL_Color DARK_PURPLE = { 81 , 40 , 136 , 255 };
SDL_Color GREEN = { 30 , 140 , 50 , 255 };

int mei , mej , enemyi , enemyj , desti , destj;
int mouseOnMe = 0 , isSendingSoldiers = 0 , AIisSendingSoldiers = 0;
int isHovernewGame = 0 , isHoverContinue = 0 , isTyping = 0 , isHoverLoadGame = 0 , isHoverScoreBoard = 0 ,
isHoverMedium = 0 , isHoverHard = 0 , isHoverGal1 = 0 , isHoverGal2 = 0 , isHoverGal3 = 0 , isHoverCon = 0;
int diff = 0 , gal = 0;
int end = 0;
int n , temp , temp2 , frame = 1;
int myflag[200] = {0} , AIflag[200] = {0} , myflag2[200] = {0} , 
AIflag2[200] = {0} , hitflag[200] = {0} , AIhitflag[200] = {0};
int hitcounter = 0 , AIhitcounter = 0;
int inputLoc = 0;
double velocity = 3;
char solNumStr[10] = {0} , username[30] = {};
int transCh = 200;
int ringedPlanets[9] = { 1 , 3 , 5 , 7 , 8 , 9 , 10 , 15 , 16 };
int ringlessPlanets[9] = { 2 , 4 , 6 , 11 , 12 , 13 , 14 , 17 , 18 };

City cities[4][6];

Coordination begin , dest , begin2 , dest2;
Coordination mouse , soldier[200] , soldier2[200];
Coordination tmp = {0};

SDL_Rect planetsRect[4][6];
SDL_Texture *planetsTexture[18];


void zeroer( int n , int a[] ) {
	for(int i = 0; i < n; i++)
		a[i] = 0;
}

void coordZeroer( int n , Coordination a[] ) {
	for(int i = 0; i < n; i++) {
		a[i].x = 0;
		a[i].y = 0;
	}
}



#endif