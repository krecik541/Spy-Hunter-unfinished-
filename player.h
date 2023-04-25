#pragma once
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include"draw.h"
#include"game.h"

#define PLAYER_WIDTH 27//PLAYER WIDTH
#define PLAYER_HEIGHT 51//PLAYER HEIGHT
#define PLAYER_START_X 311//PLAYER START X POSITION
#define PLAYER_START_Y 319//PLAYER START Y POSITION

#define NO_MOVE 0
#define MOVEMENT_LEFT -1
#define MOVEMENT_RIGHT 1

#define PLAYER_SPEED 1 //BASIC PLAYER SPEED
#define PLAYER_ACC1 2 //ACCELERATION 1 - PLAYER SPEED
#define PLAYER_ACC2 3 //ACCELERATION 2 - PLAYER SPEED
#define PLAYER_RET1 0.8 //RETARDATION 1 - PLAYER SPEED
#define PLAYER_RET2 0.5 //RETARDATION 2 - PLAYER SPEED

#define NEW_LIFE 1000//AMOUNT OF POINTS NEEDED TO SCORE NEW LIFE

struct Player {
	SDL_Texture* playerTexture;
	SDL_Rect destination;
	int life;
	int newLifeCap;
	int iniResult;
};

// update player
void playerUpdate(int ruch, SDL_Rect *destination, bool** map, int* isPlaying);

// render player
void playerRender(SDL_Renderer* renderer, Player player);

// respawn player
void playerRespawn(SDL_Renderer* renderer, Player* player);

// get new life 
void getLife(int result, Player* player, double time);