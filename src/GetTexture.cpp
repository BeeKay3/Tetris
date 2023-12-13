#include "../headers/GetTexture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
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

SDL_Texture *GetTexture(SDL_Renderer *renderer, TTF_Font *fonts, std::string text, SDL_Color textColor, SDL_Rect *textBox)
{
	SDL_Texture *newTexture = NULL;
	SDL_Surface *loadSurface = TTF_RenderText_Blended(fonts, text.c_str(), textColor);
	if (loadSurface == NULL)
		std::cout << "Text could not be rendererd, error : " << TTF_GetError() << std::endl;
	else
	{
		newTexture = SDL_CreateTextureFromSurface(renderer, loadSurface);
		if (newTexture == NULL)
			std::cout << "Texture could not be created, error : " << SDL_GetError() << std::endl;
		textBox->w = loadSurface->w;
		textBox->h = loadSurface->h;
		SDL_FreeSurface(loadSurface);
	}
	return newTexture;
}
