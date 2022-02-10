#ifndef __GAME_C__
#define __GAME_C__

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include "globals.h"




void zeroer( int n , int a[] ) {
	for(int i = 0; i < n; i++)
		a[i] = 0;
}

void coordZeroer( int n , Coordination a[] ) {
	for(int i = 0; i < n; i++) {
		a[i].x = 0;
		a[i].y = 0;
	}
}

int gameEventHandling( SDL_Renderer *rend ) {
	SDL_Event ev;

	// AI
	int flag = 0 , max = 10;
	int correctAttack = 0;

	if( frame % AI_ATTACKING_FREQUENCY == 50 && !AIisSendingSoldiers ) {
		for( int i = 0; i < 3; i++ ) {
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
			// printf("AI got 1\n");
			// cities[enemyi][enemyj].isSendingSol = 1;
			zeroer( 200 , AIflag );
			zeroer( 200 , AIflag2 );
			zeroer( 200 , AIhitflag );
			temp2 = cities[enemyi][enemyj].soldiers_num;
			for(int i = 0; i < cities[enemyi][enemyj].soldiers_num; i++) {
				soldier2[i].x = ((cities[enemyi][enemyj].x1 + cities[enemyi][enemyj].x2) / 2);
				soldier2[i].y = ((cities[enemyi][enemyj].y1 + cities[enemyi][enemyj].y2) / 2);
				// printf("sol2.x : %lf / sol2.y : %lf\n" , soldier2[i].x , soldier2[i].y );
			}
			begin2.x = (cities[enemyi][enemyj].x1 + cities[enemyi][enemyj].x2) / 2;
			begin2.y = (cities[enemyi][enemyj].y1 + cities[enemyi][enemyj].y2) / 2;

			do {
				desti = rand() % 3;
				destj = rand() % n;
			} while( ( desti == enemyi && destj == enemyj ) || ( cities[desti][destj].flag == 2 )
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

		if( !end ) {

			if( ev.type == SDL_MOUSEBUTTONUP ) {
				
				if( !isSendingSoldiers && mouseOnMe &&
				!( mouse.x > cities[mei][mej].x1 && mouse.x < cities[mei][mej].x2 &&
				mouse.y > cities[mei][mej].y1 && mouse.y < cities[mei][mej].y2 ) ) {
					
					for( int i = 0; i < 3; i++ ) {
						for( int j = 0; j < n; j++ ) {
							if( ev.button.x >= cities[i][j].x1 && ev.button.x <= cities[i][j].x2  &&  
							ev.button.y >= cities[i][j].y1 && ev.button.y <= cities[i][j].y2 ) {
								correctAttack = 1;
							}
						}
					}

					if( correctAttack ) {

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
				}
				// else { isSendingSoldiers = 0; cities[mei][mej].isSendingSol = 0; }
				mouseOnMe = 0;
			}
			
			if( ev.type == SDL_MOUSEBUTTONDOWN ) {
				if(ev.button.button == SDL_BUTTON_LEFT ) {

					for(int i = 0; i < 3; i++) {
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

		else if ( end ) {

			if( mouse.x > 200 && mouse.x < 500 && mouse.y > 350 && mouse.y < 440 ) {
				isHoverReturn = 1;
				if( ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT ) {
					return 1;
				}
			}
			else 
				isHoverReturn = 0;


			if( mouse.x > 600 && mouse.x < 800 && mouse.y > 350 && mouse.y < 440 ) {
				isHoverQuit = 1;
				if( ev.type == SDL_MOUSEBUTTONDOWN && ev.button.button == SDL_BUTTON_LEFT ) {
					return 2;
				}
			}
			else 
				isHoverQuit = 0;

		}
	}
	return -1;
}


void sendingSoldiers( SDL_Renderer *rend ) {
	int flag = 0 , i , j , incdec;
	if(!flag) {
		
		incdec = -1;
		for(i = 0; i < 3; i++) {
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
		// cities[mei][mej].isSendingSol = 1;
		for(int k = 0; k < temp; k++) {

			if( !hitflag[k] ) {

				if( begin.x > dest.x ) {
					if( soldier[k].x > dest.x ) {
						filledCircleColor( rend , soldier[k].x , soldier[k].y , SOLDIER_R + 2 , 0xffffffff );
						filledCircleRGBA( rend , soldier[k].x , soldier[k].y , SOLDIER_R , 243 , 34 , 34 , 255 );
						if( !myflag2[k] ) {
							cities[mei][mej].soldiers_num--;
							myflag2[k] = 1;
						}
					}
				}
						
				
				else if( begin.x < dest.x ) {
					if( soldier[k].x < dest.x ) {
						filledCircleColor( rend , soldier[k].x , soldier[k].y , SOLDIER_R + 2 , 0xffffffff );
						filledCircleRGBA( rend , soldier[k].x , soldier[k].y , SOLDIER_R , 243 , 34 , 34 , 255 );
						if( !myflag2[k] ) {
							cities[mei][mej].soldiers_num--;
							myflag2[k] = 1;
						}
					}
				}

				else {

					if( begin.y < dest.y ) {
						if( soldier[k].y < dest.y ) {
							filledCircleColor( rend , soldier[k].x , soldier[k].y , SOLDIER_R + 2 , 0xffffffff );
							filledCircleRGBA( rend , soldier[k].x , soldier[k].y , SOLDIER_R , 243 , 34 , 34 , 255 );
							if( !myflag2[k] ) {
								cities[mei][mej].soldiers_num--;
								myflag2[k] = 1;
							}
						}
					}

					else if( begin.y > dest.y ) {
						if( soldier[k].y > dest.y ) {
							filledCircleColor( rend , soldier[k].x , soldier[k].y , SOLDIER_R + 2 , 0xffffffff );
							filledCircleRGBA( rend , soldier[k].x , soldier[k].y , SOLDIER_R , 243 , 34 , 34 , 255 );
							if( !myflag2[k] ) {
								cities[mei][mej].soldiers_num--;
								myflag2[k] = 1;
							}
						}
					}
				}

			}
		
			
			soldier[k].x += MY_VEL * (dest.x - begin.x) / ( sqrt ( ( (dest.x - begin.x) * (dest.x - begin.x) ) + ( (dest.y - begin.y) * (dest.y - begin.y) ) ) );
			soldier[k].y += MY_VEL * (dest.y - begin.y) / ( sqrt ( ( (dest.x - begin.x) * (dest.x - begin.x) ) + ( (dest.y - begin.y) * (dest.y - begin.y) ) ) );

			// potion
			if( snow.flag == 2 ) 
            	MY_VEL = 0;


			if( abs( rocket.x - soldier[k].x ) < SOLDIER_R + 12 && abs( rocket.y - soldier[k].y ) < SOLDIER_R + 12 && rocketVisible
			&& rocket.flag != 1 ) {
				rocketVisible = 0;
				rocketOn = 1;
				rocket.flag = 1;
				MY_VEL = 6;
				navarx = 250;
			}

			else if( abs( snow.x - soldier[k].x ) < SOLDIER_R + 12 && abs( snow.y - soldier[k].y ) < SOLDIER_R + 12 && snowVisible
			&& snow.flag != 1 ) {
				snowVisible = 0;
				snowOn = 1;
				snow.flag = 1;
				navarx = 250;
			}

			else if( abs( ufo.x - soldier[k].x ) < SOLDIER_R + 12 && abs( ufo.y - soldier[k].y ) < SOLDIER_R + 12 && ufoVisible
			&& ufo.flag != 1 ) {
				ufoVisible = 0;
				ufoOn = 1;
				ufo.flag = 1;
				navarx = 250;
				INCREASE_RATE = 15;
			}

			else if( abs( inf.x - soldier[k].x ) < SOLDIER_R + 12 && abs( inf.y - soldier[k].y ) < SOLDIER_R + 12 && infVisible
			&& inf.flag != 1 ) {
				infVisible = 0;
				infOn = 1;
				inf.flag = 1;
				navarx = 250;
			}
			
			
			// hit
			for(int u = 0; u < temp2; u++) {
				if( abs( soldier[k].x - soldier2[u].x ) < SOLDIER_R + 1 && abs( soldier[k].y - soldier2[u].y ) < SOLDIER_R + 1 &&
				( ( begin2.x > dest2.x && soldier2[u].x > dest2.x ) || ( begin2.x < dest2.x && soldier2[u].x < dest2.x ) ) ) {
					if( !hitflag[k] ) {
						hitflag[k] = 1;
						hitcounter++;
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
			( hitcounter == temp ) ) {
				isSendingSoldiers = 0;
				hitcounter = 0;
            	// soldier[ temp - 1 ].x = 0; soldier[ temp - 1 ].y = 0;
				coordZeroer( 200 , soldier );
				// cities[mei][mej].isSendingSol = 0;
			}

			if( ( abs( soldier[k].x - soldier[k + 1].x ) <= 10 ) && ( abs( soldier[k].y - soldier[k + 1].y ) <= 10 ) ) {
				break;
			}


		}
	}
}


void rocketInit() {
	int tmpi1 = rand() % 3 , tmpj1 = rand() % n , tmpi2 , tmpj2;
	if( tmpi1 != 2 ) tmpi2 = tmpi1 + 1;
	else tmpi2 = tmpi1 - 1;
	tmpj2 = tmpj1;
	
	rocket.x = ( ( cities[tmpi1][tmpj1].x1 + cities[tmpi1][tmpj1].x2 ) / 2 + ( cities[tmpi2][tmpj2].x1 + cities[tmpi2][tmpj2].x2 ) / 2 ) / 2;
	rocket.y = ( ( cities[tmpi1][tmpj1].y1 + cities[tmpi1][tmpj1].y2 ) / 2 + ( cities[tmpi2][tmpj2].y1 + cities[tmpi2][tmpj2].y2 ) / 2 ) / 2;
}

void snowInit() {
	int tmpi1 = rand() % 3 , tmpj1 = rand() % n , tmpi2 , tmpj2;
	if( tmpi1 != 2 ) tmpi2 = tmpi1 + 1;
	else tmpi2 = tmpi1 - 1;
	tmpj2 = tmpj1;
	
	snow.x = ( ( cities[tmpi1][tmpj1].x1 + cities[tmpi1][tmpj1].x2 ) / 2 + ( cities[tmpi2][tmpj2].x1 + cities[tmpi2][tmpj2].x2 ) / 2 ) / 2;
	snow.y = ( ( cities[tmpi1][tmpj1].y1 + cities[tmpi1][tmpj1].y2 ) / 2 + ( cities[tmpi2][tmpj2].y1 + cities[tmpi2][tmpj2].y2 ) / 2 ) / 2;
}

void ufoInit() {
	int tmpi1 = rand() % 3 , tmpj1 = rand() % n , tmpi2 , tmpj2;
	if( tmpi1 != 2 ) tmpi2 = tmpi1 + 1;
	else tmpi2 = tmpi1 - 1;
	tmpj2 = tmpj1;
	
	ufo.x = ( ( cities[tmpi1][tmpj1].x1 + cities[tmpi1][tmpj1].x2 ) / 2 + ( cities[tmpi2][tmpj2].x1 + cities[tmpi2][tmpj2].x2 ) / 2 ) / 2;
	ufo.y = ( ( cities[tmpi1][tmpj1].y1 + cities[tmpi1][tmpj1].y2 ) / 2 + ( cities[tmpi2][tmpj2].y1 + cities[tmpi2][tmpj2].y2 ) / 2 ) / 2;
}

void infInit() {
	int tmpi1 = rand() % 3 , tmpj1 = rand() % n , tmpi2 , tmpj2;
	if( tmpi1 != 2 ) tmpi2 = tmpi1 + 1;
	else tmpi2 = tmpi1 - 1;
	tmpj2 = tmpj1;
	
	inf.x = ( ( cities[tmpi1][tmpj1].x1 + cities[tmpi1][tmpj1].x2 ) / 2 + ( cities[tmpi2][tmpj2].x1 + cities[tmpi2][tmpj2].x2 ) / 2 ) / 2;
	inf.y = ( ( cities[tmpi1][tmpj1].y1 + cities[tmpi1][tmpj1].y2 ) / 2 + ( cities[tmpi2][tmpj2].y1 + cities[tmpi2][tmpj2].y2 ) / 2 ) / 2;
}


void solNumIncreasing() {
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < n; j++) {
			if(cities[i][j].flag == 1 ) {
				if( inf.flag == 1 || cities[i][j].soldiers_num < COLOR_SOLDIERS_MAX_NUM ) {
					cities[i][j].soldiers_num ++;
				}
			}
		}
	}
}

void AIsolNumIncreasing() {
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < n; j++) {
			if(cities[i][j].flag == 2) {
				if( inf.flag == 2 || cities[i][j].soldiers_num < COLOR_SOLDIERS_MAX_NUM ) {
					cities[i][j].soldiers_num ++;
				}
			}
		}
	}
}

int checkTheEnd() {
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < n; j++) {
			if( cities[i][j].flag ) {
				for( int k = 0 ; k < 3; k++ ) {
					for( int u = 0; u < n; u++ ) {
						if( cities[i][j].flag != cities[k][u].flag && cities[k][u].flag != 0 ) {
							return 0;
						}
					}
				}
				return cities[i][j].flag;
			}
		}
	}			
	return 0;
}


void drawEndingBoxes( SDL_Renderer *rend ) {
	roundedBoxRGBA( rend , 200 , 350 , 500 , 440 , 10 , LIGHT_BLUE.r , LIGHT_BLUE.g , LIGHT_BLUE.b , LIGHT_BLUE.a );
	roundedBoxRGBA( rend , 600 , 350 , 800 , 440 , 10 , RED.r , RED.g , RED.b , RED.a );
}


void saveTheGame() {

	char filename[50] = {0};
	strcat( filename , "savings/" );
	strcat( filename , username );
	strcat( filename , ".txt" );
	// printf("%s" , filename);
	FILE *gameDetails = fopen ( filename , "w" );

	fprintf( gameDetails , "%d\n" , n );
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < n; j++) {
			fprintf( gameDetails , "%d %d %d %d %d %d %d\n" , cities[i][j].x1 , cities[i][j].x2 , cities[i][j].y1 ,
			cities[i][j].y2 , cities[i][j].flag , cities[i][j].soldiers_num , cities[i][j].number );
		}
	}
	fclose( gameDetails );
}


void updateScores() {
	int s;
	char name[50] , te[50];
	
	FILE *scores , *ftmp;
	scores = fopen( "scores.txt" , "r" );
	ftmp = fopen( "tmp.txt" , "w" );

	while( !feof( scores ) ) {
		
		strcpy( te , name );
		fscanf( scores , "%d %[^\n]s" , &s , name );
		// printf( "%d %s\n" , s , name );

		if( !strcmp( username , name ) ){
			if( end == 1 ) 
				s += 30;
			else 
				s -= 10;
		}
		
		if( strcmp( name , te ) )
			fprintf( ftmp , "%d %s\n" , s , name );
	}

	fclose( scores );
	fclose( ftmp );

	remove( "scores.txt" );
	rename( "tmp.txt" , "scores.txt" );

}


int initializingCities() {
	int n = 3 + diff;
	int color = 0xff000000;
	
	for(int i = 0; i < 3; i++) {
		cities[i][0].x1 = 40 + (rand() % 30);
		if(i != 0) cities[i][0].y1 = (rand() % 20) + 15 + cities[i - 1][0].y2;
		else cities[i][0].y1 = (rand() % 10) + 50;

		for(int j = 0; j < n; j++) {
			cities[i][j].x2 = cities[i][j].x1 + 150;
			cities[i][j].y2 = cities[i][j].y1 + 150;

			cities[i][j + 1].x1 = cities[i][j].x2 + (rand() % 20) + 270 - (n * 50);
			if(i != 0) cities[i][j + 1].y1 = cities[i - 1][j + 1].y2 + (rand() % 20) + 15;
			else cities[i][j + 1].y1 = (rand() % 10) + 50;

			cities[i][j].soldiers_num = 10;
			cities[i][j].flag = 0;
			if( gal == 3 )
				cities[i][j].number = ( rand() % 18 ) + 1;
			else if( gal == 2 ) 
				cities[i][j].number = ringedPlanets[ rand() % 9 ];
			else if( gal == 1 )
				cities[i][j].number = ringlessPlanets[ rand() % 9 ];


			planetsRect[i][j].x = cities[i][j].x1;
			planetsRect[i][j].y = cities[i][j].y1;

		}
	}

	mei = rand() % 3;
	mej = rand() % n;
	do {
		enemyi = rand() % 3;
		enemyj = rand() % n;
	} while( (enemyi == mei && enemyj == mej) );

	cities[mei][mej].flag = 1;
	cities[mei][mej].soldiers_num += 30;
	cities[enemyi][enemyj].flag = 2;
	cities[enemyi][enemyj].soldiers_num += 30;

	return n;
}

void printMap( SDL_Renderer* rend , int n ) {

	char planetsNames[18][20];
	int counter = 0;
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < n; j++) {
			
			if( cities[i][j].flag == 1 ) {
				sprintf( planetsNames[counter] , "planets/r%d.png" , cities[i][j].number );
				planetsTexture[counter] = IMG_LoadTexture( rend , planetsNames[counter] );
				SDL_QueryTexture( planetsTexture[counter] , NULL , NULL , &planetsRect[i][j].w , &planetsRect[i][j].h );
				SDL_RenderCopy( rend , planetsTexture[counter] , NULL , &planetsRect[i][j] );
			}

			else if( cities[i][j].flag == 2 ) {
				sprintf( planetsNames[counter] , "planets/y%d.png" , cities[i][j].number );
				planetsTexture[counter] = IMG_LoadTexture( rend , planetsNames[counter] );
				SDL_QueryTexture( planetsTexture[counter] , NULL , NULL , &planetsRect[i][j].w , &planetsRect[i][j].h );
				SDL_RenderCopy( rend , planetsTexture[counter] , NULL , &planetsRect[i][j] );
			}

			else {
				sprintf( planetsNames[counter] , "planets/bw%d.png" , cities[i][j].number );
				planetsTexture[counter] = IMG_LoadTexture( rend , planetsNames[counter] );
				SDL_QueryTexture( planetsTexture[counter] , NULL , NULL , &planetsRect[i][j].w , &planetsRect[i][j].h );
				SDL_RenderCopy( rend , planetsTexture[counter] , NULL , &planetsRect[i][j] );
			}

			counter++;
		}
	}

}



#endif