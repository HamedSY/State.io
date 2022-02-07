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
const int AI_ATTACKING_FREQUENCY = 400;

SDL_Color BLACK = { 0 , 0 , 0 , 255 };
SDL_Color WHITE = { 255 , 255 , 255 , 255 };

int mei , mej , enemyi , enemyj , desti , destj;
int mouseOnMe = 0 , isSendingSoldiers = 0 , AIisSendingSoldiers = 0;
int isHoverStartGame = 0 , isHoverContinue = 0 , isTyping = 0;
int n , temp , temp2 , frame = 1;
int myflag[200] = {0} , AIflag[200] = {0} , myflag2[200] = {0} , 
AIflag2[200] = {0} , hitflag[200] = {0} , AIhitflag[200] = {0};
int inputLoc = 0;
double velocity = 3;
char solNumStr[10] = {0} , username[30] = {};

City cities[4][6];

Coordination begin , dest , begin2 , dest2;
Coordination mouse , soldier[200] , soldier2[200];
Coordination tmp = {0};



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