#pragma once
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include"draw.h"
#include"game.h"
#include"map.h"
#include"player.h"
#include"ui.h"

#define SQUARE 16 // MAP IS DIVIDED INTO SQUARE X x X px
#define MAP_HEIGHT SCREEN_HEIGHT/SQUARE // MAP HEIGHT IN SQUARE 
#define MAP_WIDTH SCREEN_WIDTH/SQUARE // MAP WIDTH IN SQUARE 

#define MAX_ROAD_WIDTH 30//MAX WIDTH OF THE ROAD
#define MIN_ROAD_WIDTH 10//MIN WIDTH OF THE ROAD
#define START_ROAD_WIDTH 20//MIN WIDTH OF THE ROAD

#define CHANGE 15// ROAD CHANGES ITS WIDTH EVERY x SQUARE (mniej wiêcej)

struct Map {
	bool** map;// false - road, true - grass
	int ruch;
	int width;
	int now_width;
	int now_height;
	int isGenerating;// 0 - not generating, 1 - generates, 2 - cooldown
	double time;
	double result;
	double speed;
};


// update maps
void mapUpdate(Map* mapa, SDL_Texture** scrtex, SDL_Surface** screen, Colors colors);

// render map
void mapRender(SDL_Renderer* renderer, SDL_Texture* scrtex);

// generate map
void mapGenerate(Map* mapa);

// 
void mapGenerateStart(bool** map);

// 
int generating(double* generatingTime, double temp_time);