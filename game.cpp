#define _CRT_SECURE_NO_WARNINGS
#include<math.h>
#include<stdio.h>
#include<ctime>
#include<string.h>
#include<iostream>
#include<string>
#include<fstream>
#include"draw.h"
#include"game.h"
#include"map.h"
#include"player.h"
#include"ui.h"


using namespace std;


Game init(Game game, SDL_Surface** screen, Player* player)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		printf("SDL_Init error: %s\n", SDL_GetError());
		game.isPlaying = QUIT;
		return game;
	}
	
	if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, FULLSCREEN_MODE, &(game.window), &(game.renderer)) != 0)
	{
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		game.isPlaying = QUIT;
		return game;
	}

	SDL_SetRenderDrawColor(game.renderer, 255, 255, 255, 255);

	*screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	game.scrtex = SDL_CreateTexture(game.renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

	game.isPlaying = PLAYING;

	game.charset = SDL_LoadBMP("./Bitmaps/cs8x8.bmp");
	if (game.charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		game.isPlaying = QUIT;
	}
	SDL_SetColorKey(game.charset, true, 0x000000);

	player->playerTexture = loadTexture("./Bitmaps/player.bmp", game.renderer, &(game.isPlaying));
	player->destination.h = PLAYER_HEIGHT;
	player->destination.w = PLAYER_WIDTH;
	player->destination.y = PLAYER_START_Y;
	player->destination.x = PLAYER_START_X;

	SDL_ShowCursor(SDL_DISABLE);

	return game;
}


int handleEvents(int* ruch, double* speed, int isPlaying)
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		return QUIT;
		break;
	case SDL_KEYUP:
		*ruch = NO_MOVE;
		*speed = PLAYER_SPEED;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
			return QUIT;
		else if (event.key.keysym.sym == SDLK_UP)
		{
			if (*speed == 1)
				*speed = PLAYER_ACC1;
			else if (*speed == PLAYER_ACC1)
				*speed = PLAYER_ACC2;
		}
		else if (event.key.keysym.sym == SDLK_DOWN)
		{
			if (*speed == 1)
				*speed = PLAYER_RET1;
			else if (*speed == PLAYER_RET1)
				*speed = PLAYER_RET2;
		}
		else if (event.key.keysym.sym == SDLK_LEFT)
			*ruch = MOVEMENT_LEFT;
		else if (event.key.keysym.sym == SDLK_RIGHT)
			*ruch = MOVEMENT_RIGHT;
		else if (event.key.keysym.sym == SDLK_n)
			return NEW;
		else if (event.key.keysym.sym == SDLK_p)
			return PAUSE;
		else if (event.key.keysym.sym == SDLK_f)
			return END;
		break;

	default:
		break;
	}
	return isPlaying;
}


void render(SDL_Renderer* renderer, Player player, Game game)
{
	SDL_RenderClear(renderer);
	mapRender(renderer, game.scrtex);
	uiRender(renderer, game.scrtex);
	playerRender(renderer, player);
	SDL_RenderPresent(renderer);
}


void clean(Game game, SDL_Surface* screen, Player player, bool** map)
{
	SDL_FreeSurface(game.charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(player.playerTexture);
	SDL_DestroyRenderer(game.renderer);
	SDL_DestroyTexture(game.scrtex);
	SDL_DestroyWindow(game.window);
	SDL_Quit();
	for (int i = 0; i < MAP_HEIGHT; i++)
		delete[] map[i];

	delete[] map;
}


void FPScap(int frameTime, double speed)
{
	if (frameTime < FRAME_DELAY)
	{
		SDL_Delay((FRAME_DELAY - frameTime) / speed);
	}
}


void countingDown(SDL_Renderer* renderer)
{
	counting(renderer, "./Bitmaps/3.bmp");
	counting(renderer, "./Bitmaps/2.bmp");
	counting(renderer, "./Bitmaps/1.bmp");
	counting(renderer, "./Bitmaps/0.bmp");
}


void counting(SDL_Renderer* renderer, const char* name)
{
	SDL_Rect dstrect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	int t = PLAYING;
	SDL_Texture* F = loadTexture(name, renderer, &t);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, F, NULL, &dstrect);
	SDL_RenderPresent(renderer);
	SDL_Delay(ANIMATION_TIME_FRAME);
	SDL_DestroyTexture(F);
}


void newGame(Player* player, double* delta, double* generatingTime, int* isPlaying)
{
	player->destination.y = PLAYER_START_Y;
	player->destination.x = PLAYER_START_X;
	*delta = 0;
	*generatingTime = 0;
	*isPlaying = PLAYING;
}


double pause(SDL_Renderer* renderer, int* isPlaying, int color, SDL_Surface* charset)
{
	int start = SDL_GetTicks(); 
	bool t = true;
	SDL_RenderClear(renderer);
	SDL_Surface * screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	for (int i = 0; i < MAP_HEIGHT; i++)
		for (int j = 0; j < MAP_WIDTH; j++)
			DrawMapPart(color, &screen, j * SQUARE, i * SQUARE);
	SDL_Texture*tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
	DrawString(screen, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, "PRESS 'P' OR 'ESC' TO CONTINUE", charset);
	SDL_UpdateTexture(tex, NULL, screen->pixels, screen->pitch);
	SDL_RenderCopy(renderer, tex, NULL, NULL);
	SDL_RenderPresent(renderer);
	SDL_Event event;
	while (t)
	{	
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			*isPlaying = QUIT;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				*isPlaying = PLAYING;
				t = false;
			}
			else if (event.key.keysym.sym == SDLK_n)
			{
				*isPlaying = NEW;
				t = false;
			}
			else if (event.key.keysym.sym == SDLK_p)
			{
				*isPlaying = PLAYING;
				t = false;
			}
			else if (event.key.keysym.sym == SDLK_f)
			{
				*isPlaying = END;
				t = false;
			}
			break;
		default:
			break;
		}
	}
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(tex);
	return SDL_GetTicks() - start;
}


