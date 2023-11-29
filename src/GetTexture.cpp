#include "../headers/GetTexture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

SDL_Texture *GetTexture(SDL_Renderer *renderer, std::string path)
{
	SDL_Texture *NewTexture = NULL;
	SDL_Surface *LoadSurface = IMG_Load(path.c_str());
	if (LoadSurface == NULL)
		std::cout << "Image could not be loaded, error : " << IMG_GetError() << std::endl;
	else
	{
		NewTexture = SDL_CreateTextureFromSurface(renderer, LoadSurface);
		if (NewTexture == NULL)
			std::cout << "Texture could not be created, error : " << SDL_GetError() << std::endl;
		SDL_FreeSurface(LoadSurface);
	}
	return NewTexture;
}
