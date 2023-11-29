#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

enum shape
{
	I_Shape,
	O_Shape,
	T_Shape,
	J_Shape,
	L_Shape,
	S_Shape,
	Z_Shape
};

class tetromino
{
public:
	tetromino(SDL_Point p, shape ShapeVal, int BLOCKSIZE, SDL_Texture *BaseTile);
	~tetromino();
	void Render(SDL_Renderer *Renderer);

private:
	SDL_Rect Blocks[4];
	SDL_Point Center;
	SDL_Texture *Tile;
};

