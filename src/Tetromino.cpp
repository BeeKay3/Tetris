#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <time.h>
#include "../headers/Tetromino.h"
#include "../headers/GetTexture.h"

Tetromino::Tetromino(SDL_Renderer *Renderer, int b, SDL_Texture *Base)
{
	BLOCKSIZE = b;
	BaseTile = Base;
	renderer = Renderer;
}

void Tetromino::update(SDL_Point p, shape s)
{
	ShapeVal = s;
	Tile = BaseTile;
	Center = p;
	if (ShapeVal == O_Shape)
	{
		Blocks[0] = {Center.x, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[1] = {Center.x + BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[2] = {Center.x + BLOCKSIZE, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		Blocks[3] = {Center.x, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		SDL_SetTextureColorMod(Tile, 255, 204, 0);
	}

	else if (ShapeVal == T_Shape)
	{
		Blocks[0] = {Center.x, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		Blocks[1] = {Center.x, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[2] = {Center.x + BLOCKSIZE, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		Blocks[3] = {Center.x - BLOCKSIZE, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		SDL_SetTextureColorMod(Tile, 231, 9, 212);
	}

	else if (ShapeVal == J_Shape)
	{
		Blocks[0] = {Center.x, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		Blocks[1] = {Center.x + BLOCKSIZE, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		Blocks[2] = {Center.x - BLOCKSIZE, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		Blocks[3] = {Center.x - BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
		SDL_SetTextureColorMod(Tile, 7, 106, 182);
	}

	else if (ShapeVal == L_Shape)
	{
		Blocks[0] = {Center.x, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		Blocks[1] = {Center.x + BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[2] = {Center.x + BLOCKSIZE, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		Blocks[3] = {Center.x - BLOCKSIZE, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		SDL_SetTextureColorMod(Tile, 236, 159, 5);
	}

	else if (ShapeVal == S_Shape)
	{
		Blocks[0] = {Center.x, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[1] = {Center.x + BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[2] = {Center.x, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		Blocks[3] = {Center.x - BLOCKSIZE, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		SDL_SetTextureColorMod(Tile, 168, 233, 28);
	}

	else if (ShapeVal == Z_Shape)
	{
		Blocks[0] = {Center.x, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[1] = {Center.x + BLOCKSIZE, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		Blocks[2] = {Center.x, Center.y + BLOCKSIZE, BLOCKSIZE, BLOCKSIZE};
		Blocks[3] = {Center.x - BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
		SDL_SetTextureColorMod(Tile, 246, 3, 3);
	}

	else if (ShapeVal == I_Shape)
	{
		Blocks[0] = {Center.x + BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[1] = {Center.x, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[2] = {Center.x - BLOCKSIZE, Center.y, BLOCKSIZE, BLOCKSIZE};
		Blocks[3] = {Center.x - (2 * BLOCKSIZE), Center.y, BLOCKSIZE, BLOCKSIZE};
		SDL_SetTextureColorMod(Tile, 60, 248, 251);
	}
}

void Tetromino::update(SDL_Point p)
{
	int x1 = p.x, y1 = p.y;
	x1 -= Center.x;
	y1 -= Center.y;
	for (int i = 0; i <= 3; i++)
	{
		Blocks[i].x += x1;
		Blocks[i].y += y1;
	}
	Center = p;
}

void Tetromino::rotate()
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
		for (int i = 0; i <= 3; i++)
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

void Tetromino::render()
{
	for (int i = 0; i <= 3; i++)
		SDL_RenderCopy(renderer, Tile, NULL, &Blocks[i]);
}

void Tetromino::getBlocks(SDL_Rect Arr[4])
{
	for (int i = 0; i <= 3; i++)
		Arr[i] = Blocks[i];
}

shape Tetromino::random()
{
	srand(time(0));
	int i = rand() % 8;
	if (i == 0)
		return I_Shape;
	else if (i == 1)
		return O_Shape;
	else if (i == 2)
		return T_Shape;
	else if (i == 3)
		return J_Shape;
	else if (i == 4)
		return L_Shape;
	else if (i == 5)
		return S_Shape;
	else
		return Z_Shape;
}

Tetromino::~Tetromino()
{
	SDL_DestroyTexture(Tile);
	Tile = NULL;
}
