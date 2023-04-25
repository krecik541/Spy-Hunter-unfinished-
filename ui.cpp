#include<iostream>
#include<stdio.h>
#include<string.h>
#include"game.h"
#include"draw.h"
#include"player.h"
#include"ui.h"

void uiUpdate(SDL_Texture** scrtex, SDL_Surface* charset, SDL_Surface** screen, Colors colors, double time, double result, int life, int* isPlaying)
{
	char text[BUFFER];
	DrawRectangle(*screen, 0, 0, SCREEN_WIDTH, 4, colors.pomaranczowy, colors.pomaranczowy);
	DrawRectangle(*screen, 0, 4, SCREEN_WIDTH, 40, colors.niebieski, colors.niebieski);
	DrawRectangle(*screen, 0, 44, SCREEN_WIDTH, 6, colors.pomaranczowy, colors.pomaranczowy);
	
	DrawRectangle(*screen, 0, SCREEN_HEIGHT-32, SCREEN_WIDTH, 6, colors.pomaranczowy, colors.pomaranczowy);
	DrawRectangle(*screen, 0, SCREEN_HEIGHT-26, SCREEN_WIDTH, 26, colors.niebieski, colors.niebieski);
	
	if (int(TIME_IMMORTALITY - ceil(time)) >= 0)
	{
		sprintf_s(text, "%d s", int(TIME_IMMORTALITY - ceil(time)));
		DrawString(*screen, (*screen)->w / 2 - strlen(text) * 8 / 2, 20, text, charset);
	}
	else
	{
		sprintf_s(text, "%d x", life);
		DrawString(*screen, (*screen)->w / 2 - strlen(text) * 8 / 2, 20, text, charset);
		DrawHeart(colors.czerwony, screen, (*screen)->w / 2 - strlen(text) * 8 / 2 + 36, 24);
	}
	
	sprintf_s(text, "Implementet elements: a, b, c, d, e, f, h, i, m, o");
	DrawString(*screen, 0, SCREEN_HEIGHT - 17, text, charset);
	
	sprintf_s(text, "Spy Hunter | Maciej Szymczak 193456");
	DrawString(*screen, 4, 6, text, charset);

	int wyn = ceil(result);
	sprintf_s(text, "%d", wyn);
	DrawString(*screen, 50, 20, text, charset);

	SDL_UpdateTexture(*scrtex, NULL, (*screen)->pixels, (*screen)->pitch);
}

void uiRender(SDL_Renderer* renderer, SDL_Texture* scrtex)
{
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
}
