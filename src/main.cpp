#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "../headers/GetTexture.h"
#include "../headers/Tetromino.h"
using namespace std;

const int _SCREENWIDTH = 1920, _SCREENHEIGHT = 1080, _BLOCKSIZE = 100;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool _INIT()
{
	bool key = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL could not be initialized, error : " << SDL_GetError() << endl;
		key = false;
	}
	else
	{
		window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _SCREENWIDTH, _SCREENHEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
		if (window == NULL)
		{
			cout << "Window could not be created, error : " << SDL_GetError() << endl;
			key = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				cout << "Renderer could not be intialized, error : " << SDL_GetError() << endl;
				key = false;
			}
			if (!IMG_Init(IMG_INIT_PNG))
			{
				cout << "SDL_image could not be intialized, error : " << IMG_GetError() << endl;
				key = false;
			}
		}
	}
	return key;
}

void _CLOSE()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
	SDL_Quit();
}

int main(int argc, char *args[])
{
	if (_INIT())
	{
		SDL_Texture *BaseTile = GetTexture(renderer, "assets/img/block.png");
		SDL_Point p = {300, 300};
		tetromino a(p, _J, _BLOCKSIZE, BaseTile);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		a.Render(renderer);
		SDL_RenderPresent(renderer);

		SDL_Event e;
		bool quit = false;
		while (quit == false)
			while (SDL_PollEvent(&e))
				if (e.type == SDL_QUIT)
					quit = true;
	}
	_CLOSE();
	return 0;
}
