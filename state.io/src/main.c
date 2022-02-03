#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>


typedef struct City {
	int x1;
	int x2;
	int y1;
	int y2;
	int theta;
	int flag;
	int soldiers_num;
} City;

typedef struct Coordination {
	double x;
	double y;
} Coordination;

const int SCREEN_WIDTH = 1100 , SCREEN_HEIGHT = 600;
const int FPS = 60;
const int CENTER_R = 15 , SOLDIER_R = 3;
const int SOLDIERS_MAX_NUM = 15;

SDL_Color WHITE = { 0 , 0 , 0 , 255 };

int mei , mej , enemyi , enemyj;
int mouseOnMe = 0 , isSendingSoldiers = 0;
int n;

// char solNumStr[10];

City cities[4][6];
// City myCity;
// City enemyCity;

Coordination begin , dest;
Coordination mouse , soldier[100];
Coordination tmp = {0};

// funcs prototypes
int eventHandling( SDL_Renderer *rend );
int initializingCities();
void print2DCity( int a , int b , City arr[a][b] );
void printMap( SDL_Renderer* rend , int n );
void sendingSoldiers( SDL_Renderer *rend );
void solNumIncreasing();


int main() {

	srand(time(NULL));

	int frame = 1;

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
		printf("error : %s\n" , SDL_GetError());
		return 0;
	}
	if(TTF_Init() == -1) {
		printf("error : %s\n" , TTF_GetError());
		return 0;
	}

	// window , renderer , surface , texture , event
	SDL_Window *myWindow = SDL_CreateWindow( "My State.io" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 
	SCREEN_WIDTH , SCREEN_HEIGHT , SDL_WINDOW_OPENGL );
	SDL_Renderer *myRenderer = SDL_CreateRenderer( myWindow , -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	SDL_Surface *imgSurface = IMG_Load("images/back.jpg");
	SDL_Texture *imgTexture = SDL_CreateTextureFromSurface(myRenderer , imgSurface);
	SDL_Event *myEvent;
	// text
	n = initializingCities();

	TTF_Font *solNumFont = TTF_OpenFont("fonts/LiberationSerif-Regular.ttf" , 15);
	SDL_Surface *solNumSurface[4][6];
	SDL_Texture *solNumTexture[4][6];
	SDL_Rect textRect[4][6];
	
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < n; j++) {
			textRect[i][j].x = ((cities[i][j].x1 + cities[i][j].x2) / 2) - (CENTER_R / 2);
			textRect[i][j].y = ((cities[i][j].y1 + cities[i][j].y2) / 2) - (CENTER_R / 2);
			
		}
	}
	

	// game loop
	while( 1 ) {

		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < n; j++) {
				char solNumStr[10] = {0};
				sprintf( solNumStr , "%d" , cities[i][j].soldiers_num );
				solNumSurface[i][j] = TTF_RenderText_Solid( solNumFont , solNumStr , WHITE );
				solNumTexture[i][j] = SDL_CreateTextureFromSurface( myRenderer , solNumSurface[i][j] );
				SDL_QueryTexture( solNumTexture[i][j] , NULL , NULL , &textRect[i][j].w , &textRect[i][j].h );
				SDL_QueryTexture( solNumTexture[i][j] , NULL , NULL , &textRect[i][j].w , &textRect[i][j].h );
				SDL_FreeSurface( solNumSurface[i][j] );
			}
		}
		
		SDL_SetRenderDrawColor( myRenderer , 0xff , 0xff , 0xff , 0xff );
		SDL_RenderClear( myRenderer );

		SDL_RenderCopy( myRenderer , imgTexture , NULL , NULL );
		printMap( myRenderer , n );
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < n; j++) {
				SDL_RenderCopy( myRenderer , solNumTexture[i][j] , NULL , &textRect[i][j] );
			}
		}

		// event handling
		if( !eventHandling( myRenderer ) )
			break;
		if ( mouseOnMe ) {
			lineColor( myRenderer , (cities[mei][mej].x1 + cities[mei][mej].x2) / 2 , (cities[mei][mej].y1 + cities[mei][mej].y2) / 2
			, mouse.x , mouse.y , 0xff000000 );
		}

		if( isSendingSoldiers ) {
			sendingSoldiers( myRenderer );
		}
		
		SDL_RenderPresent( myRenderer );
		SDL_Delay( 1000 / FPS );
		SDL_RenderClear( myRenderer );

		frame++;
		if(frame % 60 == 0) {
			solNumIncreasing();
			frame = 1;
		} 
		
	}

	
	SDL_DestroyWindow( myWindow );
	SDL_DestroyRenderer( myRenderer );
    SDL_DestroyTexture( imgTexture );
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < n; j++) {
			SDL_DestroyTexture( solNumTexture[i][j] );
		}
	}
	SDL_Quit();
	IMG_Quit();
	
    return 0;
}






