#pragma once
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

struct Colors {
	int czarny;
	int zielony;
	int czerwony;
	int niebieski;
	int pomaranczowy;
};

// narysowanie napisu txt na powierzchni screen, zaczynając od punktu (x, y)
// charset to bitmapa 128x128 zawierająca znaki
void DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset);

// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt środka obrazka sprite na ekranie
void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y);

// rysowanie pojedynczego pixela
void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color);

// rysowanie linii o długoœci l w pionie (gdy dx = 0, dy = 1) 
// bądź poziomie (gdy dx = 1, dy = 0)
void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);

// rysowanie prostokąta o długości boków l i k
void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor);


// load texture
SDL_Texture* loadTexture(const char* fileName, SDL_Renderer* renderer, int* isPlaying);


// create colors
Colors createColors(SDL_Surface* screen);


// draw square SQUARE x SQUARE (SQUARE - MAP IS DIVIDED INTO SQUARE X x X px)
void DrawMapPart(int color, SDL_Surface** screen, int posX, int posY);

// draw heart
void DrawHeart(int color, SDL_Surface** screen, int posX, int posY);