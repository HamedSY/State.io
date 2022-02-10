#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

// include my .h file
#include "globals.h"


int main() {
	globalsInit();

	srand(time(NULL));

	// inits
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0) {
		printf("error : %s\n" , SDL_GetError());
		return 0;
	}
	if(TTF_Init() == -1) {
		printf("error : %s\n" , TTF_GetError());
		return 0;
	}
	if( Mix_OpenAudio( 44100 , MIX_DEFAULT_FORMAT , 2 , 2048 ) < 0 ) {
		printf("error : %s\n" , Mix_GetError());
		return 0;
	}

	// window , renderer 
	SDL_Window *myWindow = SDL_CreateWindow( "Planet.hm" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 
	SCREEN_WIDTH , SCREEN_HEIGHT , SDL_WINDOW_OPENGL );
	SDL_Renderer *myRenderer = SDL_CreateRenderer( myWindow , -1 , SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	//fonts
	TTF_Font *funtasia20 = TTF_OpenFont("fonts/Funtasia.otf" , 20);
	TTF_Font *funtasia30 = TTF_OpenFont("fonts/Funtasia.otf" , 30);
	TTF_Font *funtasia40 = TTF_OpenFont("fonts/Funtasia.otf" , 40);
	TTF_Font *funtasia50 = TTF_OpenFont("fonts/Funtasia.otf" , 50);
	TTF_Font *funtasia70 = TTF_OpenFont("fonts/Funtasia.otf" , 70);
	TTF_Font *funtasia100 = TTF_OpenFont("fonts/Funtasia.otf" , 100);
	// musics
	Mix_Music *menuMusic = Mix_LoadMUS("musics/Dramatic-Adventure.mp3");
	// menu background image
	SDL_Texture *menuBackImgTexture = IMG_LoadTexture( myRenderer , "images/back2.jpg" );



//LOGIN
	// enter your username please...
	LOGIN: {username[0] = '\0';}
	if(!Mix_PlayingMusic()) Mix_PlayMusic( menuMusic , -1 );

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
		int event1 = loginEventHandling( myRenderer );
		if( event1 == 0 )
			return 0;
		else if( event1 == 1 )
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

	// destroyings
	SDL_StopTextInput();
	SDL_DestroyTexture( textInputTexture );
	SDL_DestroyTexture( enterUsernameTexture );
	SDL_DestroyTexture( continueTexture );
	SDL_FreeSurface( textInputSurface );
	SDL_FreeSurface( enterUsernameSurface );
	SDL_FreeSurface( continueSurface );

	// saving usernames
	saveUsername();
	

// MENU
	// menu title
	MENU: {globalsInit(); if(!Mix_PlayingMusic()) Mix_PlayMusic( menuMusic , -1 );}
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

	SDL_Surface *scoreBoardSurface = TTF_RenderText_Blended( funtasia50 , "Leaderboard" , WHITE );
	SDL_Texture *scoreBoardTexture = SDL_CreateTextureFromSurface( myRenderer , scoreBoardSurface );
	SDL_Rect scoreBoardRect; scoreBoardRect.x = 380; scoreBoardRect.y = 490;
	SDL_QueryTexture( scoreBoardTexture , NULL , NULL , &scoreBoardRect.w , &scoreBoardRect.h );

	// back
	SDL_Surface *backSurface = IMG_Load("images/back.png");
	SDL_Texture *backTexture = SDL_CreateTextureFromSurface(myRenderer , backSurface);
	SDL_Rect backRect; backRect.x = 25; backRect.y = 530; backRect.w = 40; backRect.h = 40;

	// sorting scores
	sortScores();


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
		filledCircleRGBA( myRenderer , 50 , 550 , 30 , ORANGE.r , ORANGE.g , ORANGE.b , 255 );
		SDL_RenderCopy( myRenderer , backTexture , NULL , &backRect );

		// event handling
		int event2 = menuEventHandling( myRenderer );
		if( event2 == 0 )
			return 0;
		else if( event2 == 1 )
			break;
		
		else if( event2 == 2 ) {
			FILE *file;
			char filename[50] = {0};
			strcat( filename , "savings/" );
			strcat( filename , username );
			strcat( filename , ".txt" );
			if( file = fopen(filename , "r") ) {
				fclose(file);
				loading = 1;
				loadTheGame();
				break;
			}
		}
		else if( event2 == 3 ){
			scoreboard = 1;
			break;
		}
		else if( event2 == 4 )
			goto LOGIN;
		
		if( isHovernewGame )  
			roundedBoxRGBA( myRenderer , 350 , 250 , 650 , 330 , 10 , 255 , 255 , 255 , 40 );

		else if( isHoverLoadGame )
			roundedBoxRGBA( myRenderer , 350 , 365 , 650 , 445 , 10 , 255 , 255 , 255 , 40 );

		else if( isHoverScoreBoard )
			roundedBoxRGBA( myRenderer , 350 , 480 , 650 , 560 , 10 , 255 , 255 , 255 , 40 );
		
		else if( isHoverBack )
			filledCircleRGBA( myRenderer , 50 , 550 , 30 , WHITE.r , WHITE.g , WHITE.b , 40 );
		

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


if( !loading && !scoreboard ) {

// MAP CHOOSING
	
	SDL_Surface *chooseDiffSurface = TTF_RenderText_Blended( funtasia50 , "Choose A Difficulty Please" , ORANGE );
	SDL_Texture *chooseDiffTexture = SDL_CreateTextureFromSurface ( myRenderer , chooseDiffSurface );
	SDL_Rect chooseDiffRect; chooseDiffRect.x = 260; chooseDiffRect.y = 20;
	SDL_QueryTexture( chooseDiffTexture , NULL , NULL , &chooseDiffRect.w , &chooseDiffRect.h );

	SDL_Surface *chooseMapSurface = TTF_RenderText_Blended( funtasia50 , "Choose A Galaxy Please" , ORANGE );
	SDL_Texture *chooseMapTexture = SDL_CreateTextureFromSurface ( myRenderer , chooseMapSurface );
	SDL_Rect chooseMapRect; chooseMapRect.x = 290; chooseMapRect.y = 190;
	SDL_QueryTexture( chooseMapTexture , NULL , NULL , &chooseMapRect.w , &chooseMapRect.h );

	SDL_Surface *mediumSurface = TTF_RenderText_Blended( funtasia30 , "Medium" , WHITE );
	SDL_Texture *mediumTexture = SDL_CreateTextureFromSurface ( myRenderer , mediumSurface );
	SDL_Rect mediumRect; mediumRect.x = 280; mediumRect.y = 110;
	SDL_QueryTexture( mediumTexture , NULL , NULL , &mediumRect.w , &mediumRect.h );

	SDL_Surface *mediumExSurface = TTF_RenderText_Blended( funtasia20 , "The Galaxy Has 12 Planets" , WHITE );
	SDL_Texture *mediumExTexture = SDL_CreateTextureFromSurface ( myRenderer , mediumExSurface );
	SDL_Rect mediumExRect; mediumExRect.x = 235; mediumExRect.y = 145;
	SDL_QueryTexture( mediumExTexture , NULL , NULL , &mediumExRect.w , &mediumExRect.h );

	SDL_Surface *hardSurface = TTF_RenderText_Blended( funtasia30 , "Hard" , WHITE );
	SDL_Texture *hardTexture = SDL_CreateTextureFromSurface ( myRenderer , hardSurface );
	SDL_Rect hardRect; hardRect.x = 650; hardRect.y = 110;
	SDL_QueryTexture( hardTexture , NULL , NULL , &hardRect.w , &hardRect.h );

	SDL_Surface *hardExSurface = TTF_RenderText_Blended( funtasia20 , "The Galaxy Has 15 Planets" , WHITE );
	SDL_Texture *hardExTexture = SDL_CreateTextureFromSurface ( myRenderer , hardExSurface );
	SDL_Rect hardExRect; hardExRect.x = 590; hardExRect.y = 145;
	SDL_QueryTexture( hardExTexture , NULL , NULL , &hardExRect.w , &hardExRect.h );

	SDL_Surface *ringedGalSurface = TTF_RenderText_Blended( funtasia30 , "Ringed Galaxy" , WHITE );
	SDL_Texture *ringedGalTexture = SDL_CreateTextureFromSurface ( myRenderer , ringedGalSurface );
	SDL_Rect ringedGalRect; ringedGalRect.x = 430; ringedGalRect.y = 455;
	SDL_QueryTexture( ringedGalTexture , NULL , NULL , &ringedGalRect.w , &ringedGalRect.h );

	SDL_Surface *ringlessGalSurface = TTF_RenderText_Blended( funtasia30 , "Ringless Galaxy" , WHITE );
	SDL_Texture *ringlessGalTexture = SDL_CreateTextureFromSurface ( myRenderer , ringlessGalSurface );
	SDL_Rect ringlessGalRect; ringlessGalRect.x = 100; ringlessGalRect.y = 455;
	SDL_QueryTexture( ringlessGalTexture , NULL , NULL , &ringlessGalRect.w , &ringlessGalRect.h );

	SDL_Surface *randomSurface = TTF_RenderText_Blended( funtasia30 , "Random" , WHITE );
	SDL_Texture *randomTexture = SDL_CreateTextureFromSurface ( myRenderer , randomSurface );
	SDL_Rect random2Rect; random2Rect.x = 780; random2Rect.y = 455;
	SDL_QueryTexture( randomTexture , NULL , NULL , &random2Rect.w , &random2Rect.h );


	SDL_Texture *ringGal = IMG_LoadTexture( myRenderer , "images/ring.png" );
	SDL_Texture *ringlessGal = IMG_LoadTexture( myRenderer , "images/ringless.jpg" );
	SDL_Texture *random = IMG_LoadTexture( myRenderer , "images/random.png" );
	SDL_Rect ringlessRect; ringlessRect.x = 50; ringlessRect.y = 280; ringlessRect.w = 260; ringlessRect.h = 170;
	SDL_Rect ringRect; ringRect.x = 370; ringRect.y = 280; ringRect.w = 260; ringRect.h = 170;
	SDL_Rect randomRect; randomRect.x = 710; randomRect.y = 280; randomRect.w = 230; randomRect.h = 160;

	SDL_Surface *continueSurface = TTF_RenderText_Blended( funtasia30 , "Continue" , WHITE );
	SDL_Texture *continueTexture = SDL_CreateTextureFromSurface( myRenderer , continueSurface );
	SDL_Rect continueRect; continueRect.x = 450; continueRect.y = 535;
	SDL_QueryTexture( continueTexture , NULL , NULL , &continueRect.w , &continueRect.h );

	isHoverBack = 0;

	// map choosing loop
	while( 1 ) {
		SDL_SetRenderDrawColor( myRenderer , 0xff , 0xff , 0xff , 0xff );
		SDL_RenderClear( myRenderer );

		SDL_RenderCopy( myRenderer , menuBackImgTexture , NULL , NULL );
		SDL_RenderCopy( myRenderer , chooseMapTexture , NULL , &chooseMapRect );
		SDL_RenderCopy( myRenderer , chooseDiffTexture , NULL , &chooseDiffRect );
		drawChoosingBoxes( myRenderer );
		SDL_RenderCopy( myRenderer , mediumTexture , NULL , &mediumRect );
		SDL_RenderCopy( myRenderer , hardTexture , NULL , &hardRect );
		SDL_RenderCopy ( myRenderer , ringlessGal , NULL , &ringlessRect );
		SDL_RenderCopy ( myRenderer , ringGal , NULL , &ringRect );
		SDL_RenderCopy ( myRenderer , random , NULL , &randomRect );
		SDL_RenderCopy ( myRenderer , continueTexture , NULL , &continueRect );
		SDL_RenderCopy ( myRenderer , ringedGalTexture , NULL , &ringedGalRect );
		SDL_RenderCopy ( myRenderer , ringlessGalTexture , NULL , &ringlessGalRect );
		SDL_RenderCopy ( myRenderer , randomTexture , NULL , &random2Rect );
		SDL_RenderCopy ( myRenderer , mediumExTexture , NULL , &mediumExRect );
		SDL_RenderCopy ( myRenderer , hardExTexture , NULL , &hardExRect );
		filledCircleRGBA( myRenderer , 50 , 550 , 30 , ORANGE.r , ORANGE.g , ORANGE.b , 255 );
		SDL_RenderCopy( myRenderer , backTexture , NULL , &backRect );
		

		// event handling
		int event3 = mapChoosingEventHandling( myRenderer );
		if( event3 == 0 )
			return 0;
		else if( event3 == 1 )
			break;
		else if ( event3 == 2 )
			goto MENU;

		if( isHoverMedium ) 
			roundedBoxColor( myRenderer , 200 , 100 , 450 , 170 , 10 , 0x2cffffff );
		else if( isHoverHard )
			roundedBoxColor( myRenderer , 550 , 100 , 800 , 170 , 10 , 0x2cffffff );
		else if( isHoverGal1 )
			roundedBoxColor( myRenderer , 40 , 270 , 320 , 500 , 10 , 0x11ffffff );
		else if( isHoverGal2 )
			roundedBoxColor( myRenderer , 360 , 270 , 640 , 500 , 10 , 0x11ffffff );
		else if( isHoverGal3 )
			roundedBoxColor( myRenderer , 680 , 270 , 960 , 500 , 10 , 0x11ffffff );
		else if( isHoverCon )
			roundedBoxColor( myRenderer , 400 , 525 , 600 , 580 , 10 , 0x2cffffff );
		else if( isHoverBack )
			filledCircleRGBA( myRenderer , 50 , 550 , 30 , WHITE.r , WHITE.g , WHITE.b , 40 );
		
		
		SDL_RenderPresent( myRenderer );
		SDL_Delay( 1000 / FPS );
		SDL_RenderClear( myRenderer );
	}

	// destroyings
	SDL_DestroyTexture( ringGal );
	SDL_DestroyTexture( ringlessGal );
	SDL_DestroyTexture( random );
	SDL_DestroyTexture( chooseDiffTexture );
	SDL_DestroyTexture( chooseMapTexture );
	SDL_DestroyTexture( mediumExTexture );
	SDL_DestroyTexture( hardExTexture );
	SDL_DestroyTexture( ringedGalTexture );
	SDL_DestroyTexture( ringlessGalTexture );
	SDL_DestroyTexture( randomTexture );
	SDL_DestroyTexture( continueTexture );

	SDL_FreeSurface( chooseDiffSurface );
	SDL_FreeSurface( chooseMapSurface );
	SDL_FreeSurface( mediumExSurface );
	SDL_FreeSurface( hardExSurface );
	SDL_FreeSurface( ringedGalSurface );
	SDL_FreeSurface( ringlessGalSurface );
	SDL_FreeSurface( randomSurface );
	SDL_FreeSurface( continueSurface );

}


if( scoreboard ) {

//SCOREBOARD
	SDL_Surface *leaderSurface = TTF_RenderText_Blended( funtasia100 , "Leaderboard" , YELLOW );
	SDL_Texture *leaderTexture = SDL_CreateTextureFromSurface ( myRenderer , leaderSurface );
	SDL_Rect leaderRect; leaderRect.x = 270; leaderRect.y = 20;
	SDL_QueryTexture( leaderTexture , NULL , NULL , &leaderRect.w , &leaderRect.h );

	SDL_Texture *leaderImgTexture = IMG_LoadTexture( myRenderer , "images/leaderboard.png" );
	SDL_Rect leaderImgRect; leaderImgRect.x = 150; leaderImgRect.y = 160; leaderImgRect.w = 700; leaderImgRect.h = 300;

	SDL_Texture *leader1Texture = IMG_LoadTexture( myRenderer , "images/leader1.png" );
	SDL_Rect leader1Rect; leader1Rect.x = 150; leader1Rect.y = 475; leader1Rect.w = 700; leader1Rect.h = 90;

	SDL_Surface *topSurface[4] , *topSSurface[4];
	SDL_Texture *topTexture[4] , *topSTexture[4];
	SDL_Rect topRect[4] , topSRect[4];
	char ttt[10];
	for( int u = 0; u < 4; u++ ) {
		ttt[0] = '\0'; sprintf( ttt , "%d" , sortedScores[u] );
		topSurface[u] = TTF_RenderText_Blended( funtasia50 , sortedNames[u] , WHITE );
		topSSurface[u] = TTF_RenderText_Blended( funtasia50 , ttt , WHITE );
		topTexture[u] = SDL_CreateTextureFromSurface ( myRenderer , topSurface[u] );
		topSTexture[u] = SDL_CreateTextureFromSurface ( myRenderer , topSSurface[u] );
		topRect[u].x = 300; topRect[u].y = 175 + (u * 105);
		topSRect[u].x = 720; topSRect[u].y = 175 + (u * 105);
		SDL_QueryTexture( topTexture[u] , NULL , NULL , &topRect[u].w , &topRect[u].h );
		SDL_QueryTexture( topSTexture[u] , NULL , NULL , &topSRect[u].w , &topSRect[u].h );
	}

	isHoverBack = 0;




	// scoreboard loop
	while( 1 ) {
		SDL_SetRenderDrawColor( myRenderer , 0xff , 0xff , 0xff , 0xff );
		SDL_RenderClear( myRenderer );

		SDL_RenderCopy( myRenderer , menuBackImgTexture , NULL , NULL );
		SDL_RenderCopy( myRenderer , leaderTexture , NULL , &leaderRect );
		SDL_RenderCopy( myRenderer , leaderImgTexture , NULL , &leaderImgRect );
		SDL_RenderCopy( myRenderer , leader1Texture , NULL , &leader1Rect );
		filledCircleRGBA( myRenderer , 50 , 550 , 30 , ORANGE.r , ORANGE.g , ORANGE.b , 255 );
		SDL_RenderCopy( myRenderer , backTexture , NULL , &backRect );
		for(int u = 0; u < 4; u++) {
			SDL_RenderCopy( myRenderer , topTexture[u] , NULL , &topRect[u] );
			SDL_RenderCopy( myRenderer , topSTexture[u] , NULL , &topSRect[u] );
		}

		
		// event handling
		int event5 = leaderboardEventHandling();
		if( !event5 )
			return 0;
		else if ( event5 == 1 )
			goto MENU;

		if( isHoverBack )
			filledCircleRGBA( myRenderer , 50 , 550 , 30 , WHITE.r , WHITE.g , WHITE.b , 40 );


		SDL_RenderPresent( myRenderer );
		SDL_Delay( 1000 / FPS );
		SDL_RenderClear( myRenderer );
	}

	// destroyings
	SDL_DestroyTexture( leader1Texture );
	SDL_DestroyTexture( leaderImgTexture );
	SDL_DestroyTexture( leaderTexture );
	for( int u = 0; u < 4; u++ ) {
		SDL_DestroyTexture( topTexture[u] );
		SDL_FreeSurface( topSurface[u] );
		SDL_DestroyTexture( topSTexture[u] );
		SDL_FreeSurface( topSSurface[u] );
	}
	SDL_FreeSurface( leaderSurface );



}



// GAME
	if( !loading )
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

	// You Win and You Lose
	SDL_Surface *youWinSurface = TTF_RenderText_Blended( funtasia100 , "YOU WIN" , GREEN );
	SDL_Texture *youWinTexture = SDL_CreateTextureFromSurface ( myRenderer , youWinSurface );
	SDL_Rect youWinRect; youWinRect.x = 320; youWinRect.y = 100;
	SDL_QueryTexture( youWinTexture , NULL , NULL , &youWinRect.w , &youWinRect.h );

	SDL_Surface *youLoseSurface = TTF_RenderText_Blended( funtasia100 , "YOU LOSE" , RED );
	SDL_Texture *youLoseTexture = SDL_CreateTextureFromSurface ( myRenderer , youLoseSurface );
	SDL_Rect youLoseRect; youLoseRect.x = 310; youLoseRect.y = 100;
	SDL_QueryTexture( youLoseTexture , NULL , NULL , &youLoseRect.w , &youLoseRect.h );

	SDL_Surface *returnSurface = TTF_RenderText_Blended( funtasia40 , "Return To Menu" , WHITE );
	SDL_Texture *returnTexture = SDL_CreateTextureFromSurface ( myRenderer , returnSurface );
	SDL_Rect returnRect; returnRect.x = 230; returnRect.y = 370;
	SDL_QueryTexture( returnTexture , NULL , NULL , &returnRect.w , &returnRect.h );

	SDL_Surface *quitSurface = TTF_RenderText_Blended( funtasia40 , "QUIT" , WHITE );
	SDL_Texture *quitTexture = SDL_CreateTextureFromSurface ( myRenderer , quitSurface );
	SDL_Rect quitRect; quitRect.x = 665; quitRect.y = 370;
	SDL_QueryTexture( quitTexture , NULL , NULL , &quitRect.w , &quitRect.h );

	// Potions
	SDL_Texture *rocketTexture = IMG_LoadTexture( myRenderer , "images/rocket.png");
	SDL_Rect rocketRect;

	SDL_Texture *snowTexture = IMG_LoadTexture( myRenderer , "images/snow.png");
	SDL_Rect snowRect;

	SDL_Texture *ufoTexture = IMG_LoadTexture( myRenderer , "images/ufo.png");
	SDL_Rect ufoRect;

	SDL_Texture *infTexture = IMG_LoadTexture( myRenderer , "images/inf.png");
	SDL_Rect infRect;


	Mix_HaltMusic();
	Mix_FreeMusic( menuMusic );

	// game loop
	while( 1 ) {
	
		SDL_SetRenderDrawColor( myRenderer , 0xff , 0xff , 0xff , 0xff );
		SDL_RenderClear( myRenderer );

		SDL_RenderCopy( myRenderer , mapBackImgTexture , NULL , NULL );
		printMap( myRenderer , n );
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < n; j++) {
				sprintf( solNumStr , "%d" , cities[i][j].soldiers_num );
				solNumSurface[i][j] = TTF_RenderText_Blended( funtasia20 , solNumStr , BLACK );
				solNumTexture[i][j] = SDL_CreateTextureFromSurface( myRenderer , solNumSurface[i][j] );
				SDL_QueryTexture( solNumTexture[i][j] , NULL , NULL , &textRect[i][j].w , &textRect[i][j].h );
				filledCircleColor( myRenderer , (cities[i][j].x1 + cities[i][j].x2) / 2 ,
				((cities[i][j].y1 + cities[i][j].y2) / 2) + (CENTER_R / 2) , CENTER_R , 0x6cffffff );
				SDL_RenderCopy( myRenderer , solNumTexture[i][j] , NULL , &textRect[i][j] );
			}
		}


		// AI
		if( AIisSendingSoldiers && !end ) 
			AIsendingSoldiers( myRenderer );
		

		// event handling
		int event4 = gameEventHandling( myRenderer );
		if( !event4 ) {
			if( !end ) 
				saveTheGame();
			break;
		}

		else if( event4 == 1 )
			goto MENU;

		else if( event4 == 2 )
			return 0;

		
		if ( mouseOnMe ) 
			lineColor( myRenderer , (cities[mei][mej].x1 + cities[mei][mej].x2) / 2 , (cities[mei][mej].y1 + cities[mei][mej].y2) / 2
			, mouse.x , mouse.y , 0xff000000 );
		
		if( isSendingSoldiers ) 
			sendingSoldiers( myRenderer );
		

		if( frame % INCREASE_RATE == 0 ) {
			if( !end ) {
				end = checkTheEnd();
				solNumIncreasing();
			}
		}

		if( frame % AI_INCREASE_RATE == 0 ) {
			if( !end ) {
				AIsolNumIncreasing();
			}
		}

		if( end ) {
			boxColor( myRenderer , 0 , 0 , SCREEN_WIDTH , SCREEN_HEIGHT , 0xca000000 );
			if( end == 1 ) 
				SDL_RenderCopy( myRenderer , youWinTexture , NULL , &youWinRect );
			
			else 
				SDL_RenderCopy( myRenderer , youLoseTexture , NULL , &youLoseRect );
				
			drawEndingBoxes( myRenderer );
			SDL_RenderCopy( myRenderer , returnTexture , NULL , &returnRect );
			SDL_RenderCopy( myRenderer , quitTexture , NULL , &quitRect );

			if( !update ) {
				updateScores();
				update = 1;
			}
		}

		if( isHoverReturn )
			roundedBoxRGBA( myRenderer , 200 , 350 , 500 , 440 , 10 , WHITE.r , WHITE.g , WHITE.b , 40 );

		else if( isHoverQuit )
			roundedBoxRGBA( myRenderer , 600 , 350 , 800 , 440 , 10 , WHITE.r , WHITE.g , WHITE.b , 40 );

		
		// potion
		if( rocketVisible && !end )
			SDL_RenderCopy( myRenderer , rocketTexture , NULL , &rocketRect );

		if( rocket.flag == 1 && !end ) {
			roundedBoxRGBA ( myRenderer , 20 , 10 , navarx , 30 , 3 , RED.r , RED.g , RED.b , 255 );
			if(navarx > 28) navarx -= 0.4;
			else {
				rocketOn = 0;
				MY_VEL = 3;
				rocket.flag = 0;
			}
		}

		if( rocket.flag == 2 && !end ) {
			roundedBoxRGBA ( myRenderer , navarai , 10 , 980 , 30 , 3 , YELLOW.r , YELLOW.g , YELLOW.b , 255 );
			if(navarai < 972) navarai += 0.4;
			else {
				rocketOn = 0;
				AI_VEL = 3;
				rocket.flag = 0;
			}
		}

		if( snowVisible && !end )
			SDL_RenderCopy( myRenderer , snowTexture , NULL , &snowRect );

		if( snow.flag == 1 && !end ) {
			roundedBoxRGBA ( myRenderer , 20 , 10 , navarx , 30 , 3 , RED.r , RED.g , RED.b , 255 );
			if(navarx > 28) navarx -= 0.4;
			else {
				snowOn = 0;
				snow.flag = 0;
				AI_VEL = 3;
			}
		}

		if( snow.flag == 2 && !end ) {
			roundedBoxRGBA ( myRenderer , navarai , 10 , 980 , 30 , 3 , YELLOW.r , YELLOW.g , YELLOW.b , 255 );
			if(navarai < 972) navarai += 0.4;
			else {
				snowOn = 0;
				MY_VEL = 3;
				snow.flag = 0;
			}
		}

		if( ufoVisible && !end )
			SDL_RenderCopy( myRenderer , ufoTexture , NULL , &ufoRect );

		if( ufo.flag == 1 && !end ) {
			roundedBoxRGBA ( myRenderer , 20 , 10 , navarx , 30 , 3 , RED.r , RED.g , RED.b , 255 );
			if(navarx > 28) navarx -= 0.4;
			else {
				ufoOn = 0;
				ufo.flag = 0;
				INCREASE_RATE = 60;
			}
		}

		if( ufo.flag == 2 && !end ) {
			roundedBoxRGBA ( myRenderer , navarai , 10 , 980 , 30 , 3 , YELLOW.r , YELLOW.g , YELLOW.b , 255 );
			if(navarai < 972) navarai += 0.4;
			else {
				ufoOn = 0;
				ufo.flag = 0;
				AI_INCREASE_RATE = 60;
			}
		}

		if( infVisible && !end )
			SDL_RenderCopy( myRenderer , infTexture , NULL , &infRect );

		if( inf.flag == 1 && !end ) {
			roundedBoxRGBA ( myRenderer , 20 , 10 , navarx , 30 , 3 , RED.r , RED.g , RED.b , 255 );
			if(navarx > 28) navarx -= 0.4;
			else {
				infOn = 0;
				inf.flag = 0;
			}
		}

		if( inf.flag == 2 && !end ) {
			roundedBoxRGBA ( myRenderer , navarai , 10 , 980 , 30 , 3 , YELLOW.r , YELLOW.g , YELLOW.b , 255 );
			if(navarai < 972) navarai += 0.4;
			else {
				infOn = 0;
				inf.flag = 0;
			}
		}

		
		SDL_RenderPresent( myRenderer );
		SDL_Delay( 1000 / FPS );
		SDL_RenderClear( myRenderer );

		int counter = 0;
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < n; j++) {
				SDL_DestroyTexture( planetsTexture[counter] );
				SDL_DestroyTexture( solNumTexture[i][j] );
				SDL_FreeSurface( solNumSurface[i][j] );
				counter++;
			}
		}


		// potions
		if( frame % 4000 == 1000 ) {
			rocketVisible = 1;
			rocketInit();
			rocketRect.x = rocket.x - 20; rocketRect.y = rocket.y - 20; rocketRect.w = 40; rocketRect.h = 40;
		}

		if( frame % 4000 == 1900 ) {
			snowVisible = 1;
			snowInit();
			snowRect.x = snow.x - 20; snowRect.y = snow.y - 20; snowRect.w = 40; snowRect.h = 40;
		}

		if( frame % 4000 == 2800 ) {
			ufoVisible = 1;
			ufoInit();
			ufoRect.x = ufo.x - 20; ufoRect.y = ufo.y - 20; ufoRect.w = 40; ufoRect.h = 40;
		}

		if( frame % 4000 == 100 ) {
			infVisible = 1;
			infInit();
			infRect.x = inf.x - 30; infRect.y = inf.y - 15; infRect.w = 60; infRect.h = 30;
		}

		

		if( frame % 4000 == 1400 ) 
			rocketVisible = 0;
		
		if( frame % 4000 == 2400 ) 
			snowVisible = 0;

		if( frame % 4000 == 3400 ) 
			ufoVisible = 0;

		if( frame % 4000 == 500 ) 
			infVisible = 0;
		


		
		frame++;

		if(frame % 10000 == 0) 
			frame = 1;
		
	}

	SDL_DestroyTexture( menuBackImgTexture );
	SDL_DestroyTexture( mapBackImgTexture );
	SDL_DestroyTexture( youWinTexture );
	SDL_DestroyTexture( youLoseTexture );
	SDL_DestroyTexture( returnTexture );
	SDL_DestroyTexture( quitTexture );
	SDL_DestroyTexture( rocketTexture );
	SDL_DestroyTexture( snowTexture );
	SDL_DestroyTexture( ufoTexture );
	SDL_DestroyTexture( infTexture );

	SDL_FreeSurface( youWinSurface );
	SDL_FreeSurface( youLoseSurface );
	SDL_FreeSurface( returnSurface );
	SDL_FreeSurface( quitSurface );


	TTF_CloseFont( funtasia100 );
	TTF_CloseFont( funtasia20 );
	TTF_CloseFont( funtasia40 );
	TTF_CloseFont( funtasia50 );
	TTF_CloseFont( funtasia70 );

	
	

	SDL_DestroyWindow( myWindow );
	SDL_DestroyRenderer( myRenderer );
	
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	
    return 0;
}
