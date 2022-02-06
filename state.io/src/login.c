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
        if( mouse.x > 200 && mouse.x < 400 && mouse.y > 430 && mouse.y < 500 ) {
			isHoverContinue = 1;
			if( ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT ) {
				return 1;
			}
		}
		else 
			isHoverContinue = 0;
        
        if( ev.type == SDL_TEXTINPUT || ev.type == SDL_KEYDOWN ) {
			if( ev.type == SDL_TEXTINPUT ) {
				strcat( username , ev.text.text );
				isTyping = 1;
			}
			else if( ev.type == SDL_KEYDOWN ) {
				if( keystate[SDL_SCANCODE_BACKSPACE] && strlen( username ) > 0 ) {
					username[ strlen(username) - 1 ] = '\0';
				}
			}
		}
		
    }

	

    return -1;
}


void usernameInputBox( SDL_Renderer *rend ) {
    roundedBoxColor( rend , 50 , 250 , 550 , 400 , 10 , 0xdfffffff );
    roundedBoxColor( rend , 200 , 430 , 400 , 500 , 10 , 0xdf12af32  );
}



#endif