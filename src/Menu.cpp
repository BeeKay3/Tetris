#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "../headers/Menu.h"
#include "../headers/GetTexture.h"
#include "../headers/Buttons.h"


Menu::Menu(SDL_Renderer *Renderer)
{
	textFont = TTF_OpenFont("assets/fonts/Kanit-Bold.ttf", 45);
	writeFont = TTF_OpenFont("assets/fonts/Cantarell-Bold.ttf", 25);
	textColor = {255, 255, 255, 255};

	menuRenderer = Renderer;
	splash = GetTexture(menuRenderer, "assets/img/splash.png");
	SDL_SetTextureBlendMode(splash, SDL_BLENDMODE_BLEND);
}

menuState Menu::mainMenu()
{
	currentState = freshState;
	SDL_SetRenderDrawColor(menuRenderer, 0, 0, 0, 255);

	int alphaVal = 0;
	SDL_SetTextureAlphaMod(splash, alphaVal);
	Uint64 frameTime = SDL_GetTicks64();
	bool aKey = false;
	while(alphaVal <= 255)
	{
		SDL_RenderClear(menuRenderer);
		if (SDL_GetTicks64() - frameTime > 10 )
		{
			SDL_SetTextureAlphaMod(splash, alphaVal++);
			frameTime = SDL_GetTicks64();
		}
		SDL_RenderCopy(menuRenderer, splash, NULL, NULL);
		SDL_RenderPresent(menuRenderer);
	}
	
	button Play(menuRenderer, "Play", 1400, 560), Help(menuRenderer, "Help", 1400, 680), Quit(menuRenderer, "Quit", 1400, 800);
	Play.CopyToRenderer();
	Help.CopyToRenderer();
	Quit.CopyToRenderer();
	SDL_Event e;
	int keycheck = 0;

	while(currentState == freshState)
	{
		while(SDL_PollEvent(&e))
			if (e.type == SDL_KEYDOWN)
			{
				if(e.key.keysym.sym == SDLK_DOWN && keycheck < 4)
					keycheck++;
				else if(e.key.keysym.sym == SDLK_UP && keycheck > 0)
					keycheck--;
				else if(e.key.keysym.sym == SDLK_RETURN && keycheck > 0)
				{
					if (keycheck == 1)
						currentState = playState;
					else if(keycheck == 2)
						help();
					else if(keycheck == 3)
						currentState = quitState;
				}
			}
		if (keycheck == 1)
		{
			Play.SetTexture(KeyOver);
			Help.SetTexture(KeyGone);
			Quit.SetTexture(KeyGone);
		}
		else if (keycheck == 2)
		{
			Play.SetTexture(KeyGone);
			Help.SetTexture(KeyOver);
			Quit.SetTexture(KeyGone);
		}
		else if(keycheck == 3)
		{
			Play.SetTexture(KeyGone);
			Help.SetTexture(KeyGone);
			Quit.SetTexture(KeyOver);
		}
		SDL_RenderClear(menuRenderer);
		SDL_RenderCopy(menuRenderer, splash, NULL, NULL);
		Play.CopyToRenderer();
		Help.CopyToRenderer();
		Quit.CopyToRenderer();
		SDL_RenderPresent(menuRenderer);
	}
	return currentState;
}

void Menu::credits()
{
	SDL_SetRenderDrawColor(menuRenderer, 0, 0, 0, 255);
	SDL_Rect textBox[9];
	SDL_Texture *Credits[9];
	std::string creditText[9] = {"Developed By", "Kathmandu University, B.tech in AI, 1st Year Students",  "Aryan Shakya", "Bikalpa Khachhibhoya", "Sujal Bajracharya", " ", "With Assistance From", "Kathmandu University, Department of Computer Science & Engineering, Lecturer", "Mrs. Rojina Shakya"};
	int alphaVal = 0;
	for (int i = 0; i <= 8; i++)
	{
		Credits[i] = GetTexture(menuRenderer, writeFont, creditText[i], textColor, &textBox[i]);
		SDL_SetTextureAlphaMod(Credits[i], alphaVal);
		textBox[i].x = 960 - (textBox[i].w / 2);
		textBox[i].y = 300 + i * 60;
	}

	Uint64 frameTime = SDL_GetTicks64();
	bool aKey = false, bKey = false;;
	while(!aKey)
	{
		SDL_RenderClear(menuRenderer);
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
			SDL_RenderCopy(menuRenderer, Credits[i], NULL, &textBox[i]);
		if(alphaVal < 0)
			break;
		else if(alphaVal == 255)
			bKey = true;
		SDL_RenderPresent(menuRenderer);
	}
	for (int i = 0; i <= 8; i++)
	{
		SDL_DestroyTexture(Credits[i]);
		Credits[i] = NULL;
	}
}

