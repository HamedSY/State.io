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

typedef struct Potion {
	double x;
	double y;
	int flag;
} Potion;


int SCREEN_WIDTH , SCREEN_HEIGHT ;
int FPS;
int CENTER_R , SOLDIER_R;
int COLOR_SOLDIERS_MAX_NUM;
int ORDINARY_SOLDIERS_MAX_NUM;
int AI_ATTACKING_FREQUENCY;
double MY_VEL , AI_VEL;
int INCREASE_RATE , AI_INCREASE_RATE;

SDL_Color BLACK;
SDL_Color WHITE;
SDL_Color YELLOW;
SDL_Color ORANGE;
SDL_Color LIGHT_BLUE;
SDL_Color DARK_BLUE;
SDL_Color LIGHT_PURPLE;
SDL_Color DARK_PURPLE;
SDL_Color GREEN;
SDL_Color RED;

int mei , mej , enemyi , enemyj , desti , destj;
int mouseOnMe , isSendingSoldiers , AIisSendingSoldiers;
int isHovernewGame , isHoverContinue , isTyping , isHoverLoadGame , isHoverScoreBoard ,
isHoverMedium , isHoverHard , isHoverGal1 , isHoverGal2 , isHoverGal3 , isHoverCon , 
isHoverReturn , isHoverQuit , isHoverBack;
int diff , gal;
int end , loading , update , scoreboard;
int n , temp , temp2 , frame , potFrame;
double navarx , navarai;
int myflag[200] , AIflag[200] , myflag2[200] , 
AIflag2[200] , hitflag[200] , AIhitflag[200];
int hitcounter , AIhitcounter;
int inputLoc;

char solNumStr[10] , username[30];
int ringedPlanets[9];
int ringlessPlanets[9];
int sortedScores[500];
char sortedNames[500][30];

City cities[4][6];

Potion rocket;
Potion snow;
Potion ufo;
Potion inf;

int rocketVisible , rocketOn;
int snowVisible , snowOn;
int ufoOn , ufoVisible;
int infOn , infVisible;

Coordination begin , dest , begin2 , dest2;
Coordination mouse , soldier[200] , soldier2[200];

SDL_Rect planetsRect[4][6];
SDL_Texture *planetsTexture[18];




void AIsendingSoldiers( SDL_Renderer *rend );

int gameEventHandling( SDL_Renderer *rend );
int initializingCities();
void printMap( SDL_Renderer* rend , int n );
void sendingSoldiers( SDL_Renderer *rend );
void rocketInit();
void snowInit();
void ufoInit();
void infInit();
void solNumIncreasing();
void AIsolNumIncreasing();
int checkTheEnd();
void saveTheGame();
void updateScores();
void drawEndingBoxes( SDL_Renderer *rend );
void coordZeroer( int n , Coordination a[] );
void zeroer( int n , int a[] );

int loginEventHandling( SDL_Renderer *rend );
void usernameInputBox( SDL_Renderer *rend );
void saveUsername();

int menuEventHandling( SDL_Renderer *rend );
void loadTheGame();
void drawMenuBoxes( SDL_Renderer *rend );
void globalsInit();
void drawBox( SDL_Renderer *rend );
int leaderboardEventHandling();
void sortScores();

int mapChoosingEventHandling( SDL_Renderer *rend );
void drawChoosingBoxes( SDL_Renderer *rend );



#endif