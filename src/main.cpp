#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "../headers/GetTexture.h"
#include "../headers/Tetromino.h"
using namespace std;

const int SCREENWIDTH = 1920, SCREENHEIGHT = 1080, BLOCKSIZE = 50;

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
			Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
}

int main(int argc, char *args[])
{
	if (INIT())
	{
		SDL_Texture *BaseTile = GetTexture(Renderer, "assets/img/block.png");
		SDL_Point p2 = {1000, 100};
		tetromino a(BLOCKSIZE, BaseTile);
		SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
		SDL_RenderClear(Renderer);
		a.Update(p2, Z_Shape);

		SDL_Event e;
		bool quit = false;
		Uint64 CurrentTicks, FrameTicks;

		CurrentTicks = SDL_GetTicks64();
		while (quit == false)
		{
			while (SDL_PollEvent(&e))
				if (e.type == SDL_QUIT)
					quit = true;
				else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
					a.Rotate();
			if (SDL_GetTicks64() - CurrentTicks >= 1000)
			{
				CurrentTicks = SDL_GetTicks64();
				p2.y += 50;
				a.Update(p2);
			}
			SDL_RenderClear(Renderer);
			a.Render(Renderer);
			SDL_RenderPresent(Renderer);
		}
	}
	CLOSE();
	return 0;
}
