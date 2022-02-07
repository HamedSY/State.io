#ifndef __MAP_C__
#define __MAP_C__

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "globals.h"


int gameEventHandling( SDL_Renderer *rend );
int initializingCities();
void print2DCity( int a , int b , City arr[a][b] );
void printMap( SDL_Renderer* rend , int n );
void sendingSoldiers( SDL_Renderer *rend );
void solNumIncreasing();
int checkTheEnd();


int gameEventHandling( SDL_Renderer *rend ) {
	SDL_Event ev;

	// AI
	int flag = 0 , max = 10;
	if( frame % AI_ATTACKING_FREQUENCY == 50 && !AIisSendingSoldiers ) {
		for( int i = 0; i < 4; i++ ) {
            for( int j = 0; j < n; j++ ) {
                if( cities[i][j].flag == 2 ) {
                    if( cities[i][j].soldiers_num > max ) {
						max = cities[i][j].soldiers_num;
                        flag = 1;
                        enemyi = i; enemyj = j;
                    }
                }
            }
        }
		if( flag ) {
			AIisSendingSoldiers = 1;
			cities[enemyi][enemyj].isSendingSol = 1;
			zeroer( 200 , AIflag );
			zeroer( 200 , AIflag2 );
			zeroer( 200 , AIhitflag );
			temp2 = cities[enemyi][enemyj].soldiers_num;
			for(int i = 0; i < cities[enemyi][enemyj].soldiers_num; i++) {
				soldier2[i].x = ((cities[enemyi][enemyj].x1 + cities[enemyi][enemyj].x2) / 2);
				soldier2[i].y = ((cities[enemyi][enemyj].y1 + cities[enemyi][enemyj].y2) / 2);
			}
			begin2.x = (cities[enemyi][enemyj].x1 + cities[enemyi][enemyj].x2) / 2;
			begin2.y = (cities[enemyi][enemyj].y1 + cities[enemyi][enemyj].y2) / 2;

			do {
				desti = rand() % 4;
				destj = rand() % n;
			} while( ( desti == enemyi && destj == enemyj ) || ( cities[desti][destj].soldiers_num > 40 && cities[desti][destj].flag == 2 )
				  || ( cities[desti][destj].flag == 2 ) || ( cities[desti][destj].soldiers_num >= cities[enemyi][enemyj].soldiers_num ) );

			dest2.x = ( cities[desti][destj].x1 + cities[desti][destj].x2 ) / 2;
			dest2.y = ( cities[desti][destj].y1 + cities[desti][destj].y2 ) / 2;

		}
	}

	// EVENTS
	while (SDL_PollEvent(&ev)) {
		mouse.x = ev.button.x;
		mouse.y = ev.button.y;

		if( ev.type == SDL_QUIT ) 
			return 0; // Quit

		if( ev.type == SDL_MOUSEBUTTONUP ) {
			
			if( !isSendingSoldiers && mouseOnMe &&
			!( mouse.x > cities[mei][mej].x1 && mouse.x < cities[mei][mej].x2 &&
			mouse.y > cities[mei][mej].y1 && mouse.y < cities[mei][mej].y2 ) ) {
				
				// printf("!hmmm\n");

				for(int i = 0; i < cities[mei][mej].soldiers_num; i++) {
					soldier[i].x = ((cities[mei][mej].x1 + cities[mei][mej].x2) / 2);
					soldier[i].y = ((cities[mei][mej].y1 + cities[mei][mej].y2) / 2);
				}

				begin.x = (cities[mei][mej].x1 + cities[mei][mej].x2) / 2;
				begin.y = (cities[mei][mej].y1 + cities[mei][mej].y2) / 2;

				dest = mouse;

				isSendingSoldiers = 1; 
				temp = cities[mei][mej].soldiers_num;
				zeroer( 200 , myflag );
				zeroer( 200 , myflag2 );
				zeroer( 200 , hitflag );
			}
			// else { isSendingSoldiers = 0; cities[mei][mej].isSendingSol = 0; }
			mouseOnMe = 0;
		}
		
		if( ev.type == SDL_MOUSEBUTTONDOWN ) {
			if(ev.button.button == SDL_BUTTON_LEFT ) {

				for(int i = 0; i < 4; i++) {
					for(int j = 0; j < n; j++) {
						if(cities[i][j].flag == 1) {
							mei = i; mej = j;
							if( ev.button.x >= cities[mei][mej].x1 && ev.button.x <= cities[mei][mej].x2  &&  
							ev.button.y >= cities[mei][mej].y1 && ev.button.y <= cities[mei][mej].y2 ) {
								mouseOnMe = 1;
								break;
							}
						}
					}
					if( mouseOnMe ) break;
				}
						
			}
		}
	}
	return 1;
}


