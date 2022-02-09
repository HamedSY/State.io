#ifndef __MAP_CHOOSING_C__
#define __MAP_CHOOSING_C__

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "globals.h"



int mapChoosingEventHandling( SDL_Renderer *rend ) {
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {
		mouse.x = ev.button.x;
		mouse.y = ev.button.y;

		if( ev.type == SDL_QUIT ) 
			return 0; // Quit


        if( mouse.x > 200 && mouse.x < 450 && mouse.y > 100 && mouse.y < 170 ) {
			isHoverMedium = 1;
			if( ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT ) {
				diff = 1;
			}
		}
		else 
			isHoverMedium = 0;


        if( mouse.x > 550 && mouse.x < 800 && mouse.y > 100 && mouse.y < 170 ) {
			isHoverHard = 1;
			if( ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT ) {
				diff = 2;
			}
		}
		else 
			isHoverHard = 0;


        if( mouse.x > 40 && mouse.x < 320 && mouse.y > 210 && mouse.y < 500 ) {
			isHoverGal1 = 1;
			if( ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT ) {
				gal = 1;
			}
		}
		else 
			isHoverGal1 = 0;


        if( mouse.x > 360 && mouse.x < 640 && mouse.y > 210 && mouse.y < 500 ) {
			isHoverGal2 = 1;
			if( ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT ) {
				gal = 2;
			}
		}
		else 
			isHoverGal2 = 0;


        if( mouse.x > 680 && mouse.x < 960 && mouse.y > 270 && mouse.y < 500 ) {
			isHoverGal3 = 1;
			if( ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT ) {
				gal = 3;
			}
		}
		else 
			isHoverGal3 = 0;


		if( mouse.x > 400 && mouse.x < 600 && mouse.y > 525 && mouse.y < 580 ) {
			isHoverCon = 1;
			if( ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT && gal && diff ) {
				return 1;
			}
		}
		else 
			isHoverCon = 0;

		
		if( abs( mouse.x - 50 ) < 30 && abs( mouse.y - 530 ) < 30 ) {
			isHoverBack = 1;
			if( ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT ) {
				return 2;
			}
		}
		else 
			isHoverBack = 0;




    }

    return -1;

}


void drawChoosingBoxes( SDL_Renderer *rend ) {
    SDL_Color mcolor = LIGHT_BLUE , hcolor = LIGHT_BLUE , color1 = LIGHT_BLUE , color2 = LIGHT_BLUE , color3 = LIGHT_BLUE;
	
    if( diff == 1 )
        mcolor = LIGHT_PURPLE;
    else if ( diff == 2 )
        hcolor = LIGHT_PURPLE;

    // difficulty boxes
    roundedBoxRGBA( rend , 200 , 100 , 450 , 170 , 10 , mcolor.r , mcolor.g , mcolor.b , 255 );
    roundedBoxRGBA( rend , 550 , 100 , 800 , 170 , 10 , hcolor.r , hcolor.g , hcolor.b , 255 );

    if( gal == 1 )
        color1 = LIGHT_PURPLE;
    else if ( gal == 2 )
        color2 = LIGHT_PURPLE;
    else if ( gal == 3 )
        color3 = LIGHT_PURPLE;

    // galaxies
    roundedBoxRGBA( rend , 40 , 270 , 320 , 500 , 10 , color1.r , color1.g , color1.b , 200 );
    roundedBoxRGBA( rend , 360 , 270 , 640 , 500 , 10 , color2.r , color2.g , color2.b , 200 );
    roundedBoxRGBA( rend , 680 , 270 , 960 , 500 , 10 , color3.r , color3.g , color3.b , 200 );
	// continue
	roundedBoxRGBA( rend , 400 , 525 , 600 , 580 , 10 , GREEN.r , GREEN.g , GREEN.b , 255 );


}









#endif