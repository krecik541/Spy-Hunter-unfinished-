#pragma once
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include"draw.h"
#include"game.h"
#include"map.h"
#include"player.h"
#include"ui.h"

#define ESC 27// ASCII CODE - ESCAPE

#define SCREEN_WIDTH	640//SCREEN WIDTH
#define SCREEN_HEIGHT	480//SCREEN HEIGHT
#define FULLSCREEN_MODE 0 //IF EQUALS 0 -> FULLSCREEN MODE IS OFF
//SDL_WINDOW_FULLSCREEN_DESKTOP

#define FPS 60 //LIMIT OF FPS
#define FRAME_DELAY (1000 / FPS)//TIME BETWEEN EACH FRAME

#define ANIMATION_TIME_FRAME 1000// TIME OF COUNTING DOWN
#define ANIMATION_TIME 4 * ANIMATION_TIME_FRAME// TIME OF COUNTING DOWN

#define QUIT 0 
#define PLAYING 1 
#define CRASH 2 
#define NEW 3 
#define PAUSE 4 
#define END 5 
#define SAVE 6
#define LOAD 7

struct Game {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Surface* charset;
	SDL_Texture* scrtex;
	int isPlaying;// 0 - QUIT, 1 - PLAYING, 2 - CRASH, 3 - NEW GAME, 4 - PAUSE GAME, 5 - END THE GAME, 6 - SAVE, 7 - LOAD
	//screen
};


// initialaizing SDL 
Game init(Game game, SDL_Surface** screen, Player* player);

// handle ongoing events
int handleEvents(int* ruch, double* speed, int isPlaying);

// updates everything
//bool update(Game game, SDL_Rect* destination, Map* mapa, Colors colors, SDL_Surface* screen);


// renders everything
void render(SDL_Renderer* renderer, Player player, Game game);

// clean memory
void clean(Game game, SDL_Surface* screen, Player player, bool** map);

// limits the number of FPS
void FPScap(int frameTime, double speed);

// shows the counter
void countingDown(SDL_Renderer* renderer);
void counting(SDL_Renderer* renderer, const char* name);

// clear all data
void newGame(Player* player, double* delta, double* generatingTime, int* isPlaying);

// pause the game
double pause(SDL_Renderer* renderer, int* isPlaying, int color, SDL_Surface* charset);

// shows result 
void saveResult(int result, double time, SDL_Renderer* renderer, int color, SDL_Surface* charset, int* isPlaying);
void DrawTable(double** t, SDL_Renderer* renderer, int color, SDL_Surface* charset, int* isPlaying, int size);
void DrawTablePart(double** t, SDL_Renderer* renderer, int color, SDL_Surface* charset, int skip, int limit);

// sorting result table
void sorting(double** t, bool time, int size);
