#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

enum shape
{
	_I,
	_O,
	_T,
	_J,
	_L,
	_S,
	_Z
};

class tetromino
{
public:
	tetromino(SDL_Point p, shape ShapeVal, int _BLOCKSIZE, SDL_Texture *BaseTile);
	~tetromino();
	void Render(SDL_Renderer *renderer);

private:
	SDL_Rect _Blocks[4];
	SDL_Point _Center;
	SDL_Texture *Tile;
};

