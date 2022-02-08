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
	TTF_Font *funtasia15 = TTF_OpenFont("fonts/Funtasia.otf" , 15);
	TTF_Font *funtasia50 = TTF_OpenFont("fonts/Funtasia.otf" , 50);
	TTF_Font *funtasia70 = TTF_OpenFont("fonts/Funtasia.otf" , 70);
	TTF_Font *funtasia40 = TTF_OpenFont("fonts/Funtasia.otf" , 40);

	// menu background image
	SDL_Surface *menuBackImgSurface = IMG_Load("images/back2.jpg");
	SDL_Texture *menuBackImgTexture = SDL_CreateTextureFromSurface(myRenderer , menuBackImgSurface);

	
	


//LOGIN

	// enter your username please...
	SDL_Surface *enterUsernameSurface = TTF_RenderText_Blended( funtasia70 , "Enter Your Username Please" , ORANGE );
	SDL_Texture *enterUsernameTexture = SDL_CreateTextureFromSurface( myRenderer , enterUsernameSurface );
	SDL_Rect enterUsernameRect; enterUsernameRect.x = 145; enterUsernameRect.y = 140;
	SDL_QueryTexture( enterUsernameTexture , NULL , NULL , &enterUsernameRect.w , &enterUsernameRect.h );

	// continue
	SDL_Surface *continueSurface = TTF_RenderText_Blended( funtasia40 , "Continue" , WHITE );
	SDL_Texture *continueTexture = SDL_CreateTextureFromSurface( myRenderer , continueSurface );
	SDL_Rect continueRect; continueRect.x = 430; continueRect.y = 460;
	SDL_QueryTexture( continueTexture , NULL , NULL , &continueRect.w , &continueRect.h );

	// text input
	SDL_StartTextInput();
	SDL_Surface *textInputSurface;
	SDL_Texture *textInputTexture;
	SDL_Rect textInputRect; textInputRect.x = (SCREEN_WIDTH / 2); textInputRect.y = 300;



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
			roundedBoxRGBA( myRenderer , 400 , 450 , 600 , 520 , 10 , 255 , 255 , 255 , 60 );

		if( isTyping ) {
			textInputSurface = TTF_RenderText_Solid( funtasia50 , username , DARK_BLUE );
			textInputTexture = SDL_CreateTextureFromSurface( myRenderer , textInputSurface );
			textInputRect.x = (SCREEN_WIDTH / 2) - inputLoc; textInputRect.y = 300;
			SDL_QueryTexture( textInputTexture , NULL , NULL , &textInputRect.w , &textInputRect.h );
			SDL_RenderCopy( myRenderer , textInputTexture , NULL , &textInputRect );
		}



		SDL_RenderPresent( myRenderer );
		SDL_Delay( 1000 / FPS );
		SDL_RenderClear( myRenderer );
	}

	SDL_StopTextInput();
	SDL_DestroyTexture( textInputTexture );
	SDL_DestroyTexture( continueTexture );
	SDL_DestroyTexture( enterUsernameTexture );
	SDL_FreeSurface( textInputSurface );
	SDL_FreeSurface( continueSurface );
	SDL_FreeSurface( enterUsernameSurface );
	

// MENU

	// menu title
	SDL_Surface *menuTitleImgSurface = IMG_Load("images/menu_title.png");
	SDL_Texture *menuTitleImgTexture = SDL_CreateTextureFromSurface(myRenderer , menuTitleImgSurface);
	SDL_Rect menuTitleImgRect; menuTitleImgRect.x = 260; menuTitleImgRect.y = 20;
	SDL_QueryTexture( menuTitleImgTexture , NULL , NULL , &menuTitleImgRect.w , &menuTitleImgRect.h );

	// menu boxs' texts (image)
	SDL_Surface *newGameSurface = TTF_RenderText_Blended( funtasia50 , "New Game" , WHITE );
	SDL_Texture *newGameTexture = SDL_CreateTextureFromSurface( myRenderer , newGameSurface );
	SDL_Rect newGameRect; newGameRect.x = 410; newGameRect.y = 260;
	SDL_QueryTexture( newGameTexture , NULL , NULL , &newGameRect.w , &newGameRect.h );

	SDL_Surface *loadGameSurface = TTF_RenderText_Blended( funtasia50 , "Load Game" , WHITE );
	SDL_Texture *loadGameTexture = SDL_CreateTextureFromSurface( myRenderer , loadGameSurface );
	SDL_Rect loadGameRect; loadGameRect.x = 405; loadGameRect.y = 375;
	SDL_QueryTexture( loadGameTexture , NULL , NULL , &loadGameRect.w , &loadGameRect.h );

	SDL_Surface *scoreBoardSurface = TTF_RenderText_Blended( funtasia50 , "Scoreboard" , WHITE );
	SDL_Texture *scoreBoardTexture = SDL_CreateTextureFromSurface( myRenderer , scoreBoardSurface );
	SDL_Rect scoreBoardRect; scoreBoardRect.x = 390; scoreBoardRect.y = 490;
	SDL_QueryTexture( scoreBoardTexture , NULL , NULL , &scoreBoardRect.w , &scoreBoardRect.h );


	// menu loop
	while( 1 ) {
		SDL_SetRenderDrawColor( myRenderer , 0xff , 0xff , 0xff , 0xff );
		SDL_RenderClear( myRenderer );

		SDL_RenderCopy( myRenderer , menuBackImgTexture , NULL , NULL );
		SDL_RenderCopy( myRenderer , menuTitleImgTexture , NULL , &menuTitleImgRect );
		drawMenuBoxes( myRenderer );
		SDL_RenderCopy( myRenderer , newGameTexture , NULL , &newGameRect );
		SDL_RenderCopy( myRenderer , loadGameTexture , NULL , &loadGameRect );
		SDL_RenderCopy( myRenderer , scoreBoardTexture , NULL , &scoreBoardRect );

		// event handling
		int event = menuEventHandling( myRenderer );
		if( event == 0 )
			return 0;
		if( event == 1 )
			break;
		if( isHovernewGame )  
			roundedBoxRGBA( myRenderer , 350 , 250 , 650 , 330 , 10 , 255 , 255 , 255 , 60 );

		if( isHoverLoadGame )
			roundedBoxRGBA( myRenderer , 350 , 365 , 650 , 445 , 10 , 255 , 255 , 255 , 60 );

		if( isHoverScoreBoard )
			roundedBoxRGBA( myRenderer , 350 , 480 , 650 , 560 , 10 , 255 , 255 , 255 , 60 );
		
		

		SDL_RenderPresent( myRenderer );
		SDL_Delay( 1000 / FPS );
		SDL_RenderClear( myRenderer );
	}

	// destroyings
	SDL_DestroyTexture( menuTitleImgTexture );
	SDL_DestroyTexture( newGameTexture );
	SDL_DestroyTexture( loadGameTexture );
	SDL_DestroyTexture( scoreBoardTexture );
	SDL_FreeSurface( menuTitleImgSurface );
	SDL_FreeSurface( newGameSurface );
	SDL_FreeSurface( loadGameSurface );
	SDL_FreeSurface( scoreBoardSurface );


