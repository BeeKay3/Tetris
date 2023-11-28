#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../headers/Tetromino.h"
#include "../headers/GetTexture.h"

tetromino::tetromino(SDL_Point p, shape ShapeVal, int _BLOCKSIZE, SDL_Texture *BaseTile)
{
	_Center = p;
	Tile = BaseTile;
	if (ShapeVal == _O)
	{
		_Blocks[0] = {_Center.x, _Center.y, _BLOCKSIZE, _BLOCKSIZE};
		_Blocks[1] = {_Center.x + _BLOCKSIZE, _Center.y, _BLOCKSIZE, _BLOCKSIZE};
		_Blocks[2] = {_Center.x + _BLOCKSIZE, _Center.y + _BLOCKSIZE, _BLOCKSIZE, _BLOCKSIZE};
		_Blocks[3] = {_Center.x, _Center.y + _BLOCKSIZE, _BLOCKSIZE, _BLOCKSIZE};
		SDL_SetTextureColorMod(Tile, 255, 255, 0);
	}
	else if (ShapeVal == _T)
	{
		_Blocks[0] = {_Center.x, _Center.y, _BLOCKSIZE, _BLOCKSIZE};
		_Blocks[1] = {_Center.x, _Center.y - _BLOCKSIZE, _BLOCKSIZE, _BLOCKSIZE};
		_Blocks[2] = {_Center.x + _BLOCKSIZE, _Center.y, _BLOCKSIZE, _BLOCKSIZE};
		_Blocks[3] = {_Center.x - _BLOCKSIZE, _Center.y, _BLOCKSIZE, _BLOCKSIZE};
		SDL_SetTextureColorMod(Tile, 150, 0, 255);
	}
	else if (ShapeVal == _J)
	{
		_Blocks[0] = {_Center.x, _Center.y, _BLOCKSIZE, _BLOCKSIZE};
		_Blocks[1] = {_Center.x + _BLOCKSIZE, _Center.y, _BLOCKSIZE, _BLOCKSIZE};
		_Blocks[2] = {_Center.x - _BLOCKSIZE, _Center.y, _BLOCKSIZE, _BLOCKSIZE};
		_Blocks[3] = {_Center.x - _BLOCKSIZE, _Center.y - _BLOCKSIZE, _BLOCKSIZE, _BLOCKSIZE};
		SDL_SetTextureColorMod(Tile, 0, 0, 255);
	}
	else if (ShapeVal == _L)
	{
		_Blocks[0] = {_Center.x, _Center.y, _BLOCKSIZE, _BLOCKSIZE};
		_Blocks[1] = {_Center.x + _BLOCKSIZE, _Center.y - _BLOCKSIZE, _BLOCKSIZE, _BLOCKSIZE};
		_Blocks[2] = {_Center.x + _BLOCKSIZE, _Center.y, _BLOCKSIZE, _BLOCKSIZE};
		_Blocks[3] = {_Center.x - _BLOCKSIZE, _Center.y, _BLOCKSIZE, _BLOCKSIZE};
		SDL_SetTextureColorMod(Tile, 255, 150, 0);
	}
	else if (ShapeVal == _S)
	{
		_Blocks[0] = {_Center.x, _Center.y, _BLOCKSIZE, _BLOCKSIZE};
		_Blocks[1] = {_Center.x + _BLOCKSIZE, _Center.y, _BLOCKSIZE, _BLOCKSIZE};
		_Blocks[2] = {_Center.x, _Center.y + _BLOCKSIZE, _BLOCKSIZE, _BLOCKSIZE};
		_Blocks[3] = {_Center.x - _BLOCKSIZE, _Center.y + _BLOCKSIZE, _BLOCKSIZE, _BLOCKSIZE};
		SDL_SetTextureColorMod(Tile, 50, 255, 0);
	}
	else if (ShapeVal == _Z)
	{
		_Blocks[0] = {_Center.x, _Center.y, _BLOCKSIZE, _BLOCKSIZE};
		_Blocks[1] = {_Center.x + _BLOCKSIZE, _Center.y + _BLOCKSIZE, _BLOCKSIZE, _BLOCKSIZE};
		_Blocks[2] = {_Center.x, _Center.y + _BLOCKSIZE, _BLOCKSIZE, _BLOCKSIZE};
		_Blocks[3] = {_Center.x - _BLOCKSIZE, _Center.y, _BLOCKSIZE, _BLOCKSIZE};
		SDL_SetTextureColorMod(Tile, 255, 0, 0);
	}
	else if (ShapeVal == _I)
	{
		_Blocks[0] = {_Center.x + _BLOCKSIZE, _Center.y, _BLOCKSIZE, _BLOCKSIZE};
		_Blocks[1] = {_Center.x, _Center.y, _BLOCKSIZE, _BLOCKSIZE};
		_Blocks[2] = {_Center.x - _BLOCKSIZE, _Center.y, _BLOCKSIZE, _BLOCKSIZE};
		_Blocks[3] = {_Center.x - (2 * _BLOCKSIZE), _Center.y, _BLOCKSIZE, _BLOCKSIZE};
		SDL_SetTextureColorMod(Tile, 0, 190, 255);
	}
}

void tetromino::Render(SDL_Renderer *renderer)
{
	for (int i = 0; i <= 3; i++)
		SDL_RenderCopy(renderer, Tile, NULL, &_Blocks[i]);
}

tetromino::~tetromino()
{
	SDL_DestroyTexture(Tile);
	Tile = NULL;
}

