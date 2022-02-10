#ifndef __AI_C__
#define __AI_C__

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "globals.h"


void AIsendingSoldiers( SDL_Renderer *rend ) {
    int incdec = -1;
    
    for(int k = 0; k < temp2; k++) {

        if( !AIhitflag[k] ) {

            if( begin2.x > dest2.x ) {
                if( soldier2[k].x > dest2.x ) {
                    filledCircleColor( rend , soldier2[k].x , soldier2[k].y , SOLDIER_R + 2 , 0xffffffff );
                    filledCircleRGBA( rend , soldier2[k].x , soldier2[k].y , SOLDIER_R , 248 , 248 , 37 , 255 );
                    if( !AIflag2[k] ) {
                        cities[enemyi][enemyj].soldiers_num--;
                        AIflag2[k] = 1;
                    }
                }
            }
                    
            
            else if( begin2.x < dest2.x ) {
                if( soldier2[k].x < dest2.x ) {
                    filledCircleColor( rend , soldier2[k].x , soldier2[k].y , SOLDIER_R + 2 , 0xffffffff );
                    filledCircleRGBA( rend , soldier2[k].x , soldier2[k].y , SOLDIER_R , 248 , 248 , 37 , 255 );
                    if( !AIflag2[k] ) {
                        cities[enemyi][enemyj].soldiers_num--;
                        AIflag2[k] = 1;
                    }
                }
            }

            else {

                if( begin2.y < dest2.y ) {
                    if( soldier2[k].y < dest2.y ) {
                        filledCircleColor( rend , soldier2[k].x , soldier2[k].y , SOLDIER_R + 2 , 0xffffffff );
                        filledCircleRGBA( rend , soldier2[k].x , soldier2[k].y , SOLDIER_R , 248 , 248 , 37 , 255 );
                        if( !AIflag2[k] ) {
                            cities[enemyi][enemyj].soldiers_num--;
                            AIflag2[k] = 1;
                        }
                    }
                }

                else if( begin2.y > dest2.y ) {
                    if( soldier2[k].y > dest2.y ) {
                        filledCircleColor( rend , soldier2[k].x , soldier2[k].y , SOLDIER_R + 2 , 0xffffffff );
                        filledCircleRGBA( rend , soldier2[k].x , soldier2[k].y , SOLDIER_R , 248 , 248 , 37 , 255 );
                        if( !AIflag2[k] ) {
                            cities[enemyi][enemyj].soldiers_num--;
                            AIflag2[k] = 1;
                        }
                    }
                }
                
            }

        }
    
        // if( !snowOn ) {
            soldier2[k].x += AI_VEL * ( (dest2.x - begin2.x) / ( sqrt ( ( (dest2.x - begin2.x) * (dest2.x - begin2.x) ) + ( (dest2.y - begin2.y) * (dest2.y - begin2.y) ) ) ) );
            soldier2[k].y += AI_VEL * ( (dest2.y - begin2.y) / ( sqrt ( ( (dest2.x - begin2.x) * (dest2.x - begin2.x) ) + ( (dest2.y - begin2.y) * (dest2.y - begin2.y) ) ) ) );
        // }


        // potions
        if( snow.flag == 1 ) 
            AI_VEL = 0;

        // potion
			if( abs( rocket.x - soldier2[k].x ) < SOLDIER_R + 12 && abs( rocket.y - soldier2[k].y ) < SOLDIER_R + 12 && rocketVisible
			&& rocket.flag != 2 ) {
				rocketVisible = 0;
				rocketOn = 1;
				rocket.flag = 2;
				AI_VEL = 6;
				navarx = 750;
			}

			else if( abs( snow.x - soldier2[k].x ) < SOLDIER_R + 12 && abs( snow.y - soldier2[k].y ) < SOLDIER_R + 12 && snowVisible
			&& snow.flag != 2 ) {
				snowVisible = 0;
				snowOn = 1;
				snow.flag = 2;
				navarai = 750;
			}

			else if( abs( ufo.x - soldier2[k].x ) < SOLDIER_R + 12 && abs( ufo.y - soldier2[k].y ) < SOLDIER_R + 12 && ufoVisible
			&& ufo.flag != 2 ) {
				ufoVisible = 0;
				ufoOn = 1;
				ufo.flag = 2;
				navarx = 750;
				AI_INCREASE_RATE = 15;
			}

			else if( abs( inf.x - soldier2[k].x ) < SOLDIER_R + 12 && abs( inf.y - soldier2[k].y ) < SOLDIER_R + 12 && infVisible
			&& inf.flag != 1 ) {
				infVisible = 0;
				infOn = 1;
				inf.flag = 2;
				navarx = 750;
			}


        // hit
            for(int u = 0; u < temp; u++) {
                if( abs( soldier2[k].x - soldier[u].x ) < SOLDIER_R + 1 && abs( soldier2[k].y - soldier[u].y ) < SOLDIER_R + 1 &&
                ( ( begin.x > dest.x && soldier[u].x > dest.x ) || ( begin.x < dest.x && soldier[u].x < dest.x ) ) ) {
                    if( !AIhitflag[k] ) {
                        AIhitflag[k] = 1;
                        AIhitcounter++;
                    }
                }
            }
        
        if( abs(soldier2[k].x - dest2.x) <= 10 && abs(soldier2[k].y - dest2.y) <= 10 && !AIhitflag[k] ) {
            if( !AIflag[k] ) {
                if( cities[desti][destj].flag == 2 ) {
                    incdec = 1;
                }
                if( cities[desti][destj].soldiers_num <= 0 ) {
                    cities[desti][destj].flag = 2;
                    incdec = 1;
                }
                cities[desti][destj].soldiers_num += incdec;
                AIflag[k] = 1;
            }
        }
        

        if( ( abs(soldier2[ temp2 - 1 ].x - dest2.x) <= 10 && abs(soldier2[ temp2 - 1 ].y - dest2.y) <= 10 ) ||
        AIhitcounter == temp2  ) {
            AIisSendingSoldiers = 0;
            // printf("AI got 0\n");
            AIhitcounter = 0;
            coordZeroer( 200 , soldier2 );
            // cities[enemyi][enemyj].isSendingSol = 0;
            // flag = 0;
        }

        if( ( abs( soldier2[k].x - soldier2[k + 1].x ) <= 10 ) && ( abs( soldier2[k].y - soldier2[k + 1].y ) <= 10 ) && !snowOn ) {
            break;
        }
        // else velocity = AI_VEL;


    }

}





#endif