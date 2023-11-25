#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<string>
using namespace std;

int _SCREENWIDTH = 1920, _SCREENHEIGHT = 1080;
SDL_Window* window = NULL;
SDL_Surface* screensurface = NULL;
SDL_Renderer* renderer = NULL;

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
			if(renderer == NULL)
			{
				cout << "Renderer could not be intialized, error : " << SDL_GetError() << endl;
				key = false;
			}
			if(!IMG_Init(IMG_INIT_PNG))
			{
				cout << "SDL_image could not be intialized, error : " << IMG_GetError() << endl;
				key = false;
			}
		}
	}
	return key;
}

SDL_Texture* GetTexture(string path)
{
	SDL_Texture *newTexture = NULL;
	SDL_Surface* loadSurface = IMG_Load(path.c_str());
	if (loadSurface == NULL)
		cout << "Image could not be loaded, error : " << IMG_GetError() << endl;
	else
	{
		newTexture = SDL_CreateTextureFromSurface(renderer, loadSurface);
		if (newTexture == NULL)
			cout << "Texture could not be created, error : " << SDL_GetError() << endl;
		SDL_FreeSurface(loadSurface);
	}
	return newTexture;
}

int main(int argc, char* args[])
{
	if (_INIT())
	{
		SDL_Rect d = {500, 500, 100, 100};
		SDL_Texture* Block = GetTexture("assets/img/block.png");
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, Block, NULL, &d);
		SDL_RenderPresent(renderer);
		
		SDL_Event e;
		bool quit = false;
		while(quit == false)
			while(SDL_PollEvent(&e))
				if(e.type == SDL_QUIT)
					quit = true;
		
		SDL_DestroyTexture(Block);
		Block = NULL;
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
	SDL_Quit();
	return 0;
}
