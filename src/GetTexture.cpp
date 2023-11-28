#include "../headers/GetTexture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

SDL_Texture *GetTexture(SDL_Renderer *renderer, std::string path)
{
	SDL_Texture *newTexture = NULL;
	SDL_Surface *loadSurface = IMG_Load(path.c_str());
	if (loadSurface == NULL)
		std::cout << "Image could not be loaded, error : " << IMG_GetError() << std::endl;
	else
	{
		newTexture = SDL_CreateTextureFromSurface(renderer, loadSurface);
		if (newTexture == NULL)
			std::cout << "Texture could not be created, error : " << SDL_GetError() << std::endl;
		SDL_FreeSurface(loadSurface);
	}
	return newTexture;
}
