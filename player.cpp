#include<iostream>
#include"game.h"
#include"draw.h"
#include"player.h"
#include"map.h"



void playerUpdate(int ruch, SDL_Rect* destination, bool** map, int* isPlaying)
{
	destination->x += ruch * 7;
	int x = destination->x;//20
	int i = 0;
	for (; i < MAP_WIDTH; i++)
		if (map[20][i] == false)
			break;

	if ((i - 1) * SQUARE > x || (MAP_WIDTH - i - 1) * SQUARE < x)
		*isPlaying = CRASH;
}


void playerRender(SDL_Renderer* renderer, Player player)
{
	SDL_RenderCopy(renderer, player.playerTexture, NULL, &(player.destination));
}


void playerRespawn(SDL_Renderer* renderer, Player* player)
{
	player->destination.x = PLAYER_START_X;
	SDL_Delay(500);
}


void getLife(int result, Player* player, double time)
{
	if (time > TIME_IMMORTALITY && result >= player->newLifeCap)
	{
		player->newLifeCap += NEW_LIFE;
		player->life++;
	}
}