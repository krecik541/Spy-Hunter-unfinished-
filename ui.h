#pragma once
#define _USE_MATH_DEFINES
#include<iostream>
#include"game.h"
#include"draw.h"

#define BUFFER 128
#define TIME_IMMORTALITY 10


// update ui
void uiUpdate(SDL_Texture** scrtex, SDL_Surface* charset, SDL_Surface** screen, Colors colors, double time, double result, int life, int* isPlaying);

// render ui
void uiRender(SDL_Renderer* renderer, SDL_Texture* scrtex);

