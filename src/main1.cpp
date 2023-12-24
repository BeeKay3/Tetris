#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "../headers/GetTexture.h"
#include "../headers/Menu.h"
using namespace std;

const int SCREENWIDTH = 1920, SCREENHEIGHT = 1080, BLOCKSIZE = 100;

SDL_Window *Window = NULL;
SDL_Renderer *Renderer = NULL;

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
		Window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
		if (Window == NULL)
		{
			cout << "Window could not be created, error : " << SDL_GetError() << endl;
			Key = false;
		}
		else
		{
			Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
			if (Renderer == NULL)
			{
				cout << "Renderer could not be intialized, error : " << SDL_GetError() << endl;
				Key = false;
			}
			if (!IMG_Init(IMG_INIT_PNG))
			{
				cout << "SDL_image could not be intialized, error : " << IMG_GetError() << endl;
				Key = false;
			}
			if (TTF_Init() < 0)
			{
				cout << "SDL_ttf coulf not be initialized, error : " << TTF_GetError() << endl;
				Key = false; 
			}
		}
	}
	return Key;
}

void CLOSE()
{
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	Renderer = NULL;
	Window = NULL;
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}

int main(int argc, char *args[])
{
	if (INIT())
	{
		Menu menu(Renderer);
		SDL_Event e;
		bool quit = false;
		Uint64 CurrentTicks, FrameTicks;
//		menu.credits();
//		menu.mainMenu();
//		menu.pause();
		menu.death("8", "1000", "50");
	}			
	CLOSE();
	return 0;
}
