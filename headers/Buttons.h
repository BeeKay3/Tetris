#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

enum buttonState{
	KeyOver,
	KeyGone,
	KeyDown
};

class button
{
	private:
		SDL_Renderer *buttonRenderer;
		SDL_Texture *buttonTexture, *textTexture;
		SDL_Texture *hoverTexture, *clickTexture;
		SDL_Texture *currentTexture;
		TTF_Font *textFont;
		SDL_Color textColor;
		SDL_Rect textBox, buttonBox;
		buttonState currentState;

	public:
		button(SDL_Renderer *, std::string, int, int);
		void CopyToRenderer();
		void SetTexture(buttonState);
		~button();
};
