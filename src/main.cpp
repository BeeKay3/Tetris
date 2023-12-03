#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "../headers/GetTexture.h"
#include "../headers/Tetromino.h"
#include "../headers/board.h"
using namespace std;

const int SCREENWIDTH = 1920, SCREENHEIGHT = 1080, BLOCKSIZE = 50;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool INIT()
{
	bool Key = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL could not be initialized, error : " << SDL_GetError() << endl;
		Key = false;
	}
	else
	{
		window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
		if (window == NULL)
		{
			cout << "Window could not be created, error : " << SDL_GetError() << endl;
			Key = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				cout << "Renderer could not be intialized, error : " << SDL_GetError() << endl;
				Key = false;
			}
			if (!IMG_Init(IMG_INIT_PNG))
			{
				cout << "SDL_image could not be intialized, error : " << IMG_GetError() << endl;
				Key = false;
			}
		}
	}
	return Key;
}

void CLOSE()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
	SDL_Quit();
}

int main(int argc, char *args[])
{
	if (INIT())
	{

		SDL_Event e;
		bool quit = false;
		Uint64 currentTicks;
		SDL_Texture *BASETILE = GetTexture(renderer, "assets/img/block.png");
		SDL_Point pos = {910, 40};
		shape randomShape;

		Board b(renderer, BLOCKSIZE);
		tetromino t(renderer, BLOCKSIZE, BASETILE);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		t.Update(pos, t.random());

		while (quit == false)
		{
			while (SDL_PollEvent(&e))
				if (e.type == SDL_QUIT)
					quit = true;
				else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
				{
					t.Rotate();
				}
			if (SDL_GetTicks64() - currentTicks >= 1000)
			{
				currentTicks = SDL_GetTicks64();
				pos.y += 50;
				t.Update(pos);
			}
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderClear(renderer);
			b.update();
			t.Render();
			SDL_RenderPresent(renderer);
		}
		CLOSE();
		return 0;
	}
	return 0;
}