// MAP CHOOSING



// GAME

	n = initializingCities();

	// background of map image
	SDL_Texture *mapBackImgTexture = IMG_LoadTexture( myRenderer , "images/back.jpg");

	// soldiers' numbers text
	SDL_Surface *solNumSurface[4][6];
	SDL_Texture *solNumTexture[4][6];
	SDL_Rect textRect[4][6];
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < n; j++) {
			textRect[i][j].x = ((cities[i][j].x1 + cities[i][j].x2) / 2) - (CENTER_R / 2);
			textRect[i][j].y = ((cities[i][j].y1 + cities[i][j].y2) / 2) - (CENTER_R / 2);
		}
	}



	// game loop
	while( 1 ) {

		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < n; j++) {
				sprintf( solNumStr , "%d" , cities[i][j].soldiers_num );
				solNumSurface[i][j] = TTF_RenderText_Blended( funtasia15 , solNumStr , BLACK );
				solNumTexture[i][j] = SDL_CreateTextureFromSurface( myRenderer , solNumSurface[i][j] );
				SDL_QueryTexture( solNumTexture[i][j] , NULL , NULL , &textRect[i][j].w , &textRect[i][j].h );
			}
		}
		
		SDL_SetRenderDrawColor( myRenderer , 0xff , 0xff , 0xff , 0xff );
		SDL_RenderClear( myRenderer );

		SDL_RenderCopy( myRenderer , mapBackImgTexture , NULL , NULL );
		printMap( myRenderer , n );
		for(int i = 0; i < 3; i++) {
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

		if( frame % 60 == 0 ) {
			if( !end ) {
				solNumIncreasing();
				if(checkTheEnd() == 1) {
					end = 1;
				}
			}
				
			// printf("issending is : %d\t AIissending: %d\n" , isSendingSoldiers , AIisSendingSoldiers);
		}

		if(end) {
			boxColor( myRenderer , 0 , 0 , SCREEN_WIDTH , SCREEN_HEIGHT , 0xaa000000 );
			// SDL_Delay( 2000 );
		}
		
		SDL_RenderPresent( myRenderer );
		SDL_Delay( 1000 / FPS );
		SDL_RenderClear( myRenderer );

		int counter = 0;
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < n; j++) {
				SDL_DestroyTexture( solNumTexture[i][j] );
				SDL_DestroyTexture( planetsTexture[counter] );
				SDL_FreeSurface( solNumSurface[i][j] );
				counter++;
			}
		}

		frame++;

		if(frame % 10000 == 0) 
			frame = 1;
		
	}

	
	SDL_DestroyWindow( myWindow );
	SDL_DestroyRenderer( myRenderer );

    SDL_DestroyTexture( mapBackImgTexture );
	// SDL_FreeSurface( mapBackImgSurface );
	
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
	
    return 0;
}






/*

	bakhsh haye baghi mande {

		- zakhire sazi ha:
			- usernames
			- scoreboards
			- zakhire sazi khode bazi

		//- handle kardan chand enemy

		- map haye amaade

		- moshakhas shodan baakht o bord ha baad az etmam bazi

		- ma'joons
	}


	bakhsh haye naghes ya bug dar {
		
		//- hamle hamzaman

		- hamle tan be tan ya inke har do be ye ja hamle konim

		- taghviat AI
	}

*/