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
	tetromino(int b, SDL_Texture *Base);
	~tetromino();
	void Update(SDL_Point p, shape s);
	void Update(SDL_Point p);
	void Render(SDL_Renderer *Renderer);
	void Rotate();
	void GetBlocks(SDL_Rect *Arr);

private:
	shape ShapeVal;
	int BLOCKSIZE;
	SDL_Rect Blocks[4];
	SDL_Point Center;
	SDL_Texture *Tile;
	SDL_Texture *BaseTile;
};

