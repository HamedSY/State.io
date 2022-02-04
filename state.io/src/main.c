#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "globals.h"
#include "game.c"
#include "menu.c"


int main() {
	srand(time(NULL));
	int frame = 1;

	// inits
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
		printf("error : %s\n" , SDL_GetError());
		return 0;
	}
	if(TTF_Init() == -1) {
		printf("error : %s\n" , TTF_GetError());
		return 0;
	}

	// window , renderer
	SDL_Window *myWindow = SDL_CreateWindow( "State.hm" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 
	SCREEN_WIDTH , SCREEN_HEIGHT , SDL_WINDOW_OPENGL );
	SDL_Renderer *myRenderer = SDL_CreateRenderer( myWindow , -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

	// menu images
	SDL_Surface *menuBackImgSurface = IMG_Load("images/menu_back.jpeg");
	SDL_Texture *menuBackImgTexture = SDL_CreateTextureFromSurface(myRenderer , menuBackImgSurface);

	// menu title
	SDL_Surface *menuTitleImgSurface = IMG_Load("images/menu_title.png");
	SDL_Texture *menuTitleImgTexture = SDL_CreateTextureFromSurface(myRenderer , menuTitleImgSurface);
	SDL_Rect menuTitleImgRect; menuTitleImgRect.x = 150; menuTitleImgRect.y = 50;
	menuTitleImgRect.w = 300; menuTitleImgRect.h = 150;

	

	n = initializingCities();
	
	// background of map image
	SDL_Surface *mapBackImgSurface = IMG_Load("images/back.jpg");
	SDL_Texture *mapBackImgTexture = SDL_CreateTextureFromSurface(myRenderer , mapBackImgSurface);

	// soldiers' numbers text
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
	

	// menu loop
	while( 1 ) {
		SDL_SetRenderDrawColor( myRenderer , 0xff , 0xff , 0xff , 0xff );
		SDL_RenderClear( myRenderer );

		SDL_RenderCopy( myRenderer , menuBackImgTexture , NULL , NULL );
		SDL_RenderCopy( myRenderer , menuTitleImgTexture , NULL , &menuTitleImgRect );

		// event handling
		if( !menuEventHandling( myRenderer ) )
			break;
		


		SDL_RenderPresent( myRenderer );
		SDL_Delay( 1000 / FPS );
		SDL_RenderClear( myRenderer );
	}

	SDL_DestroyTexture( menuBackImgTexture );
	SDL_FreeSurface( menuBackImgSurface );



	// game loop
	while( 1 ) {

		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < n; j++) {
				sprintf( solNumStr , "%d" , cities[i][j].soldiers_num );
				solNumSurface[i][j] = TTF_RenderText_Solid( solNumFont , solNumStr , WHITE );
				solNumTexture[i][j] = SDL_CreateTextureFromSurface( myRenderer , solNumSurface[i][j] );
				SDL_QueryTexture( solNumTexture[i][j] , NULL , NULL , &textRect[i][j].w , &textRect[i][j].h );
			}
		}
		
		SDL_SetRenderDrawColor( myRenderer , 0xff , 0xff , 0xff , 0xff );
		SDL_RenderClear( myRenderer );

		SDL_RenderCopy( myRenderer , mapBackImgTexture , NULL , NULL );
		printMap( myRenderer , n );
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < n; j++) {
				SDL_RenderCopy( myRenderer , solNumTexture[i][j] , NULL , &textRect[i][j] );
			}
		}

		// event handling
		if( !gameEventHandling( myRenderer ) )
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
    SDL_DestroyTexture( mapBackImgTexture );
	SDL_FreeSurface( mapBackImgSurface );
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < n; j++) {
			SDL_DestroyTexture( solNumTexture[i][j] );
			SDL_FreeSurface( solNumSurface[i][j] );
		}
	}
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
	
    return 0;
}






/*
	bugs: {
		- vaghti tedad sarbaza mire bala, age ye sarbazkhone dar hale ferestadane sarbaz bashe, dar lahze
		sarbaze ezefe shode ham ersal mishe;
		- hamzaman nemishe az chand ta shahr sarbaz eresal kard

	}
*/