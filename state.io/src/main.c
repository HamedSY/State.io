#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "map.c"


// // funcs prototypes
int eventHandling( SDL_Renderer *rend );


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
	

	// // menu loop
	// while( 1 ) {
	// 	SDL_SetRenderDrawColor( myRenderer , 0xff , 0xff , 0xff , 0xff );
	// 	SDL_RenderClear( myRenderer );

	// 	// event handling
	// 	if( !eventHandling( myRenderer ) )
	// 		break;
		


	// 	SDL_RenderPresent( myRenderer );
	// 	SDL_Delay( 1000 / FPS );
	// 	SDL_RenderClear( myRenderer );
	// }



	// game loop
	while( 1 ) {

		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < n; j++) {
				sprintf( solNumStr , "%d" , cities[i][j].soldiers_num );
				solNumSurface[i][j] = TTF_RenderText_Solid( solNumFont , solNumStr , WHITE );
				solNumTexture[i][j] = SDL_CreateTextureFromSurface( myRenderer , solNumSurface[i][j] );
				SDL_QueryTexture( solNumTexture[i][j] , NULL , NULL , &textRect[i][j].w , &textRect[i][j].h );
				SDL_QueryTexture( solNumTexture[i][j] , NULL , NULL , &textRect[i][j].w , &textRect[i][j].h );
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
	SDL_FreeSurface( imgSurface );
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



int eventHandling( SDL_Renderer *rend ) {
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		mouse.x = ev.button.x;
		mouse.y = ev.button.y;

		if( ev.type == SDL_QUIT ) 
			return 0; // Quit

		if( ev.type == SDL_MOUSEBUTTONUP ) {
			for(int i = 0; i < cities[mei][mej].soldiers_num; i++) {
				soldier[i].x = ((cities[mei][mej].x1 + cities[mei][mej].x2) / 2) + ((rand() % 20) - 10);
				soldier[i].y = ((cities[mei][mej].y1 + cities[mei][mej].y2) / 2) + ((rand() % 20) - 10);
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


/*
	bugs: {
		- vaghti tedad sarbaza mire bala, age ye sarbazkhone dar hale ferestadane sarbaz bashe, dar lahze
		sarbaze ezefe shode ham ersal mishe;
		- hamzaman nemishe az chand ta shahr sarbaz eresal kard

	}
*/