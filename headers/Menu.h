#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

enum menuState{
	freshState,
	playState,
	pauseState,
	quitState,
};

class Menu
{
public:
	menuState mainMenu(SDL_Renderer *Renderer);
	void credits(SDL_Renderer *Renderer);
	void help(SDL_Renderer *Renderer, SDL_Texture *staticBackground);
	Menu();
	~Menu();
private:
	TTF_Font *textFont, *writeFont;
	SDL_Color textColor;
};
