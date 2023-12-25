#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include "../headers/board.h"
#include "../headers/Menu.h"

bool init();
void close();

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

int main(int argc, char *args[])
{
	if (!init())
		return 1;

	bool run = true;
	Menu menu(renderer);
	menuState currentState = freshState;
	menu.credits();
	while (run)
	{
		if (currentState == freshState || currentState == restartState)
			currentState = menu.mainMenu();
		else if (currentState == playState)
		{
			Board b(renderer, &menu);
			currentState = b.game();
		}
		else if (currentState == quitState)
		{
			run = false;
		}
	}

	close();
	return 0;
}

const int SCREENWIDTH = 1920, SCREENHEIGHT = 1080;

bool init()
{
	bool key = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL could not be initialized, error : " << SDL_GetError() << std::endl;
		key = false;
	}
	else
	{
		window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
		if (window == NULL)
		{
			std::cout << "Window could not be created, error : " << SDL_GetError() << std::endl;
			key = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				std::cout << "Renderer could not be intialized, error : " << SDL_GetError() << std::endl;
				key = false;
			}
			if (!IMG_Init(IMG_INIT_PNG))
			{
				std::cout << "SDL_image could not be intialized, error : " << IMG_GetError() << std::endl;
				key = false;
			}
			if (TTF_Init() < 0)
			{
				std::cout << "SDL_TTF not initialized, error: " << TTF_GetError() << std::endl;
				key = false;
			}
		}
	}
	return key;
}

void close()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}