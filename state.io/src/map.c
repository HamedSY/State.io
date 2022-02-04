#ifndef __MAP_C__
#define __MAP_C__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef struct City {
	int x1;
	int x2;
	int y1;
	int y2;
	int theta;
	int flag;
	int soldiers_num;
} City;

typedef struct Coordination {
	double x;
	double y;
} Coordination;

const int SCREEN_WIDTH = 600 , SCREEN_HEIGHT = 600;
const int FPS = 60;
const int CENTER_R = 15 , SOLDIER_R = 3;
const int COLOR_SOLDIERS_MAX_NUM = 60;
const int ORDINARY_SOLDIERS_MAX_NUM = 10;

SDL_Color WHITE = { 0 , 0 , 0 , 255 };

int mei , mej , enemyi , enemyj;
int mouseOnMe = 0 , isSendingSoldiers = 0;
int n;
char solNumStr[10] = {0};

City cities[4][6];

Coordination begin , dest;
Coordination mouse , soldier[100];
Coordination tmp = {0};


int initializingCities();
void print2DCity( int a , int b , City arr[a][b] );
void printMap( SDL_Renderer* rend , int n );
void sendingSoldiers( SDL_Renderer *rend );
void solNumIncreasing();


void sendingSoldiers( SDL_Renderer *rend ) {
	int flag = 0 , i , j;
	if(!flag)
		for(i = 0; i < 4; i++) {
			for(j = 0; j < n; j++) {
				if( dest.x <= cities[i][j].x2 && dest.x >= cities[i][j].x1 &&
				dest.y <= cities[i][j].y2 && dest.y >= cities[i][j].y1 ) {
					dest.x = (cities[i][j].x1 + cities[i][j].x2) / 2;
					dest.y = (cities[i][j].y1 + cities[i][j].y2) / 2;
					// printf("%d %d\n" , i , j);
					flag = 1;
					break;
				}
			}
			if(flag) break;
		}

	if(flag){
		for(int k = 0; k < cities[mei][mej].soldiers_num && k < 100; k++) {

			filledCircleColor( rend , soldier[k].x , soldier[k].y , SOLDIER_R , 0xffffffff );
			soldier[k].x += 4 * (dest.x - begin.x) / ( sqrt ( ( (dest.x - begin.x) * (dest.x - begin.x) ) + ( (dest.y - begin.y) * (dest.y - begin.y) ) ) );
			soldier[k].y += 4 * (dest.y - begin.y) / ( sqrt ( ( (dest.x - begin.x) * (dest.x - begin.x) ) + ( (dest.y - begin.y) * (dest.y - begin.y) ) ) );
			if( abs(soldier[k].x - dest.x) <= 10 && abs(soldier[k].y - dest.y) <= 10 ) {
				isSendingSoldiers = 0;
				if(cities[i][j].flag == 1) {
					if(cities[i][j].soldiers_num + cities[mei][mej].soldiers_num <= 60)
						cities[i][j].soldiers_num += cities[mei][mej].soldiers_num;	
					cities[mei][mej].soldiers_num = 0;
				}
				else {
					cities[i][j].soldiers_num -= cities[mei][mej].soldiers_num;
					cities[mei][mej].soldiers_num = 0;
					if(cities[i][j].soldiers_num < 0) {
						cities[i][j].soldiers_num = -cities[i][j].soldiers_num;
						cities[i][j].flag = 1;
					}
				}
			}

		}
	}
}

void solNumIncreasing() {
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < n; j++) {
			if(cities[i][j].flag == 0) {
				if(cities[i][j].soldiers_num < ORDINARY_SOLDIERS_MAX_NUM) {
					cities[i][j].soldiers_num++;
				}
			}
			else {
				if(cities[i][j].soldiers_num < COLOR_SOLDIERS_MAX_NUM) {
					cities[i][j].soldiers_num++;
				}
			}
		}
	}
}

int initializingCities() {
	int length[6] = {0} , width[4][6] = {0} , theta , n = 3 + (rand() % 2);
	int color = 0xff000000;
	
	for(int i = 0; i < 4; i++) {
		cities[i][0].x1 = 40 + (rand() % 30);
		if(i != 0) cities[i][0].y1 = (rand() % 20) + 30 + cities[i - 1][0].y2;
		else cities[i][0].y1 = (rand() % 30) + 40;

		for(int j = 0; j < n; j++) {
			theta = (rand() % 10) + 5;
			if(i == 0) length[j] = (rand() % 50) + 70 - (n * 3);
			width[i][j] = (rand() % 50) + 50;
			cities[i][j].x2 = cities[i][j].x1 + length[j];
			cities[i][j].y2 = cities[i][j].y1 + width[i][j];
			cities[i][j].theta = theta;

			cities[i][j + 1].x1 = cities[i][j].x2 + (rand() % 20) + 30;
			if(i != 0) cities[i][j + 1].y1 = cities[i - 1][j + 1].y2 + (rand() % 20) + 30;
			else cities[i][j + 1].y1 = (rand() % 30) + 40;

			cities[i][j].soldiers_num = 0;

		}
	}

	mei = rand() % 4;
	mej = rand() % n;
	do {
		enemyi = rand() % 4;
		enemyj = rand() % n;
	} while( (enemyi == mei && enemyj == mej) );

	cities[mei][mej].flag = 1;
	cities[enemyi][enemyj].flag = 1;
	cities[mei][mej].soldiers_num += 10;
	cities[enemyi][enemyj].soldiers_num += 10;

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