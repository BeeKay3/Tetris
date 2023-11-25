#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
using namespace std;

int _SCREENWIDTH = 1920, _SCREENHEIGHT = 1080;
SDL_Window* window = NULL;
SDL_Surface* screensurface = NULL;

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
			if(!IMG_Init(IMG_INIT_PNG))
			{
				cout << "SDL_image could not be initialized, error : " << IMG_GetError() << endl;
				key = false;
			}
			else
			{
				screensurface = SDL_GetWindowSurface(window);
			}
		}
	}
	return key;
}

int main(int argc, char* args[])
{
	if (_INIT())
	{
		
		SDL_FillRect( screensurface, NULL, SDL_MapRGB(screensurface->format, 255, 255, 255));
		
		SDL_UpdateWindowSurface(window);

		SDL_Event e;
		bool quit = false;
		while(quit == false)
			while(SDL_PollEvent(&e))
				if(e.type == SDL_QUIT)
					quit = true;
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
