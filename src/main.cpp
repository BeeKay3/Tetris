#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

using namespace std;

const int _SCREENWIDTH = 1920, _SCREENHEIGHT = 1080, _BLOCKSIZE = 100;
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

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *BaseTile = NULL;

class tetromino
{
public:
	tetromino(SDL_Point p, shape ShapeVal);
	~tetromino();
	void Render();

private:
	SDL_Rect _Blocks[4];
	SDL_Point _Center;
	SDL_Texture *Tile;
};

bool _INIT()
{
	bool key = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL could not be initialized, error : " << SDL_GetError() << endl;
		key = false;
	}
	else
	{
		window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _SCREENWIDTH, _SCREENHEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
		if (window == NULL)
		{
			cout << "Window could not be created, error : " << SDL_GetError() << endl;
			key = false;
		}
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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

SDL_Texture *GetTexture(string path)
{
	SDL_Texture *newTexture = NULL;
	SDL_Surface *loadSurface = IMG_Load(path.c_str());
	if (loadSurface == NULL)
		cout << "Image could not be loaded, error : " << IMG_GetError() << endl;
	else
	{
		newTexture = SDL_CreateTextureFromSurface(renderer, loadSurface);
		if (newTexture == NULL)
			cout << "Texture could not be created, error : " << SDL_GetError() << endl;
		SDL_FreeSurface(loadSurface);
	}
	return newTexture;
}

void _CLOSE()
{
	SDL_DestroyTexture(BaseTile);
	BaseTile = NULL;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;
	SDL_Quit();
}

tetromino::tetromino(SDL_Point p, shape ShapeVal)
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

void tetromino::Render()
{
	for (int i = 0; i <= 3; i++)
		SDL_RenderCopy(renderer, Tile, NULL, &_Blocks[i]);
}

tetromino::~tetromino()
{
	SDL_DestroyTexture(Tile);
	Tile = NULL;
}

int main(int argc, char *args[])
{
	if (_INIT())
	{
		BaseTile = GetTexture("assets/img/block.png");
		SDL_Point p = {300, 300};
		tetromino a(p, _Z);

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		a.Render();
		SDL_RenderPresent(renderer);

		SDL_Event e;
		bool quit = false;
		while (quit == false)
			while (SDL_PollEvent(&e))
				if (e.type == SDL_QUIT)
					quit = true;
	}
	_CLOSE();
	return 0;
}
