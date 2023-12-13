#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

SDL_Texture *GetTexture(SDL_Renderer *, std::string);
SDL_Texture *GetTexture(SDL_Renderer *, TTF_Font *, std::string, SDL_Color, SDL_Rect *textBox);
