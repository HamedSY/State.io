#ifndef __MENU_C__
#define __MENU_C__

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "globals.h"

int menuEventHandling( SDL_Renderer *rend );
void drawBox( SDL_Renderer *rend );



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





#endif