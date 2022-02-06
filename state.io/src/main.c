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
#include "login.c"
#include "ai.c"


int main() {
	srand(time(NULL));

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
	//fonts
	TTF_Font *LiberationReg15 = TTF_OpenFont("fonts/LiberationSerif-Regular.ttf" , 15);
	TTF_Font *IRNazanin50 = TTF_OpenFont("fonts/IRNazanin.ttf" , 50);


// MENU

	// menu background image
	SDL_Surface *menuBackImgSurface = IMG_Load("images/menu_back.jpeg");
	SDL_Texture *menuBackImgTexture = SDL_CreateTextureFromSurface(myRenderer , menuBackImgSurface);

	// menu title
	SDL_Surface *menuTitleImgSurface = IMG_Load("images/menu_title2.png");
	SDL_Texture *menuTitleImgTexture = SDL_CreateTextureFromSurface(myRenderer , menuTitleImgSurface);
	SDL_Rect menuTitleImgRect; menuTitleImgRect.x = 100; menuTitleImgRect.y = 50;
	menuTitleImgRect.w = 400; menuTitleImgRect.h = 150;

	// menu boxs' texts (image)
	SDL_Surface *startGameSurface = IMG_Load("images/start_game.png");
	SDL_Texture *startGameTexture = SDL_CreateTextureFromSurface( myRenderer , startGameSurface );
	SDL_Rect startGameRect; startGameRect.x = 200; startGameRect.y = 285; startGameRect.w = 200; startGameRect.h = 55;

	SDL_Surface *startGameHoverSurface = IMG_Load("images/start_game_hover.png");
	SDL_Texture *startGameHoverTexture = SDL_CreateTextureFromSurface( myRenderer , startGameHoverSurface );
	

	

	// menu loop
	while( 1 ) {
		SDL_SetRenderDrawColor( myRenderer , 0xff , 0xff , 0xff , 0xff );
		SDL_RenderClear( myRenderer );

		SDL_RenderCopy( myRenderer , menuBackImgTexture , NULL , NULL );
		SDL_RenderCopy( myRenderer , menuTitleImgTexture , NULL , &menuTitleImgRect );
		drawMenuBoxes( myRenderer );
		SDL_RenderCopy( myRenderer , startGameTexture , NULL , &startGameRect );

		// event handling
		int event = menuEventHandling( myRenderer );
		if( event == 0 )
			return 0;
		if( event == 1 )
			break;
		if( isHoverStartGame ) { // hover
			SDL_RenderCopy( myRenderer , startGameHoverTexture , NULL , &startGameRect );
		}
		


		SDL_RenderPresent( myRenderer );
		SDL_Delay( 1000 / FPS );
		SDL_RenderClear( myRenderer );
	}

	// destroyings
	SDL_DestroyTexture( menuTitleImgTexture );
	SDL_DestroyTexture( startGameTexture );
	SDL_DestroyTexture( startGameHoverTexture );
	SDL_FreeSurface( menuTitleImgSurface );
	SDL_FreeSurface( startGameSurface );
	SDL_FreeSurface( startGameHoverSurface );


//LOGIN

	// enter your username please...
	SDL_Surface *enterUsernameSurface = IMG_Load("images/enter.png");
	SDL_Texture *enterUsernameTexture = SDL_CreateTextureFromSurface( myRenderer , enterUsernameSurface );
	SDL_Rect enterUsernameRect; enterUsernameRect.x = 50; enterUsernameRect.y = 150;
	enterUsernameRect.w = 500; enterUsernameRect.h = 75;

	// continue
	SDL_Surface *continueSurface = IMG_Load("images/continue.png");
	SDL_Texture *continueTexture = SDL_CreateTextureFromSurface( myRenderer , continueSurface );
	SDL_Rect continueRect; continueRect.x = 230; continueRect.y = 440;
	continueRect.w = 140; continueRect.h = 50;
	SDL_Surface *continueHoverSurface = IMG_Load("images/continue_hover.png");
	SDL_Texture *continueHoverTexture = SDL_CreateTextureFromSurface( myRenderer , continueHoverSurface );

	// text input
	SDL_StartTextInput();
	SDL_Surface *textInputSurface;
	SDL_Texture *textInputTexture;
	SDL_Rect textInputRect; textInputRect.x = 70; textInputRect.y = 300;



	// login loop
	while( 1 ) {
		SDL_SetRenderDrawColor( myRenderer , 0xff , 0xff , 0xff , 0xff );
		SDL_RenderClear( myRenderer );
		
		SDL_RenderCopy( myRenderer , menuBackImgTexture , NULL , NULL );
		SDL_RenderCopy( myRenderer , enterUsernameTexture , NULL , &enterUsernameRect );
		usernameInputBox( myRenderer );
		SDL_RenderCopy( myRenderer , continueTexture , NULL , &continueRect );


		// event handling
		int event = loginEventHandling( myRenderer );
		if( event == 0 )
			return 0;
		if( event == 1 )
			break;
		if( isHoverContinue )
			SDL_RenderCopy( myRenderer , continueHoverTexture , NULL , &continueRect );

		if( isTyping ) {
			textInputSurface = TTF_RenderText_Solid( IRNazanin50 , username , BLACK );
			textInputTexture = SDL_CreateTextureFromSurface( myRenderer , textInputSurface );
			textInputRect.x = 70; textInputRect.y = 300;
			SDL_QueryTexture( textInputTexture , NULL , NULL , &textInputRect.w , &textInputRect.h );
			SDL_RenderCopy( myRenderer , textInputTexture , NULL , &textInputRect );
		}



		SDL_RenderPresent( myRenderer );
		SDL_Delay( 1000 / FPS );
		SDL_RenderClear( myRenderer );
	}

	SDL_StopTextInput();
	SDL_DestroyTexture( textInputTexture );
	SDL_DestroyTexture( continueHoverTexture );
	SDL_DestroyTexture( continueTexture );
	SDL_DestroyTexture( enterUsernameTexture );
	SDL_FreeSurface( textInputSurface );
	SDL_FreeSurface( continueHoverSurface );
	SDL_FreeSurface( continueSurface );
	SDL_FreeSurface( enterUsernameSurface );


// GAME

	n = initializingCities();

	// background of map image
	SDL_Surface *mapBackImgSurface = IMG_Load("images/back.jpg");
	SDL_Texture *mapBackImgTexture = SDL_CreateTextureFromSurface(myRenderer , mapBackImgSurface);

	// soldiers' numbers text
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
				sprintf( solNumStr , "%d" , cities[i][j].soldiers_num );
				solNumSurface[i][j] = TTF_RenderText_Solid( LiberationReg15 , solNumStr , WHITE );
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

		// AI handling
		if( AIisSendingSoldiers ) {
			AIsendingSoldiers( myRenderer );
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

		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < n; j++) {
				SDL_DestroyTexture( solNumTexture[i][j] );
				SDL_FreeSurface( solNumSurface[i][j] );
			}
		}

		frame++;
		if( frame % 60 == 0 ) 
			solNumIncreasing();
		if( frame % 1500 == 0 )
			AIisSendingSoldiers = 1;

		if(frame % 10000 == 0) 
			frame = 1;
		
	}

	
	SDL_DestroyWindow( myWindow );
	SDL_DestroyRenderer( myRenderer );

    SDL_DestroyTexture( mapBackImgTexture );
	SDL_FreeSurface( mapBackImgSurface );
	
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