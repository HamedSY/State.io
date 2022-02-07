#ifndef __LOGIN_C__
#define __LOGIN_C__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "globals.h"

int menuEventHandling( SDL_Renderer *rend );
void usernameInputBox( SDL_Renderer *rend );


int loginEventHandling( SDL_Renderer *rend ) {
	SDL_Event ev;
	const unsigned char *keystate = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&ev)) {
		mouse.x = ev.button.x;
		mouse.y = ev.button.y;

		if( ev.type == SDL_QUIT ) 
			return 0; // Quit
        if( mouse.x > 400 && mouse.x < 600 && mouse.y > 450 && mouse.y < 520 ) {
			isHoverContinue = 1;
			if( ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT ) {
				return 1;
			}
		}
		else 
			isHoverContinue = 0;
        
        if( ( ev.type == SDL_TEXTINPUT || ev.type == SDL_KEYDOWN ) ) {
			if( ev.type == SDL_TEXTINPUT && inputLoc < 200 ) {
				strcat( username , ev.text.text );
				inputLoc += 11;
				isTyping = 1;
			}
			else if( ev.type == SDL_KEYDOWN ) {
				if( keystate[SDL_SCANCODE_BACKSPACE] && strlen( username ) > 0 ) {
					username[ strlen(username) - 1 ] = '\0';
					inputLoc -= 11;
				}
				else if ( ev.key.keysym.sym == SDLK_RETURN ) {
					return 1;
				}
			}
		}
		
    }

	

    return -1;
}


void usernameInputBox( SDL_Renderer *rend ) {
    roundedBoxColor( rend , 250 , 250 , 750 , 400 , 10 , 0xdfffffff );
    roundedBoxRGBA( rend , 400 , 450 , 600 , 520 , 10 , 0 , 103 , 217 , 255 );
}



#endif