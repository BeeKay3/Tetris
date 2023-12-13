#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../headers/Menu.h"
#include "../headers/GetTexture.h"

void Menu::mainMenu(SDL_Renderer *Renderer)
{
	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
	TTF_Font *textFont = TTF_OpenFont("assets/fonts/Cantarell-Bold.ttf", 75);
	TTF_SetFontStyle(textFont, TTF_STYLE_BOLD);
	SDL_Color textColor = {0, 0, 0, 255};
	SDL_Rect textBox = {1000, 800, 0, 0};
	
	SDL_Texture *splash = GetTexture(Renderer, "assets/img/splash.png");
	SDL_Texture *gameText = GetTexture(Renderer, textFont, "NEW GAME", textColor, &textBox);

	SDL_RenderCopy(Renderer, splash, NULL, NULL);
	SDL_RenderCopy(Renderer, gameText, NULL, &textBox);
	SDL_RenderPresent(Renderer);
}