int eventHandling( SDL_Renderer *rend ) {
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		mouse.x = ev.button.x;
		mouse.y = ev.button.y;

		if( ev.type == SDL_QUIT ) 
			return 0; // Quit

		if( ev.type == SDL_MOUSEBUTTONUP ) {
			for(int i = 0; i < cities[mei][mej].soldiers_num; i++) {
				soldier[i].x = ((cities[mei][mej].x1 + cities[mei][mej].x2) / 2) + ((rand() % 50) - 25);
				soldier[i].y = ((cities[mei][mej].y1 + cities[mei][mej].y2) / 2) + ((rand() % 50) - 25);
			}

			begin.x = (cities[mei][mej].x1 + cities[mei][mej].x2) / 2;
			begin.y = (cities[mei][mej].y1 + cities[mei][mej].y2) / 2;

			dest = mouse;
			if(mouseOnMe) isSendingSoldiers = 1;
			else isSendingSoldiers = 0;
			mouseOnMe = 0;
		}
		
		if( ev.type == SDL_MOUSEBUTTONDOWN ) {
			if(ev.button.button == SDL_BUTTON_LEFT ) {

				for(int i = 0; i < 4; i++) {
					for(int j = 0; j < n; j++) {
						if(cities[i][j].flag == 1) {
							mei = i; mej = j;
							if( ev.button.x >= cities[mei][mej].x1 && ev.button.x <= cities[mei][mej].x2  &&  
							ev.button.y >= cities[mei][mej].y1 && ev.button.y <= cities[mei][mej].y2 ) {
								mouseOnMe = 1;
								break;
							}
						}
					}
					if( mouseOnMe ) break;
				}
						
			}
		}

	}
	return 1;
}


void sendingSoldiers( SDL_Renderer *rend ) {
	int flag = 0 , i , j;
	if(!flag)
		for(i = 0; i < 4; i++) {
			for(j = 0; j < n; j++) {
				if( dest.x <= cities[i][j].x2 && dest.x >= cities[i][j].x1 &&
				dest.y <= cities[i][j].y2 && dest.y >= cities[i][j].y1 ) {
					dest.x = (cities[i][j].x1 + cities[i][j].x2) / 2;
					dest.y = (cities[i][j].y1 + cities[i][j].y2) / 2;
					// printf("%d %d\n" , i , j);
					flag = 1;
					break;
				}
			}
			if(flag) break;
		}

	if(flag){
		for(int k = 0; k < cities[mei][mej].soldiers_num; k++) {

			filledCircleColor( rend , soldier[k].x , soldier[k].y , SOLDIER_R , 0xffffffff );
			soldier[k].x += 4 * (dest.x - begin.x) / ( sqrt ( ( (dest.x - begin.x) * (dest.x - begin.x) ) + ( (dest.y - begin.y) * (dest.y - begin.y) ) ) );
			soldier[k].y += 4 * (dest.y - begin.y) / ( sqrt ( ( (dest.x - begin.x) * (dest.x - begin.x) ) + ( (dest.y - begin.y) * (dest.y - begin.y) ) ) );
			if( abs(soldier[k].x - dest.x) <= 10 && abs(soldier[k].y - dest.y) <= 10 ) {
				isSendingSoldiers = 0;
				cities[i][j].soldiers_num -= cities[mei][mej].soldiers_num;
				cities[mei][mej].soldiers_num = 0;
				if(cities[i][j].soldiers_num < 0) {
					cities[i][j].soldiers_num = -cities[i][j].soldiers_num;
					cities[i][j].flag = 1;
				}
			}

		}
	}
}