void saveResult(int result, double time, SDL_Renderer* renderer, int color, SDL_Surface* charset, int* isPlaying)
{
	fstream plik;
	int i = 0, len = 0;
	double **t;
	plik.open("./Bitmaps/resultSAVE.txt", ios::out | ios::in);
	if (plik.good())
	{
		plik.seekg(0, ios::end);
		if (plik.tellg() != 0)
		{
			plik.seekg(0, ios::beg);
			plik >> len;
			plik.seekp(0, ios::beg);
			plik << ++len << endl;
			plik.seekp(0, ios::end);
			plik << result << " " << time << endl;
		}
		else
		{
			plik << ++len << endl;
			plik << result << " " << time << endl;
		}

		plik.seekg(0, ios::beg);
		
		plik >> i;
		t = new double* [len];
		for (int i = 0; i < len; i++)
		{
			t[i] = new double[2];
			plik >> t[i][0] >> t[i][1];
		}

		plik.close();
	}
	else
	{
		FILE* plik = fopen("./Bitmaps/resultSAVE.txt", "w");
		fprintf(plik, "%d\n", ++len);
		fprintf(plik, "%d ", result);
		fprintf(plik, "%f\n", time);
		fclose(plik);
		t = new double* [len];
		t[0] = new double[2];
		t[0][0] = result;
		t[0][1] = time;
	}
	
	DrawTable(t, renderer, color, charset, isPlaying, len);
}


void DrawTable(double** t, SDL_Renderer* renderer, int color, SDL_Surface* charset, int* isPlaying, int size)
{
	bool q = true, time = true;
	SDL_Event event;
	int skip = 0;
	const int limit = 5;
	sorting(t, false, size);
	while (q)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
		{
			*isPlaying = QUIT;
			q = false;
			break;
		}
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				*isPlaying = QUIT;
				q = false;
			}
			else if (event.key.keysym.sym == SDLK_n)
			{
				*isPlaying = NEW;
				q = false;
			}
			else if (event.key.keysym.sym == SDLK_UP)
			{
				SDL_Delay(300);
				if ((skip - 1) * limit >= 0)
					skip--;
			}
			else if (event.key.keysym.sym == SDLK_DOWN)
			{
				SDL_Delay(300);
				if ((skip + 1) * limit < size)
					skip++;
			}
			else if (event.key.keysym.sym == SDLK_t)
				sorting(t, true, size);
			else if (event.key.keysym.sym == SDLK_p)
				sorting(t, false, size);
			break;
		default:
			break;
		}
		if (limit * skip + limit <= size)
			DrawTablePart(t, renderer, color, charset, skip * limit, limit);
		else 
			DrawTablePart(t, renderer, color, charset, skip * limit, size - skip * limit);
	}
}


void DrawTablePart(double** t, SDL_Renderer* renderer, int color, SDL_Surface* charset, int skip, int limit)
{
	char text[BUFFER];
	SDL_RenderClear(renderer);
	SDL_Surface* screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	for (int i = 0; i < MAP_HEIGHT; i++)
		for (int j = 0; j < MAP_WIDTH; j++)
			DrawMapPart(color, &screen, j * SQUARE, i * SQUARE);

	sprintf_s(text, "PRESS 'N' TO START A NEW GAME");
	DrawString(screen, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4, text, charset);
	sprintf_s(text, "PRESS 'ESC' TO ESCAPE");
	DrawString(screen, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 16, text, charset);
	sprintf_s(text, "PRESS '\030' TO SCROLL UP");
	DrawString(screen, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 32, text, charset);
	sprintf_s(text, "PRESS '\031' TO SCROLL DOWN");
	DrawString(screen, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 + 48, text, charset);

	sprintf_s(text, "    Result \t Time");
	DrawString(screen, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 16, text, charset);
	for (int i = skip; i < skip + limit; i++)
	{
		sprintf_s(text, "%d    %d \t %f", i + 1, (int)(t[i][0]), t[i][1]);
		DrawString(screen, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + (i - skip) * 16, text, charset);
	}

	SDL_Texture* tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_UpdateTexture(tex, NULL, screen->pixels, screen->pitch);
	SDL_RenderCopy(renderer, tex, NULL, NULL);
	SDL_RenderPresent(renderer);

	SDL_FreeSurface(screen);
	SDL_DestroyTexture(tex);
}


void sorting(double** t, bool time, int size)
{
	int p = 0;
	if (time)
		p = 1;
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size - 1; j++)
			if (t[j][p] < t[j + 1][p])
			{
				swap(t[j][p], t[j + 1][p]);
				swap(t[j][(p + 1) % 2], t[j + 1][(p + 1)%2]);
			}
			else if (t[j][p] == t[j + 1][p] && t[j][(p + 1) % 2] > t[j + 1][(p + 1) % 2])
			{
				swap(t[j][p], t[j + 1][p]);
				swap(t[j][(p + 1) % 2], t[j + 1][(p + 1) % 2]);
			}
}