void sendingSoldiers( SDL_Renderer *rend ) {
	int flag = 0 , i , j , incdec;
	if(!flag) {
		
		incdec = -1;
		for(i = 0; i < 4; i++) {
			for(j = 0; j < n; j++) {
				if( dest.x <= cities[i][j].x2 && dest.x >= cities[i][j].x1 &&
				dest.y <= cities[i][j].y2 && dest.y >= cities[i][j].y1 &&
				!( dest.x <= cities[mei][mej].x2 && dest.x >= cities[mei][mej].x1 &&
				dest.y <= cities[mei][mej].y2 && dest.y >= cities[mei][mej].y1 ) ) {

					dest.x = (cities[i][j].x1 + cities[i][j].x2) / 2;
					dest.y = (cities[i][j].y1 + cities[i][j].y2) / 2;
					flag = 1;
					// printf("flag is okay\n");
					break;
				}
			}
			if(flag) break;
		}
	}

	if(flag) {
		cities[mei][mej].isSendingSol = 1;
		for(int k = 0; k < temp; k++) {

			if( !hitflag[k] ) {

				if( begin.x > dest.x ) {
					if( soldier[k].x > dest.x ) {
						filledCircleColor( rend , soldier[k].x , soldier[k].y , SOLDIER_R , 0xffffffff );
						if( !myflag2[k] ) {
							cities[mei][mej].soldiers_num--;
							myflag2[k] = 1;
						}
					}
				}
						
				
				else if( begin.x < dest.x ) {
					if( soldier[k].x < dest.x ) {
						filledCircleColor( rend , soldier[k].x , soldier[k].y , SOLDIER_R , 0xffffffff );
						if( !myflag2[k] ) {
							cities[mei][mej].soldiers_num--;
							myflag2[k] = 1;
						}
					}
				}

				else {

					if( begin.y < dest.y ) {
						if( soldier[k].y < dest.y ) {
							filledCircleColor( rend , soldier[k].x , soldier[k].y , SOLDIER_R , 0xffffffff );
							if( !myflag2[k] ) {
								cities[mei][mej].soldiers_num--;
								myflag2[k] = 1;
							}
						}
					}

					else if( begin.y > dest.y ) {
						if( soldier[k].y > dest.y ) {
							filledCircleColor( rend , soldier[k].x , soldier[k].y , SOLDIER_R , 0xffffffff );
							if( !myflag2[k] ) {
								cities[mei][mej].soldiers_num--;
								myflag2[k] = 1;
							}
						}
					}
				}

			}
		
			
			soldier[k].x += velocity * (dest.x - begin.x) / ( sqrt ( ( (dest.x - begin.x) * (dest.x - begin.x) ) + ( (dest.y - begin.y) * (dest.y - begin.y) ) ) );
			soldier[k].y += velocity * (dest.y - begin.y) / ( sqrt ( ( (dest.x - begin.x) * (dest.x - begin.x) ) + ( (dest.y - begin.y) * (dest.y - begin.y) ) ) );
			
			
			// hit
			for(int u = 0; u < temp2; u++) {
				if( abs( soldier[k].x - soldier2[u].x ) < SOLDIER_R + 2 && abs( soldier[k].y - soldier2[u].y ) < SOLDIER_R + 2 &&
				( ( begin2.x > dest2.x && soldier2[u].x > dest2.x ) || ( begin2.x < dest2.x && soldier2[u].x < dest2.x ) ) ) {
					if( !hitflag[k] ) {
						hitflag[k] = 1;
						// printf("k is : %d\tu is : %d\n" , k , u);
					}
				}
			}
			
			if( abs(soldier[k].x - dest.x) <= 10 && abs(soldier[k].y - dest.y) <= 10 && !hitflag[k] ) {
				if( !myflag[k] ) {
					if( cities[i][j].flag == 1 ) {
						incdec = 1;
					}
					if( cities[i][j].soldiers_num <= 0 ) {
						cities[i][j].flag = 1;
						incdec = 1;
					}
					cities[i][j].soldiers_num += incdec;
					
					myflag[k] = 1;
				}
			}
			

			if( ( abs(soldier[k].x - dest.x) <= 10 && abs(soldier[k].y - dest.y) <= 10 && k == temp - 1 ) ||
			hitflag[ temp - 1 ] || hitflag[ temp - 2 ] ) {
				isSendingSoldiers = 0;
            	// soldier[ temp - 1 ].x = 0; soldier[ temp - 1 ].y = 0;
				coordZeroer( 200 , soldier );
				cities[mei][mej].isSendingSol = 0;
			}

			if( ( abs( soldier[k].x - soldier[k + 1].x ) <= 8 ) && ( abs( soldier[k].y - soldier[k + 1].y ) <= 8 ) ) {
				break;
			}
			else velocity = 3;


		}
	}
}

