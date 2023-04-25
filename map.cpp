#include<iostream>
#include"game.h"
#include"draw.h"
#include"map.h"
#include <stdlib.h>
#include <time.h>   

using namespace std;

void mapUpdate(Map* mapa, SDL_Texture** scrtex, SDL_Surface** screen, Colors colors)
{
	mapGenerate(mapa);
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (mapa->map[i][j])
			{
				DrawMapPart(colors.zielony, screen, j * SQUARE, i * SQUARE);
			}
			else
				DrawMapPart(colors.czarny, screen, j * SQUARE, i * SQUARE);
		}
	}

	SDL_UpdateTexture(*scrtex, NULL, (*screen)->pixels, (*screen)->pitch);
}

void mapRender(SDL_Renderer* renderer, SDL_Texture* scrtex)
{
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
}

void mapGenerate(Map* mapa)
{
	if (mapa->isGenerating == 0)
	{
		mapa->isGenerating = 1;
		srand(time(NULL));
		while(1)
		{
			mapa->width = rand() % (MAX_ROAD_WIDTH - MIN_ROAD_WIDTH) + MIN_ROAD_WIDTH;
			if (mapa->width % 2 == 0)
				break;
		}
	}

	for (int i = MAP_HEIGHT - 1; i > 0; i--)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			mapa->map[i][j] = mapa->map[i - 1][j];
		}
	}


	if(mapa->now_height % CHANGE != 0)
	{
		if (mapa->now_width == mapa->width)
			mapa->isGenerating = 2;
		else if (mapa->now_width > mapa->width)
			(mapa->now_width) -= 1;
		else
			(mapa->now_width) += 1;
		
		(mapa->now_height) = 0;

		for (int i = 0; i < MAP_WIDTH; i++)
		{
			if (i < (ceil)((MAP_WIDTH - (mapa->now_width)) / 2.0) || i >= (floor)((MAP_WIDTH + (mapa->now_width)) / 2.0))
				mapa->map[0][i] = true;
			else
				mapa->map[0][i] = false;
		}
	}
	else
	{
		(mapa->now_height)++;
	}
}

void mapGenerateStart(bool** map)
{
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		if (i < (MAP_WIDTH - START_ROAD_WIDTH)/2 || i >= (MAP_WIDTH + START_ROAD_WIDTH) / 2)
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			map[j][i] = true;
		}
	}
}

int generating(double* generatingTime, double temp_time)
{
	*generatingTime += temp_time;
	if (*generatingTime >= 1)
	{
		*generatingTime = 0;
		return 0;
	}
	return 2;
}