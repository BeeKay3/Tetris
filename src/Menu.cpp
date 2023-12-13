#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../headers/Menu.h"
#include "../headers/GetTexture.h"

void Menu::mainMenu(SDL_Renderer *Renderer)
{
	SDL_Texture *splash = GetTexture(Renderer, "assets/img/splash.png");
	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
	SDL_RenderCopy(Renderer, splash, NULL, NULL);
	SDL_RenderPresent(Renderer);
}
