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

class Tetromino
{
public:
	Tetromino(SDL_Renderer *Renderer, int b, SDL_Texture *Base);
	~Tetromino();
	void update(SDL_Point p, shape s, SDL_Rect piece[4]);
	void update(SDL_Point p, SDL_Rect piece[4]);
	void render();
	void rotate();
	void getBlocks(SDL_Rect Arr[4]);
	shape getShape();
	shape random();

private:
	shape ShapeVal;
	int BLOCKSIZE;
	SDL_Rect Blocks[4];
	SDL_Point Center;
	SDL_Texture *Tile;
	SDL_Texture *BaseTile;
	SDL_Renderer *renderer;
};
