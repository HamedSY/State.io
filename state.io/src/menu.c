#ifndef __MENU_C__
#define __MENU_C__

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "globals.h"



void drawMenuBoxes( SDL_Renderer *rend ) {
	roundedBoxRGBA( rend , 350 , 250 , 650 , 330 , 10 , LIGHT_BLUE.r , LIGHT_BLUE.g , LIGHT_BLUE.b , LIGHT_BLUE.a );
	roundedBoxRGBA( rend , 350 , 365 , 650 , 445 , 10 , LIGHT_BLUE.r , LIGHT_BLUE.g , LIGHT_BLUE.b , LIGHT_BLUE.a );
	roundedBoxRGBA( rend , 350 , 480 , 650 , 560 , 10 , LIGHT_BLUE.r , LIGHT_BLUE.g , LIGHT_BLUE.b , LIGHT_BLUE.a );
}

int menuEventHandling( SDL_Renderer *rend ) {
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		mouse.x = ev.button.x;
		mouse.y = ev.button.y;

		if( ev.type == SDL_QUIT ) 
			return 0; // Quit
		if( mouse.x > 350 && mouse.x < 650 && mouse.y > 250 && mouse.y < 330 ) {
			isHovernewGame = 1;
			if( ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT ) {
				return 1;
			}
		}
		else 
			isHovernewGame = 0;


		if( mouse.x > 350 && mouse.x < 650 && mouse.y > 365 && mouse.y < 445 ) {
			isHoverLoadGame = 1;
			if( ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT ) {
				return 2;
			}
		}
		else 
			isHoverLoadGame = 0;


		if( mouse.x > 350 && mouse.x < 650 && mouse.y > 480 && mouse.y < 560 ) {
			isHoverScoreBoard = 1;
			if( ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT ) {
				return 3;
			}
		}
		else 
			isHoverScoreBoard = 0;
    }
    return -1;
}


void loadTheGame() {
	
	FILE *gameDetails = fopen( "savings/game_details.txt" , "r" );

	fscanf( gameDetails , "%d\n" , &n );
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < n; j++) {
			fscanf( gameDetails , "%d %d %d %d %d %d %d\n" , &cities[i][j].x1 , &cities[i][j].x2 , &cities[i][j].y1 ,
			&cities[i][j].y2 , &cities[i][j].flag , &cities[i][j].soldiers_num , &cities[i][j].number );
			planetsRect[i][j].x = cities[i][j].x1;
			planetsRect[i][j].y = cities[i][j].y1;
		}
	}
	fclose( gameDetails );

}





void globalsInit() {

	SCREEN_WIDTH = 1000 ; SCREEN_HEIGHT = 600;
	FPS = 60;
	CENTER_R = 15 ; SOLDIER_R = 3;
	COLOR_SOLDIERS_MAX_NUM = 60;
	ORDINARY_SOLDIERS_MAX_NUM = 10;
	AI_ATTACKING_FREQUENCY = 100;

	BLACK = (SDL_Color){ 0 , 0 , 0 , 255 };
	WHITE = (SDL_Color){ 255 , 255 , 255 , 255 };
	YELLOW = (SDL_Color){ 255 , 231 , 47 , 255 };
	ORANGE = (SDL_Color){ 255 , 178 , 0 , 255 };
	LIGHT_BLUE = (SDL_Color){ 0 , 103 , 217 , 255 };
	DARK_BLUE = (SDL_Color){ 0 , 24 , 168 , 255 };
	LIGHT_PURPLE = (SDL_Color){ 149 , 50 , 170 , 255 };
	DARK_PURPLE = (SDL_Color){ 81 , 40 , 136 , 255 };
	GREEN = (SDL_Color){ 30 , 140 , 50 , 255 };

	mouseOnMe = 0 ; isSendingSoldiers = 0 ; AIisSendingSoldiers = 0;
	isHovernewGame = 0 ; isHoverContinue = 0 ; isTyping = 0 ; isHoverLoadGame = 0 ; isHoverScoreBoard = 0 ;
	isHoverMedium = 0 ; isHoverHard = 0 ; isHoverGal1 = 0 ; isHoverGal2 = 0 ; isHoverGal3 = 0 ; isHoverCon = 0;
	diff = 0 ; gal = 0; end = 0; loading = 0;
	hitcounter = 0 ; AIhitcounter = 0; inputLoc = 0;
	frame = 1;
	velocity = 3;

	ringedPlanets[0] = 1;   ringlessPlanets[0] = 2;
	ringedPlanets[1] = 3;   ringlessPlanets[1] = 4;
	ringedPlanets[2] = 5;   ringlessPlanets[2] = 6;
	ringedPlanets[3] = 7;   ringlessPlanets[3] = 11;
	ringedPlanets[4] = 8;   ringlessPlanets[4] = 12;
	ringedPlanets[5] = 9;   ringlessPlanets[5] = 13;
	ringedPlanets[6] = 10;  ringlessPlanets[6] = 14;
	ringedPlanets[7] = 15;  ringlessPlanets[7] = 17;
	ringedPlanets[8] = 16;  ringlessPlanets[8] = 18;

}




#endif