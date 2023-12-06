#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include "../headers/GetTexture.h"
#include "../headers/Tetromino.h"
#include "../headers/board.h"

using namespace std;

const int SCREENWIDTH = 1920, SCREENHEIGHT = 1080, BLOCKSIZE = 50, INITIAL_X = 910, INITIAL_Y = 40;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool init()
{
	bool key = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL could not be initialized, error : " << SDL_GetError() << endl;
		key = false;
	}
	else
	{
		window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
		if (window == NULL)
		{
			cout << "Window could not be created, error : " << SDL_GetError() << endl;
			key = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				cout << "Renderer could not be intialized, error : " << SDL_GetError() << endl;
				key = false;
			}
			if (!IMG_Init(IMG_INIT_PNG))
			{
				cout << "SDL_image could not be intialized, error : " << IMG_GetError() << endl;
				key = false;
			}
		}
	}
	return key;
}

void close()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
	SDL_Quit();
}

int main(int argc, char *args[])
{
	if (!init())
		return 1;

	SDL_Event e;
	bool quit = false;
	Uint64 currentTicks;
	SDL_Texture *BASETILE = GetTexture(renderer, "assets/img/block.png");
	const SDL_Point INITIAL_POS = {INITIAL_X, INITIAL_Y};
	SDL_Point pos = INITIAL_POS;
	SDL_Rect currentTetromino[4];

	Board b(renderer, BLOCKSIZE);
	Tetromino t(renderer, BLOCKSIZE, BASETILE);

	t.update(pos, t.random(), currentTetromino);

	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = true;
			else if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_SPACE)
				{
					t.rotate(currentTetromino);
					if (b.collisionBlocks(currentTetromino))
					{
						t.rotate(currentTetromino);
						t.rotate(currentTetromino);
						t.rotate(currentTetromino);
					}
				}
				else if (e.key.keysym.sym == SDLK_z)
				{
					t.update(INITIAL_POS, t.random(), currentTetromino);
					pos = INITIAL_POS;
				}
				else if (e.key.keysym.sym == SDLK_LEFT)
				{
					if (!b.outOfLeftBounds(currentTetromino))
					{
						pos.x -= 50;
						t.update(pos, currentTetromino);
						if (b.collisionBlocks(currentTetromino))
						{
							pos.x += 50;
							t.update(pos, currentTetromino);
						}
					}
				}
				else if (e.key.keysym.sym == SDLK_RIGHT)
				{
					if (!b.outOfRightBounds(currentTetromino))
					{
						pos.x += 50;
						t.update(pos, currentTetromino);
						if (b.collisionBlocks(currentTetromino))
						{
							pos.x -= 50;
							t.update(pos, currentTetromino);
						}
					}
				}
				else if (e.key.keysym.sym == SDLK_DOWN)
				{
					pos.y += BLOCKSIZE;
					t.update(pos, currentTetromino);

					if (b.collisionBlocks(currentTetromino))
					{
						pos.y -= BLOCKSIZE;
						t.update(pos, currentTetromino);
						b.insert(currentTetromino, t.getShape());
						b.lineClear();
						b.updateLog();
						t.update(INITIAL_POS, t.random(), currentTetromino);
						pos = INITIAL_POS;
					}
				}
				else if (e.key.keysym.sym == SDLK_UP)
				{
					bool drop = true;
					while (drop)
					{
						pos.y += BLOCKSIZE;
						t.update(pos, currentTetromino);

						if (b.collisionBlocks(currentTetromino))
						{
							pos.y -= BLOCKSIZE;
							t.update(pos, currentTetromino);
							b.insert(currentTetromino, t.getShape());
							b.lineClear();
							b.updateLog();
							t.update(INITIAL_POS, t.random(), currentTetromino);
							pos = INITIAL_POS;
							drop = false;
						}
						else if (b.collisionGround(currentTetromino))
						{
							b.insert(currentTetromino, t.getShape());
							b.lineClear();
							b.updateLog();
							t.update(INITIAL_POS, t.random(), currentTetromino);
							pos = INITIAL_POS;
							drop = false;
						}
					}
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		b.update();
		t.render();
		SDL_RenderPresent(renderer);

		if (SDL_GetTicks64() - currentTicks >= 1000)
		{
			currentTicks = SDL_GetTicks64();
			pos.y += BLOCKSIZE;
			t.update(pos, currentTetromino);

			if (b.collisionBlocks(currentTetromino))
			{
				pos.y -= BLOCKSIZE;
				t.update(pos, currentTetromino);
				b.insert(currentTetromino, t.getShape());
				b.lineClear();
				b.updateLog();
				t.update(INITIAL_POS, t.random(), currentTetromino);
				pos = INITIAL_POS;
			}
			else if (b.collisionGround(currentTetromino))
			{
				b.insert(currentTetromino, t.getShape());
				b.lineClear();
				b.updateLog();
				t.update(INITIAL_POS, t.random(), currentTetromino);
				pos = INITIAL_POS;
			}
		}
	}
	close();
	return 0;
}