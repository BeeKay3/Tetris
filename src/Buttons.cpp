#include "../headers/Buttons.h"
#include "../headers/GetTexture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

button::button(SDL_Renderer *Renderer, std::string text, int x, int y)
{
	buttonRenderer = Renderer;
	textFont = TTF_OpenFont("assets/fonts/Kanit-Bold.ttf", 45);
	textColor = {255, 255, 255, 255};
	buttonTexture = GetTexture(buttonRenderer, "assets/img/rect.png");
	hoverTexture =  GetTexture(buttonRenderer, "assets/img/rect.png");
	clickTexture =  GetTexture(buttonRenderer, "assets/img/rect.png");
	SDL_SetTextureColorMod(buttonTexture, 0, 90, 255);
	SDL_SetTextureColorMod(hoverTexture, 255, 200, 0);
	SDL_SetTextureColorMod(clickTexture, 100, 100, 100);
	currentTexture = buttonTexture;
	currentState = KeyGone;
	buttonBox.x = x;
	buttonBox.y = y;
	SDL_QueryTexture(buttonTexture, NULL, NULL, &buttonBox.w, &buttonBox.h);
	textTexture = GetTexture(buttonRenderer, textFont, text, textColor, &textBox);
	textBox.x = x + (buttonBox.w - textBox.w) / 2;
	textBox.y = y + (buttonBox.h - textBox.h) / 2;
}

void button::CopyToRenderer()
{
	SDL_RenderCopy(buttonRenderer, currentTexture, NULL, &buttonBox);
	SDL_RenderCopy(buttonRenderer, textTexture, NULL, &textBox);
}

void button::SetTexture(buttonState state)
{
	if(state == KeyGone)
		currentTexture = buttonTexture;
	else if(state == KeyOver)
		currentTexture = hoverTexture;
	else if(state == KeyDown)
		currentTexture = clickTexture;
}
button::~button()
{
	SDL_DestroyTexture(buttonTexture);
	buttonTexture = NULL;
	SDL_DestroyTexture(hoverTexture);
	hoverTexture = NULL;
	SDL_DestroyTexture(clickTexture);
	clickTexture = NULL;
	currentTexture = NULL;
	SDL_DestroyTexture(textTexture);
	textTexture = NULL;
}
