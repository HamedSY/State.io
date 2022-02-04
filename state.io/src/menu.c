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
	roundedBoxColor( rend , 150 , 275 , 450 , 350 , 10 , 0xdfffffff );
	roundedBoxColor( rend , 150 , 375 , 450 , 450 , 10 , 0xdfffffff );
	roundedBoxColor( rend , 150 , 475 , 450 , 550 , 10 , 0xdfffffff );
}

int menuEventHandling( SDL_Renderer *rend ) {
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		mouse.x = ev.button.x;
		mouse.y = ev.button.y;

		if( ev.type == SDL_QUIT ) 
			return 0; // Quit
		if( mouse.x > 150 && mouse.x < 450 && mouse.y > 275 && mouse.y < 350 ) {
			isHoverStartGame = 1;
			if( ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT ) {
				return 1;
			}
		}
		else 
			isHoverStartGame = 0;
    }
    return -1;
}





#endif