void solNumIncreasing() {
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < n; j++) {
			if(cities[i][j].flag) {
				if(cities[i][j].soldiers_num < COLOR_SOLDIERS_MAX_NUM ) {
					cities[i][j].soldiers_num ++;
				}
			}
		}
	}
}

int checkTheEnd() {
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < n; j++) {
			if( cities[i][j].flag ) {
				for( int k = 0 ; k < 4; k++ ) {
					for( int u = 0; u < n; u++ ) {
						if( cities[i][j].flag != cities[k][u].flag && cities[k][u].flag != 0 ) {
							return 0;
						}
					}
				}
				return 1;
			}
		}
	}			
	return -1;
}


int initializingCities() {
	int length[6] = {0} , width[4][6] = {0} , theta , n = 4 + (rand() % 3);
	int color = 0xff000000;
	
	for(int i = 0; i < 4; i++) {
		cities[i][0].x1 = 40 + (rand() % 30);
		if(i != 0) cities[i][0].y1 = (rand() % 20) + 30 + cities[i - 1][0].y2;
		else cities[i][0].y1 = (rand() % 30) + 40;

		for(int j = 0; j < n; j++) {
			theta = (rand() % 10) + 5;
			if(i == 0) length[j] = (rand() % 30) + 370 - (n * 50);
			width[i][j] = (rand() % 30) + 60;
			cities[i][j].x2 = cities[i][j].x1 + length[j];
			cities[i][j].y2 = cities[i][j].y1 + width[i][j];
			cities[i][j].theta = theta;

			cities[i][j + 1].x1 = cities[i][j].x2 + (rand() % 20) + 40;
			if(i != 0) cities[i][j + 1].y1 = cities[i - 1][j + 1].y2 + (rand() % 20) + 40;
			else cities[i][j + 1].y1 = (rand() % 30) + 40;

			cities[i][j].soldiers_num = 10;
			cities[i][j].isSendingSol = 0;

		}
	}

	mei = rand() % 4;
	mej = rand() % n;
	do {
		enemyi = rand() % 4;
		enemyj = rand() % n;
	} while( (enemyi == mei && enemyj == mej) );

	cities[mei][mej].flag = 1;
	cities[mei][mej].soldiers_num += 30;
	cities[enemyi][enemyj].flag = 2;
	cities[enemyi][enemyj].soldiers_num += 30;

	return n;
}

void printMap( SDL_Renderer* rend , int n ) {
	int theta;
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < n; j++) {
			
			if( cities[i][j].flag == 1 ) {
				roundedBoxRGBA( rend , cities[i][j].x1 , cities[i][j].y1 , cities[i][j].x2 , cities[i][j].y2 , cities[i][j].theta ,
				200 , 10 , 10 , 255 );
				filledCircleRGBA( rend , (cities[i][j].x1 + cities[i][j].x2) / 2 , (cities[i][j].y1 + cities[i][j].y2) / 2 ,
				CENTER_R , 150 , 10 , 10 , 255 );				
			}

			else if( cities[i][j].flag == 2 ) {
				roundedBoxRGBA( rend , cities[i][j].x1 , cities[i][j].y1 , cities[i][j].x2 , cities[i][j].y2 , cities[i][j].theta ,
				10 , 200 , 10 , 255 );
				filledCircleRGBA( rend , (cities[i][j].x1 + cities[i][j].x2) / 2 , (cities[i][j].y1 + cities[i][j].y2) / 2 ,
				CENTER_R , 10 , 150 , 10 , 255 );
			}

			else {
				roundedBoxRGBA( rend , cities[i][j].x1 , cities[i][j].y1 , cities[i][j].x2 , cities[i][j].y2 , cities[i][j].theta ,
				170 , 200 , 180 , 255 );
				filledCircleRGBA( rend , (cities[i][j].x1 + cities[i][j].x2) / 2 , (cities[i][j].y1 + cities[i][j].y2) / 2 ,
				CENTER_R , 150 , 160 , 180 , 255 );
			}
		}
	}
}



#endif