void solNumIncreasing() {
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < n; j++) {
			if(cities[i][j].flag == 0) {
				if(cities[i][j].soldiers_num <= SOLDIERS_MAX_NUM) {
					cities[i][j].soldiers_num++;
				}
			}
			else {
				cities[i][j].soldiers_num++;
			}
		}
	}
}


void print2DCity(int a , int b , City arr[a][b]) {
	for(int i = 0; i < a; i++) {
		for(int j = 0; j < b; j++) {
			printf("cities[%d][%d].x1 : %d\tcities[%d][%d].y1 : %d\tcities[%d][%d].x2 : %d\tcities[%d][%d].y2 : %d\n"
			, i , j , arr[i][j].x1
			, i , j , arr[i][j].y1
			, i , j , arr[i][j].x2
			, i , j , arr[i][j].y2
			);
		}
		printf("\n");
	}
}

int initializingCities() {
	int length[6] = {0} , width[4][6] = {0} , theta , n = 4 + (rand() % 3);
	int color = 0xff000000;
	
	for(int i = 0; i < 4; i++) {
		cities[i][0].x1 = 40 + (rand() % 30);
		if(i != 0) cities[i][0].y1 = (rand() % 20) + 30 + cities[i - 1][0].y2;
		else cities[i][0].y1 = (rand() % 30) + 40;

		for(int j = 0; j < n; j++) {
			theta = (rand() % 20) + 10;
			if(i == 0) length[j] = (rand() % 70) + 200 - (n * 20);
			width[i][j] = (rand() % 50) + 50;
			cities[i][j].x2 = cities[i][j].x1 + length[j];
			cities[i][j].y2 = cities[i][j].y1 + width[i][j];
			cities[i][j].theta = theta;

			cities[i][j + 1].x1 = cities[i][j].x2 + (rand() % 20) + 30;
			if(i != 0) cities[i][j + 1].y1 = cities[i - 1][j + 1].y2 + (rand() % 20) + 30;
			else cities[i][j + 1].y1 = (rand() % 30) + 40;

			cities[i][j].soldiers_num = 0;

		}
	}

	mei = rand() % 4;
	mej = rand() % n;
	do {
		enemyi = rand() % 4;
		enemyj = rand() % n;
	} while( (enemyi == mei && enemyj == mej) );

	cities[mei][mej].flag = 1;
	cities[enemyi][enemyj].flag = 1;
	cities[mei][mej].soldiers_num += 10;
	cities[enemyi][enemyj].soldiers_num += 10;

	// myCity = cities[mei][mej];
	// enemyCity = cities[enemyi][enemyj];

	return n;
}

void printMap( SDL_Renderer* rend , int n ) {
	int theta;
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < n; j++) {
			
			if( cities[i][j].flag == 1 ) {
				roundedBoxRGBA( rend , cities[i][j].x1 , cities[i][j].y1 , cities[i][j].x2 , cities[i][j].y2 , cities[i][j].theta ,
				200 , 10 , 10 , 255 );
				filledCircleRGBA( rend , (cities[i][j].x1 + cities[i][j].x2) / 2 , (cities[i][j].y1 + cities[i][j].y2) / 2 ,
				CENTER_R , 150 , 10 , 10 , 255 );				
			}

			else if( cities[i][j].flag == 2 ) {
				roundedBoxRGBA( rend , cities[i][j].x1 , cities[i][j].y1 , cities[i][j].x2 , cities[i][j].y2 , cities[i][j].theta ,
				10 , 200 , 10 , 255 );
				filledCircleRGBA( rend , (cities[i][j].x1 + cities[i][j].x2) / 2 , (cities[i][j].y1 + cities[i][j].y2) / 2 ,
				CENTER_R , 10 , 150 , 10 , 255 );
			}

			else {
				roundedBoxRGBA( rend , cities[i][j].x1 , cities[i][j].y1 , cities[i][j].x2 , cities[i][j].y2 , cities[i][j].theta ,
				170 , 200 , 180 , 255 );
				filledCircleRGBA( rend , (cities[i][j].x1 + cities[i][j].x2) / 2 , (cities[i][j].y1 + cities[i][j].y2) / 2 ,
				CENTER_R , 150 , 160 , 180 , 255 );
			}
		}
	}
}