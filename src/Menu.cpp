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

menuState Menu::mainMenu(SDL_Renderer *Renderer)
{
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	SDL_Rect buttonBox[3], textBox[3];
	SDL_Texture *gameText, *helpText, *quitText;

	SDL_Texture *splash = GetTexture(Renderer, "assets/img/splash.png");
	SDL_SetTextureBlendMode(splash, SDL_BLENDMODE_BLEND);
	SDL_Texture *button = GetTexture(Renderer, "assets/img/rect.png");
	SDL_SetTextureBlendMode(button, SDL_BLENDMODE_BLEND);
	SDL_SetTextureColorMod(button, 0, 90, 255);
	SDL_Texture *hoverButton = GetTexture(Renderer, "assets/img/rect.png");
	SDL_SetTextureColorMod(hoverButton, 255, 200, 0);
	SDL_Texture *clickButton = GetTexture(Renderer, "assets/img/rect.png");
	SDL_SetTextureColorMod(clickButton, 100, 100, 100);
	SDL_Texture *smallBlock = GetTexture(Renderer, "assets/img/smallBlock.png");
	SDL_SetTextureColorMod(smallBlock, 0, 90 ,255);
	SDL_Texture *hoverSmallBlock = GetTexture(Renderer, "assets/img/smallBlock.png");
	SDL_SetTextureColorMod(hoverSmallBlock, 255, 200, 0);
	SDL_Texture *clickSmallBlock = GetTexture(Renderer, "assets/img/smallBlock.png");
	SDL_SetTextureColorMod(clickSmallBlock, 100, 100 ,100);
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
		if (SDL_GetTicks64() - frameTime > 10 )
		{
			SDL_SetTextureAlphaMod(splash, alphaVal++);
			frameTime = SDL_GetTicks64();
		}
		SDL_RenderCopy(Renderer, splash, NULL, NULL);
		SDL_RenderPresent(Renderer);
	}

	frameTime = SDL_GetTicks64();
	while(!aKey)
	{
		SDL_RenderClear(Renderer);
		if ( (SDL_GetTicks64() - frameTime) > 15)
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
			frameTime = SDL_GetTicks64();
		}

		SDL_RenderCopy(Renderer, splash, NULL, NULL);
		for (int i = 0; i <= 2; i++)
			SDL_RenderCopy(Renderer, button, NULL, &buttonBox[i]);
		SDL_RenderCopy(Renderer, gameText, NULL, &textBox[0]);
		SDL_RenderCopy(Renderer, helpText, NULL, &textBox[1]);
		SDL_RenderCopy(Renderer, quitText, NULL, &textBox[2]);

		SDL_RenderPresent(Renderer);
	}

	SDL_Event e;
	SDL_Point mouseLocation;
	SDL_Texture *currentButtonTexture[3] = {button, button, button};
	int mouseKey = 0;
	menuState currentState = freshState;
	while(currentState == freshState)
	{
		SDL_RenderClear(Renderer);
		SDL_RenderCopy(Renderer, splash, NULL, NULL);
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_MOUSEMOTION && mouseKey == -1)
			{
				SDL_GetMouseState(&mouseLocation.x, &mouseLocation.y);
				for(int i = 0; i <= 2; i++)
				{
					if(SDL_PointInRect(&mouseLocation, &buttonBox[i]) == SDL_TRUE)
						currentButtonTexture[i] = hoverButton;
					else
						currentButtonTexture[i] = button;
				}
			}
			else if(e.type == SDL_MOUSEBUTTONDOWN || mouseKey != -1)
			{
				SDL_GetMouseState(&mouseLocation.x, &mouseLocation.y);
				for(int i = 0; i <= 2; i++)
				{
					if(SDL_PointInRect(&mouseLocation, &buttonBox[i]) == SDL_TRUE)
					{
						currentButtonTexture[i] = clickButton;
						mouseKey = i;
					}
				}
				if(SDL_PointInRect(&mouseLocation, &buttonBox[mouseKey]) == SDL_FALSE)
				{
					currentButtonTexture[mouseKey] = button;
					mouseKey = -1;
				}
			}
			if(e.type == SDL_MOUSEBUTTONUP)
			{
				SDL_GetMouseState(&mouseLocation.x, &mouseLocation.y);
				if(SDL_PointInRect(&mouseLocation, &buttonBox[mouseKey]) == SDL_TRUE)
				{
					if(mouseKey == 0)
					{
						currentButtonTexture[mouseKey] = button;
						mouseKey = -1;
						SDL_Rect smallRect[2], smallTextBox[2], bigTextBox[2];
						for (int i = 0; i < 2; i++)
						{
							smallRect[i].x = buttonBox[1].x + buttonBox[1].w + 25 - (i * (buttonBox[1].w + 50 + buttonBox[1].h));
							smallRect[i].y = buttonBox[1].y;
							smallRect[i].w = buttonBox[1].h;
							smallRect[i].h = buttonBox[1].h;
						}
						std::string levelText[10] = {"Level 1", "Level 2", "Level 3", "Level 4", "Level 5", "Level 6", "Level 7", "Level 8", "Level 9", "Level 10"};
						SDL_Texture *smallTextTexture[2], *bigTextTexture[2];
						smallTextTexture[0] = GetTexture(Renderer, textFont, ">", textColor, &smallTextBox[0]);
						smallTextTexture[1] = GetTexture(Renderer, textFont, "<", textColor, &smallTextBox[1]);
						bigTextTexture[0] = GetTexture(Renderer, textFont, "Play", textColor, &bigTextBox[0]);
						bigTextTexture[1] = GetTexture(Renderer, textFont, levelText[0], textColor, &bigTextBox[1]);
						bigTextBox[0].x = buttonBox[0].x + (buttonBox[0].w - bigTextBox[0].w) / 2; bigTextBox[0].y = buttonBox[0].y + (buttonBox[0].h - bigTextBox[0].h) / 2;
						bigTextBox[1].x = buttonBox[1].x + (buttonBox[1].w - bigTextBox[1].w) / 2; bigTextBox[1].y = buttonBox[1].y + (buttonBox[1].h - bigTextBox[1].h) / 2;
						smallTextBox[0].x = smallRect[0].x + (smallRect[0].w - smallTextBox[0].w) / 2; smallTextBox[0].y = smallRect[0].y + (smallRect[0].h - smallTextBox[0].h) / 2;
						smallTextBox[1].x = smallRect[1].x + (smallRect[1].w - smallTextBox[1].w) / 2; smallTextBox[1].y = smallRect[1].y + (smallRect[1].h - smallTextBox[1].h) / 2;
						SDL_RenderClear(Renderer);
						SDL_RenderCopy(Renderer, splash, NULL, NULL);
						SDL_RenderCopy(Renderer, button, NULL, &buttonBox[0]);
						SDL_RenderCopy(Renderer, button, NULL, &buttonBox[1]);
						SDL_RenderCopy(Renderer, smallBlock, NULL, &smallRect[0]);
						SDL_RenderCopy(Renderer, smallBlock, NULL, &smallRect[1]);
						SDL_RenderCopy(Renderer, smallTextTexture[0], NULL, &smallTextBox[0]);
						SDL_RenderCopy(Renderer, smallTextTexture[1], NULL, &smallTextBox[1]);
						SDL_RenderCopy(Renderer, bigTextTexture[0], NULL, &bigTextBox[0]);
						SDL_RenderCopy(Renderer, bigTextTexture[1], NULL, &bigTextBox[1]);
						SDL_RenderPresent(Renderer);
						SDL_Event e;
						bool quit = false;
						while(!quit)
							while(SDL_PollEvent(&e))
								if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
									quit = true;
					}
					if(mouseKey == 1)
					{
						currentButtonTexture[mouseKey] = button;
						mouseKey = -1;
						SDL_Texture *staticBackground = SDL_CreateTexture(Renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1920, 1080);
						SDL_SetRenderTarget(Renderer, staticBackground);
						SDL_RenderCopy(Renderer, splash, NULL, NULL);
						for (int i = 0; i <= 2; i++)
							SDL_RenderCopy(Renderer, currentButtonTexture[i], NULL, &buttonBox[i]);
						SDL_RenderCopy(Renderer, gameText, NULL, &textBox[0]);
						SDL_RenderCopy(Renderer, helpText, NULL, &textBox[1]);
						SDL_RenderCopy(Renderer, quitText, NULL, &textBox[2]);
						help(Renderer, staticBackground);
					}
					if(mouseKey == 2)
						return quitState;
				}
			}
		}
		SDL_RenderCopy(Renderer, splash, NULL, NULL);
		for (int i = 0; i <= 2; i++)
			SDL_RenderCopy(Renderer, currentButtonTexture[i], NULL, &buttonBox[i]);
		SDL_RenderCopy(Renderer, gameText, NULL, &textBox[0]);
		SDL_RenderCopy(Renderer, helpText, NULL, &textBox[1]);
		SDL_RenderCopy(Renderer, quitText, NULL, &textBox[2]);
		SDL_RenderPresent(Renderer);
	}
}

