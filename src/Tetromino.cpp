#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../headers/Tetromino.h"
#include "../headers/GetTexture.h"

tetromino::tetromino(SDL_Point p, shape ShapeVal, int BLOCKSIZE, SDL_Texture *BaseTile)
{
	Center = p;
	Tile = BaseTile;
	if (ShapeVal == O_Shape)
	{
		Blocks[0] = {Center.x, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[1] = {Center.x + BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[2] = {Center.x + BLOCKSIZE, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		Blocks[3] = {Center.x, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		SDL_SetTextureColorMod(Tile, 255, 255, 0);
	}
	else if (ShapeVal == T_Shape)
	{
		Blocks[0] = {Center.x, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[1] = {Center.x, Center.y - BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		Blocks[2] = {Center.x + BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[3] = {Center.x - BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
		SDL_SetTextureColorMod(Tile, 150, 0, 255);
	}
	else if (ShapeVal == J_Shape)
	{
		Blocks[0] = {Center.x, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[1] = {Center.x + BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[2] = {Center.x - BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[3] = {Center.x - BLOCKSIZE, Center.y - BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		SDL_SetTextureColorMod(Tile, 0, 0, 255);
	}
	else if (ShapeVal == L_Shape)
	{
		Blocks[0] = {Center.x, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[1] = {Center.x + BLOCKSIZE, Center.y - BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		Blocks[2] = {Center.x + BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[3] = {Center.x - BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
		SDL_SetTextureColorMod(Tile, 255, 150, 0);
	}
	else if (ShapeVal == S_Shape)
	{
		Blocks[0] = {Center.x, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[1] = {Center.x + BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[2] = {Center.x, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		Blocks[3] = {Center.x - BLOCKSIZE, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		SDL_SetTextureColorMod(Tile, 50, 255, 0);
	}
	else if (ShapeVal == Z_Shape)
	{
		Blocks[0] = {Center.x, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[1] = {Center.x + BLOCKSIZE, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		Blocks[2] = {Center.x, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		Blocks[3] = {Center.x - BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
		SDL_SetTextureColorMod(Tile, 255, 0, 0);
	}
	else if (ShapeVal == I_Shape)
	{
		Blocks[0] = {Center.x + BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[1] = {Center.x, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[2] = {Center.x - BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[3] = {Center.x - (2 * BLOCKSIZE), Center.y, BLOCKSIZE, BLOCKSIZE};
		SDL_SetTextureColorMod(Tile, 0, 190, 255);
	}
}

void tetromino::Render(SDL_Renderer *Renderer)
{
	for (int i = 0; i <= 3; i++)
		SDL_RenderCopy(Renderer, Tile, NULL, &Blocks[i]);
}

tetromino::~tetromino()
{
	SDL_DestroyTexture(Tile);
	Tile = NULL;
}

