#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>


typedef struct City {
	int x1;
	int x2;
	int y1;
	int y2;
	int theta;
	int flag;
} City;

const int SCREEN_WIDTH = 1100;
const int SCREEN_HEIGHT = 600;
const int FPS = 60;
int mei , mej , enemyi , enemyj;
City cities[4][6];
City myCity;
City enemyCity;

// funcs prototypes
int checkExit();
int initializingCities();
void print2DCity( int a , int b , City arr[a][b] );
void printMap( SDL_Renderer* rend , int n );


int main() {

	srand(time(NULL));

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
		printf("error : %s\n" , SDL_GetError());
		return 0;
	}

	//printf("Hello World!\n\n");

	SDL_Window *myWindow = SDL_CreateWindow( "My Window" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 
	SCREEN_WIDTH , SCREEN_HEIGHT , SDL_WINDOW_OPENGL );

	SDL_Renderer *myRenderer = SDL_CreateRenderer( myWindow , -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

	SDL_Surface* mySurface = IMG_Load("images/back.jpg");
	SDL_Texture* myTexture = SDL_CreateTextureFromSurface(myRenderer , mySurface);

	// SDL_Rect a;
	// a.x / a.y / a.h / a.w
	
	int n = initializingCities();	

	while( !checkExit() ) {
		
		SDL_SetRenderDrawColor( myRenderer , 0xff , 0xff , 0xff , 0xff );
		SDL_RenderClear( myRenderer ); //clear the window and blacken it

		SDL_RenderCopy( myRenderer , myTexture , NULL , NULL );

		printMap( myRenderer , n );
		
		SDL_RenderPresent( myRenderer );
		SDL_Delay( 1000 / FPS );
		SDL_RenderClear( myRenderer );
		
	}

	
	SDL_DestroyWindow( myWindow );
	SDL_DestroyRenderer( myRenderer );
    SDL_DestroyTexture( myTexture );
	SDL_Quit();
	
    return 0;
}






int checkExit() {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
			case SDL_QUIT:
				return 1;
				break;
		}
	}
	return 0;
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

		}
	}

	mei = rand() % 4;
	mej = rand() % n;
	do {
		enemyi = rand() % 4;
		enemyj = rand() % n;
	} while( (enemyi == mei && enemyj == mej) );

	myCity = cities[mei][mej];
	enemyCity = cities[enemyi][enemyj];

	return n;
}

void printMap( SDL_Renderer* rend , int n ) {
	int theta;
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < n; j++) {
			
			if( i == mei && j == mej ) {
				roundedBoxRGBA( rend , cities[i][j].x1 , cities[i][j].y1 , cities[i][j].x2 , cities[i][j].y2 , cities[i][j].theta ,
				200 , 10 , 10 , 255 );
				filledCircleRGBA( rend , (cities[i][j].x1 + cities[i][j].x2) / 2 , (cities[i][j].y1 + cities[i][j].y2) / 2 ,
				10 , 150 , 10 , 10 , 255 );				
			}

			else if( i == enemyi && j == enemyj ) {
				roundedBoxRGBA( rend , cities[i][j].x1 , cities[i][j].y1 , cities[i][j].x2 , cities[i][j].y2 , cities[i][j].theta ,
				10 , 200 , 10 , 255 );
				filledCircleRGBA( rend , (cities[i][j].x1 + cities[i][j].x2) / 2 , (cities[i][j].y1 + cities[i][j].y2) / 2 ,
				10 , 10 , 150 , 10 , 255 );
			}

			else {
				roundedBoxRGBA( rend , cities[i][j].x1 , cities[i][j].y1 , cities[i][j].x2 , cities[i][j].y2 , cities[i][j].theta ,
				170 , 200 , 180 , 255 );
				filledCircleRGBA( rend , (cities[i][j].x1 + cities[i][j].x2) / 2 , (cities[i][j].y1 + cities[i][j].y2) / 2 ,
				10 , 150 , 160 , 180 , 255 );
			}
		}
	}
}