void Menu::credits(SDL_Renderer *Renderer)
{
	SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
	SDL_Rect textBox[9];
	SDL_Texture *Credits[9];
	std::string creditText[9] = {"Developed By", "Kathmandu University, B.tech in AI, 1st Year Students",  "Aryan Shakya", "Bikalpa Khachhibhoya", "Sujal Bajracharya", " ", "With Assistance From", "Kathmandu University, Department of Computer Science & Engineering, Lecturer", "Mrs. Rojina Shakya"};
	int alphaVal = 0;
	for (int i = 0; i <= 8; i++)
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
		if (SDL_GetTicks64() - frameTime > 15)
		{
			if(bKey)
				alphaVal -= 1;
			else if (!bKey && alphaVal != 255)
				alphaVal += 1;
			for (int j = 0; j <= 8; j++)
				SDL_SetTextureAlphaMod(Credits[j], alphaVal);
			frameTime = SDL_GetTicks64();
		}
		for (int i = 0; i <= 8; i++)
			SDL_RenderCopy(Renderer, Credits[i], NULL, &textBox[i]);
		if(alphaVal < 0)
			break;
		else if(alphaVal == 255)
			bKey = true;
		SDL_RenderPresent(Renderer);
	}
}

void Menu::help(SDL_Renderer *Renderer, SDL_Texture *staticBackground)
{
	SDL_SetTextureBlendMode(staticBackground, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(staticBackground, 50);
	SDL_SetRenderTarget(Renderer, NULL);
	SDL_Rect textBox;
	textBox.y = 540; textBox.x = 960;
	SDL_Texture *instructions = GetTexture(Renderer, writeFont, "Press Esc to go back", textColor, &textBox);
	textBox.x -= textBox.w / 2;
	SDL_RenderClear(Renderer);
	SDL_RenderCopy(Renderer, staticBackground, NULL, NULL);
	SDL_RenderCopy(Renderer, instructions, NULL, &textBox);
	SDL_RenderPresent(Renderer);
	SDL_Event e;
	bool quit = false;
	while(!quit)
		while(SDL_PollEvent(&e))
			if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
				quit = true;
}

Menu::~Menu()
{
	TTF_CloseFont(textFont);
}
