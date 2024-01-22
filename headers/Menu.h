#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

enum menuState {
  freshState,
  playState,
  pauseState,
  resumeState,
  restartState,
  quitState,
};

class Menu {
public:
  menuState mainMenu();
  void credits();
  void help();
  menuState pause();
  void death(std::string finalLevel, std::string finalScore,
             std::string lineClears);
  Menu(SDL_Renderer *Renderer);
  ~Menu();

private:
  SDL_Renderer *menuRenderer;
  TTF_Font *textFont, *writeFont;
  SDL_Texture *splash;
  SDL_Color textColor;
  menuState currentState;
};
