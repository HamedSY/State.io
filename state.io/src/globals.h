#ifndef __GLOBALS_H__
#define __GLOBALS_H__


typedef struct City {
	int x1;
	int x2;
	int y1;
	int y2;
	int flag;
	int soldiers_num;
	// int isSendingSol;
	int number;
} City;

typedef struct Coordination {
	double x;
	double y;
} Coordination;


int SCREEN_WIDTH , SCREEN_HEIGHT ;
int FPS;
int CENTER_R , SOLDIER_R;
int COLOR_SOLDIERS_MAX_NUM;
int ORDINARY_SOLDIERS_MAX_NUM;
int AI_ATTACKING_FREQUENCY;

SDL_Color BLACK;
SDL_Color WHITE;
SDL_Color YELLOW;
SDL_Color ORANGE;
SDL_Color LIGHT_BLUE;
SDL_Color DARK_BLUE;
SDL_Color LIGHT_PURPLE;
SDL_Color DARK_PURPLE;
SDL_Color GREEN;

int mei , mej , enemyi , enemyj , desti , destj;
int mouseOnMe , isSendingSoldiers , AIisSendingSoldiers;
int isHovernewGame , isHoverContinue , isTyping , isHoverLoadGame , isHoverScoreBoard ,
isHoverMedium , isHoverHard , isHoverGal1 , isHoverGal2 , isHoverGal3 , isHoverCon;
int diff , gal;
int end , loading;
int n , temp , temp2 , frame;
int myflag[200] , AIflag[200] , myflag2[200] , 
AIflag2[200] , hitflag[200] , AIhitflag[200];
int hitcounter , AIhitcounter;
int inputLoc;
double velocity;
char solNumStr[10] , username[30];
int ringedPlanets[9];
//  = { 1 , 3 , 5 , 7 , 8 , 9 , 10 , 15 , 16 };
int ringlessPlanets[9];
//  = { 2 , 4 , 6 , 11 , 12 , 13 , 14 , 17 , 18 };

City cities[4][6];

Coordination begin , dest , begin2 , dest2;
Coordination mouse , soldier[200] , soldier2[200];

SDL_Rect planetsRect[4][6];
SDL_Texture *planetsTexture[18];




void AIsendingSoldiers( SDL_Renderer *rend );

int gameEventHandling( SDL_Renderer *rend );
int initializingCities();
void print2DCity( int a , int b , City arr[a][b] );
void printMap( SDL_Renderer* rend , int n );
void sendingSoldiers( SDL_Renderer *rend );
void solNumIncreasing();
int checkTheEnd();
void saveTheGame();
void coordZeroer( int n , Coordination a[] );
void zeroer( int n , int a[] );

int loginEventHandling( SDL_Renderer *rend );
void usernameInputBox( SDL_Renderer *rend );
void globalsInit();

int menuEventHandling( SDL_Renderer *rend );
void loadTheGame();
void drawMenuBoxes( SDL_Renderer *rend );
void drawBox( SDL_Renderer *rend );

int mapChoosingEventHandling( SDL_Renderer *rend );
void drawChoosingBoxes( SDL_Renderer *rend );



#endif