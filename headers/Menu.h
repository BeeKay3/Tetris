#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Menu
{
public:
	void mainMenu(SDL_Renderer *Renderer);
	void credits(SDL_Renderer *Renderer);
	Menu();
	~Menu();
private:
	TTF_Font *textFont, *writeFont;
	SDL_Color textColor;
};