menuState Menu::pause()
{
	SDL_Texture *staticBackground = GetTexture(menuRenderer, "assets/img/splash.png");
	SDL_SetTextureBlendMode(staticBackground, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(staticBackground, 50);
	button Resume(menuRenderer, "Resume", 800, 300 ), Restart(menuRenderer, "Restart", 800, 430), Help(menuRenderer, "Help", 800, 560), Quit(menuRenderer, "Quit", 800, 690);
	currentState = pauseState;

	SDL_RenderCopy(menuRenderer, staticBackground, NULL, NULL);
	Resume.CopyToRenderer();
	Restart.CopyToRenderer();
	Help.CopyToRenderer();
	Quit.CopyToRenderer();
	SDL_RenderPresent(menuRenderer);
	
	SDL_Event e;
	int keycheck = 0;

	while(currentState == pauseState)
	{
		while(SDL_PollEvent(&e))
			if (e.type == SDL_KEYDOWN)
			{
				if(e.key.keysym.sym == SDLK_DOWN && keycheck < 5)
					keycheck++;
				else if(e.key.keysym.sym == SDLK_UP && keycheck > 0)
					keycheck--;
				else if(e.key.keysym.sym == SDLK_RETURN && keycheck > 0)
				{
					if (keycheck == 1)
						currentState = playState;
					else if(keycheck == 2)
						currentState = restartState;
					else if(keycheck == 3)
						help();
					else if(keycheck == 4)
						currentState = quitState;
				}
			}
		if (keycheck == 1)
		{
			Resume.SetTexture(KeyOver);
			Restart.SetTexture(KeyGone);
			Help.SetTexture(KeyGone);
			Quit.SetTexture(KeyGone);
		}
		else if (keycheck == 2)
		{
			Resume.SetTexture(KeyGone);
			Restart.SetTexture(KeyOver);
			Help.SetTexture(KeyGone);
			Quit.SetTexture(KeyGone);
		}
		else if(keycheck == 3)
		{
			Resume.SetTexture(KeyGone);
			Restart.SetTexture(KeyGone);
			Help.SetTexture(KeyOver);
			Quit.SetTexture(KeyGone);
		}
		else if(keycheck == 4)
		{
			Resume.SetTexture(KeyGone);
			Restart.SetTexture(KeyGone);
			Help.SetTexture(KeyGone);
			Quit.SetTexture(KeyOver);
		}
		SDL_RenderClear(menuRenderer);
		SDL_RenderCopy(menuRenderer, staticBackground, NULL, NULL);
		Resume.CopyToRenderer();
		Restart.CopyToRenderer();
		Help.CopyToRenderer();
		Quit.CopyToRenderer();
		SDL_RenderPresent(menuRenderer);
	}

	SDL_DestroyTexture(staticBackground);
	staticBackground = NULL;
	return currentState;
}

void Menu::help()
{
	SDL_Texture *staticBackground = GetTexture(menuRenderer, "assets/img/splash.png");
	SDL_SetTextureBlendMode(staticBackground, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(staticBackground, 50);
	SDL_Rect textBox;
	textBox.y = 540; textBox.x = 960;
	SDL_Texture *instructions = GetTexture(menuRenderer, writeFont, "Press Esc to go back", textColor, &textBox);
	textBox.x -= textBox.w / 2;
	SDL_RenderClear(menuRenderer);
	SDL_RenderCopy(menuRenderer, staticBackground, NULL, NULL);
	SDL_RenderCopy(menuRenderer, instructions, NULL, &textBox);
	SDL_RenderPresent(menuRenderer);
	SDL_Event e;
	bool quit = false;
	while(!quit)
		while(SDL_PollEvent(&e))
			if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
				quit = true;
	SDL_DestroyTexture(staticBackground);
	staticBackground = NULL;
	SDL_DestroyTexture(instructions);
	instructions = NULL;
}

Menu::~Menu()
{
	TTF_CloseFont(textFont);
	textFont = NULL;
	TTF_CloseFont(writeFont);
	writeFont = NULL;
	SDL_DestroyTexture(splash);
	splash = NULL;
}
