#ifndef __AI_C__
#define __AI_C__

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "globals.h"


void AIsendingSoldiers( SDL_Renderer *rend ) {
    int flag = 0;
    for( int i = 0; i < 4; i++ ) {
        for( int j = 0; j < n; j++ ) {
            if( cities[i][j].flag == 2 ) {
                if( rand() % 2 ) {
                    flag = 1;
                    enemyi = i; enemyj = j;
                }
            }
        }
    }

    if( flag ) {

        begin2.x = (cities[enemyi][enemyj].x1 + cities[enemyi][enemyj].x2) / 2;
		begin2.y = (cities[enemyi][enemyj].y1 + cities[enemyi][enemyj].y2) / 2;

        for(int k = 0; k < cities[enemyi][enemyj].soldiers_num; k++) {

        }

    }

}





#endif