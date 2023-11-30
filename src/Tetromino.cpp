#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../headers/Tetromino.h"
#include "../headers/GetTexture.h"

tetromino::tetromino(int b, SDL_Texture *Base)
{
	BLOCKSIZE = b;
	BaseTile = Base;
}

void tetromino::Update(SDL_Point p, shape s)
{
	ShapeVal = s;
	Tile = BaseTile;
	if (ShapeVal == O_Shape)
		SDL_SetTextureColorMod(Tile, 255, 255, 0);

	else if (ShapeVal == T_Shape)
		SDL_SetTextureColorMod(Tile, 150, 0, 255);

	else if (ShapeVal == J_Shape)
		SDL_SetTextureColorMod(Tile, 0, 0, 255);

	else if (ShapeVal == L_Shape)
		SDL_SetTextureColorMod(Tile, 255, 150, 0);

	else if (ShapeVal == S_Shape)
		SDL_SetTextureColorMod(Tile, 50, 255, 0);

	else if (ShapeVal == Z_Shape)
		SDL_SetTextureColorMod(Tile, 255, 0, 0);

	else if (ShapeVal == I_Shape)
		SDL_SetTextureColorMod(Tile, 0, 190, 255);

	Update(p);
}

void tetromino::Update(SDL_Point p)
{
	Center = p;
	if (ShapeVal == O_Shape)
	{
		Blocks[0] = {Center.x, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[1] = {Center.x + BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[2] = {Center.x + BLOCKSIZE, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		Blocks[3] = {Center.x, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
	}

	else if (ShapeVal == T_Shape)
	{
		Blocks[0] = {Center.x, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[1] = {Center.x, Center.y - BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		Blocks[2] = {Center.x + BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[3] = {Center.x - BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
	}

	else if (ShapeVal == J_Shape)
	{
		Blocks[0] = {Center.x, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[1] = {Center.x + BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[2] = {Center.x - BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[3] = {Center.x - BLOCKSIZE, Center.y - BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
	}

	else if (ShapeVal == L_Shape)
	{
		Blocks[0] = {Center.x, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[1] = {Center.x + BLOCKSIZE, Center.y - BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		Blocks[2] = {Center.x + BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[3] = {Center.x - BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
	}

	else if (ShapeVal == S_Shape)
	{
		Blocks[0] = {Center.x, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[1] = {Center.x + BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[2] = {Center.x, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		Blocks[3] = {Center.x - BLOCKSIZE, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
	}

	else if (ShapeVal == Z_Shape)
	{
		Blocks[0] = {Center.x, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[1] = {Center.x + BLOCKSIZE, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		Blocks[2] = {Center.x, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		Blocks[3] = {Center.x - BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
	}

	else if (ShapeVal == I_Shape)
	{
		Blocks[0] = {Center.x + BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[1] = {Center.x, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[2] = {Center.x - BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[3] = {Center.x - (2 * BLOCKSIZE), Center.y, BLOCKSIZE, BLOCKSIZE};
	}
}

void tetromino::Rotate()
{
	if (ShapeVal != O_Shape)
	{
		SDL_Point RotationCenter = Center;
		if (ShapeVal == I_Shape)
		{
			RotationCenter.x -= BLOCKSIZE / 2;
			RotationCenter.y -= BLOCKSIZE / 2;
		}
		int temp;
		for( int i = 0; i <=3; i++)
		{
			Blocks[i].x -= RotationCenter.x;
			Blocks[i].y -= RotationCenter.y; 
			temp = Blocks[i].x;
			Blocks[i].x = -Blocks[i].y;
			Blocks[i].y = temp;
			Blocks[i].x += RotationCenter.x;
			Blocks[i].y += RotationCenter.y; 
		}
	}
}

void tetromino::Render(SDL_Renderer *Renderer)
{
	for (int i = 0; i <= 3; i++)
		SDL_RenderCopy(Renderer, Tile, NULL, &Blocks[i]);
}

void tetromino::GetBlocks(SDL_Rect *Arr)
{
	for (int i = 0; i <= 3; i++)
		*(Arr+i) = Blocks[i];
}
tetromino::~tetromino()
{
	SDL_DestroyTexture(Tile);
	Tile = NULL;
}

