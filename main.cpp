#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include"draw.h"
#include"game.h"
#include"map.h"
#include"player.h"
#include"ui.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

using namespace std;

int update(Game game, SDL_Rect* destination, Map* mapa, Colors colors, SDL_Surface* screen, int life);

int main(int argc, char** argv) 
{
	Game game = {nullptr, nullptr, nullptr, nullptr, false};
	Map mapa = {nullptr, 0, START_ROAD_WIDTH, START_ROAD_WIDTH, 0, 0, 0, 0, PLAYER_SPEED};
	Player player = { nullptr, NULL, 1, NEW_LIFE, 0 };
	SDL_Surface* screen = nullptr;

	game = init(game, &screen, &player);
	Colors colors = createColors(screen);

	unsigned int frameStart, frames = 0;
	double delta = 0, generatingTime = 0, pauzaTime = 0;

	mapa.map = new bool* [MAP_HEIGHT];
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		mapa.map[i] = new bool[MAP_WIDTH];
		for (int j = 0; j < MAP_WIDTH; j++)
			mapa.map[i][j] = false;
	}
	mapGenerateStart(mapa.map);

	countingDown(game.renderer);

	while (game.isPlaying != QUIT)
	{
		frameStart = SDL_GetTicks() - ANIMATION_TIME - pauzaTime;
		double temp_time = (frameStart - frames) * 0.001;
		mapa.time += temp_time;

		if (delta >= 1)
		{
			delta = 0;
			mapa.result += 75 * mapa.speed;
			if (mapa.time <= TIME_IMMORTALITY)
				player.iniResult += 75 * mapa.speed;
		}
		else
			delta += temp_time;

		if (mapa.isGenerating == 2)
			mapa.isGenerating = generating(&generatingTime, temp_time);
		if (game.isPlaying == CRASH)
		{
			if (mapa.time < TIME_IMMORTALITY)
				game.isPlaying = PLAYING;
			else 
			{
				player.life--;
				if (player.life < 0)
					saveResult(mapa.result, mapa.time, game.renderer, colors.czarny, game.charset, &(game.isPlaying));// funkcja końca gry
				else
					game.isPlaying = PLAYING;
			}
			playerRespawn(game.renderer, &player);
		}
		if (game.isPlaying == NEW)
		{
			newGame(&player, &delta, &generatingTime, &(game.isPlaying));
			mapa = { mapa.map, 0, START_ROAD_WIDTH, START_ROAD_WIDTH, 0, 0, 0, 0, PLAYER_SPEED };
			player.life = 1;
			player.newLifeCap = NEW_LIFE;
			game.isPlaying = PLAYING;
			player.iniResult = 0;
		}
		if (game.isPlaying == PAUSE)
			pause(game.renderer, &(game.isPlaying), colors.czarny, game.charset);
		if (game.isPlaying == END)
			saveResult(mapa.result, mapa.time, game.renderer, colors.czarny, game.charset, &(game.isPlaying));// funkcja końca gry, podliczanie i wyświetlanie punktów

		getLife(mapa.result - player.iniResult, &player, mapa.time);

		game.isPlaying = handleEvents(&(mapa.ruch), &(mapa.speed), game.isPlaying);

		game.isPlaying = update(game, &(player.destination), &mapa, colors, screen, player.life);
		render(game.renderer, player, game);

		frames = SDL_GetTicks() - ANIMATION_TIME - pauzaTime;
		FPScap(frames - frameStart, mapa.speed);
	}

	clean(game, screen, player, mapa.map);
	return 0;
}


int update(Game game, SDL_Rect* destination, Map* mapa, Colors colors, SDL_Surface* screen, int life)
{
	mapUpdate(mapa, &(game.scrtex), &screen, colors);
	uiUpdate(&(game.scrtex), game.charset, &screen, colors, mapa->time, mapa->result, life, &(game.isPlaying));
	playerUpdate(mapa->ruch, destination, mapa->map, &(game.isPlaying));
	SDL_RenderCopy(game.renderer, game.scrtex, NULL, NULL);
	return game.isPlaying;
}
