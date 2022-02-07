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
                    filledCircleColor( rend , soldier2[k].x , soldier2[k].y , SOLDIER_R , 0xffffffff );
                    if( !AIflag2[k] ) {
                        cities[enemyi][enemyj].soldiers_num--;
                        AIflag2[k] = 1;
                    }
                }
            }
                    
            
            else if( begin2.x < dest2.x ) {
                if( soldier2[k].x < dest2.x ) {
                    filledCircleColor( rend , soldier2[k].x , soldier2[k].y , SOLDIER_R , 0xffffffff );
                    if( !AIflag2[k] ) {
                        cities[enemyi][enemyj].soldiers_num--;
                        AIflag2[k] = 1;
                    }
                }
            }

            else {

                if( begin2.y < dest2.y ) {
                    if( soldier2[k].y < dest2.y ) {
                        filledCircleColor( rend , soldier2[k].x , soldier2[k].y , SOLDIER_R , 0xffffffff );
                        if( !AIflag2[k] ) {
                            cities[enemyi][enemyj].soldiers_num--;
                            AIflag2[k] = 1;
                        }
                    }
                }

                else if( begin2.y > dest2.y ) {
                    if( soldier2[k].y > dest2.y ) {
                        filledCircleColor( rend , soldier2[k].x , soldier2[k].y , SOLDIER_R , 0xffffffff );
                        if( !AIflag2[k] ) {
                            cities[enemyi][enemyj].soldiers_num--;
                            AIflag2[k] = 1;
                        }
                    }
                }
                
            }

        }
    
        soldier2[k].x += velocity * (dest2.x - begin2.x) / ( sqrt ( ( (dest2.x - begin2.x) * (dest2.x - begin2.x) ) + ( (dest2.y - begin2.y) * (dest2.y - begin2.y) ) ) );
        soldier2[k].y += velocity * (dest2.y - begin2.y) / ( sqrt ( ( (dest2.x - begin2.x) * (dest2.x - begin2.x) ) + ( (dest2.y - begin2.y) * (dest2.y - begin2.y) ) ) );

        // hit
        for(int u = 0; u < temp; u++) {
            if( abs( soldier2[k].x - soldier[u].x ) < SOLDIER_R + 2 && abs( soldier2[k].y - soldier[u].y ) < SOLDIER_R + 2 &&
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
            printf("AI got 0\n");
            AIhitcounter = 0;
            coordZeroer( 200 , soldier2 );
            cities[enemyi][enemyj].isSendingSol = 0;
            // flag = 0;
        }

        if( ( abs( soldier2[k].x - soldier2[k + 1].x ) <= 10 ) && ( abs( soldier2[k].y - soldier2[k + 1].y ) <= 10 ) ) {
            break;
        }
        else velocity = 3;


    }

}





#endif