#pragma once
#include<iostream>
#include"draw.h"
#include"map.h"
#include"game.h"

using namespace std;

void DrawString(SDL_Surface* screen, int x, int y, const char* text, SDL_Surface* charset)
{
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while (*text) 
	{
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
	}
}


void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y) 
{
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
}


void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) 
{
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
}


void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) 
{
	for (int i = 0; i < l; i++) 
	{
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	}
}


void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k, Uint32 outlineColor, Uint32 fillColor)
{
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
}


SDL_Texture* loadTexture(const char* fileName, SDL_Renderer* renderer, int* isPlaying)
{
	SDL_Surface* surface;

	surface = SDL_LoadBMP(fileName);
	if (surface == NULL)
	{
		printf("SDL_LoadBMP(%s", fileName, ") error: %s\n", SDL_GetError());
		*isPlaying = QUIT;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	return texture;
}


Colors createColors(SDL_Surface* screen)
{
	Colors colors;
	colors.czerwony = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	colors.czarny = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	colors.zielony = SDL_MapRGB(screen->format, 0x04, 0x73, 0x0B);
	colors.niebieski = SDL_MapRGB(screen->format, 0x05, 0x05, 0x82);
	colors.pomaranczowy = SDL_MapRGB(screen->format, 0xFF, 0x98, 0x2C);
	return colors;
}


void DrawMapPart(int color, SDL_Surface** screen, int posX, int posY)
{
	DrawRectangle(*screen, posX, posY, SQUARE, SQUARE, color, color);
}


void DrawHeart(int color, SDL_Surface** screen, int posX, int posY)
{
	DrawPixel(*screen, posX - 2, posY - 3, color);
	DrawPixel(*screen, posX + 2, posY - 3, color);
	DrawLine(*screen, posX - 3, posY - 2, 3, 1, 0, color);
	DrawLine(*screen, posX + 1, posY - 2, 3, 1, 0, color);
	DrawLine(*screen, posX - 4, posY - 1, 9, 1, 0, color);
	DrawLine(*screen, posX - 3, posY, 7, 1, 0, color);
	DrawLine(*screen, posX - 2, posY + 1, 5, 1, 0, color);
	DrawLine(*screen, posX - 1, posY + 2, 3, 1, 0, color);
	DrawPixel(*screen, posX, posY + 3, color);
}