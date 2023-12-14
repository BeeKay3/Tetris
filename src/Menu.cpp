#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "../headers/Menu.h"
#include "../headers/GetTexture.h"


Menu::Menu()
{
	textFont = TTF_OpenFont("assets/fonts/Kanit-Bold.ttf", 45);
	writeFont = TTF_OpenFont("assets/fonts/Cantarell-Bold.ttf", 25);
	textColor = {255, 255, 255, 255};
}

void Menu::mainMenu(SDL_Renderer *Renderer)
{
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	SDL_Rect buttonBox[3], textBox[3];
	SDL_Texture *gameText, *helpText, *quitText;
	
	SDL_Texture *splash = GetTexture(Renderer, "assets/img/splash.png");
	SDL_SetTextureBlendMode(splash, SDL_BLENDMODE_BLEND);
	SDL_Texture *button = GetTexture(Renderer, "assets/img/rect.png");
	SDL_SetTextureColorMod(button, 0, 90, 255);
	gameText = GetTexture(Renderer, textFont, "Start", textColor, &textBox[0]);
	helpText = GetTexture(Renderer, textFont, "Help", textColor, &textBox[1]);
	quitText = GetTexture(Renderer, textFont, "Quit", textColor, &textBox[2]);
	for (int i = 0; i <= 2; i++ )
	{
		buttonBox[i].x = 1920;
		textBox[i].x = buttonBox[i].x;
		buttonBox[i].y = 560 + i * 120;
		buttonBox[i].w = 363;
		buttonBox[i].h = 100;
		textBox[i].y = buttonBox[i].y + (buttonBox[i].h - textBox[i].h) / 2;
	}

	int alphaVal = 0;
	SDL_SetTextureAlphaMod(splash, alphaVal);
	Uint64 frameTime = SDL_GetTicks64();
	bool aKey = false;
	while(alphaVal <= 255)
	{
		SDL_RenderClear(Renderer);
		if (SDL_GetTicks64() - frameTime > 4 )
		{
			SDL_SetTextureAlphaMod(splash, alphaVal++);
			frameTime = SDL_GetTicks64();
		}
		SDL_RenderCopy(Renderer, splash, NULL, NULL);
		SDL_RenderPresent(Renderer);
	}
	while(!aKey)
	{
		SDL_RenderClear(Renderer);
		if ( (SDL_GetTicks64() - frameTime) > 20)
		{
			if (buttonBox[0].x > 1400)
			{
				buttonBox[0].x -= 55;
				textBox[0].x = buttonBox[0].x + (buttonBox[0].w - textBox[0].w) / 2;
			}
			if (buttonBox[0].x < 1580 && buttonBox[1].x > 1400)
			{
				buttonBox[1].x -= 55;
				textBox[1].x = buttonBox[1].x + (buttonBox[1].w - textBox[1].w) / 2;
			}
			if (buttonBox[1].x < 1580 && buttonBox[2].x > 1400)
			{
				buttonBox[2].x -= 55;
				textBox[2].x = buttonBox[2].x + (buttonBox[2].w - textBox[2].w) / 2;
			}
			if (buttonBox[2].x < 1400)
				aKey = true;
		}
		
		SDL_RenderCopy(Renderer, splash, NULL, NULL);
		for (int i = 0; i <= 2; i++)
			SDL_RenderCopy(Renderer, button, NULL, &buttonBox[i]);
		SDL_RenderCopy(Renderer, gameText, NULL, &textBox[0]);
		SDL_RenderCopy(Renderer, helpText, NULL, &textBox[1]);
		SDL_RenderCopy(Renderer, quitText, NULL, &textBox[2]);

		SDL_RenderPresent(Renderer);
	}
}

void Menu::credits(SDL_Renderer *Renderer)
{
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	SDL_Rect textBox[6];
	SDL_Texture *Credits[6];
	std::string creditText[6] = {"Developed By", "Aryan Shakya", "Bikalpa Khachhibhoya", "Sujal Bajracharya", "With Assistance From", "Rojina Shakya"};
	int alphaVal = 0;
	for (int i = 0; i <= 5; i++)
	{
		Credits[i] = GetTexture(Renderer, writeFont, creditText[i], textColor, &textBox[i]);
		SDL_SetTextureAlphaMod(Credits[i], alphaVal);
		textBox[i].x = 960 - (textBox[i].w / 2);
		textBox[i].y = 300 + i * 60;
	}
	
	Uint64 frameTime = SDL_GetTicks64();
	bool aKey = false, bKey = false;;
	while(!aKey)
	{
		SDL_RenderClear(Renderer);
		if (SDL_GetTicks64() - frameTime > 35)
		{
			if(bKey)
				alphaVal -= 5;
			else if (!bKey && alphaVal != 255)
				alphaVal += 5;
			for (int j = 0; j <= 5; j++)
				SDL_SetTextureAlphaMod(Credits[j], alphaVal);
			frameTime = SDL_GetTicks64();
		}
		for (int i = 0; i <= 5; i++)
			SDL_RenderCopy(Renderer, Credits[i], NULL, &textBox[i]);
		if(alphaVal < 0)
			break;
		else if(alphaVal == 255)
			bKey = true;
		SDL_RenderPresent(Renderer);
	}
}
Menu::~Menu()
{
	TTF_CloseFont(textFont);
}
