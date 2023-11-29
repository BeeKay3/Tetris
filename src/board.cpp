#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include "../headers/board.h"
#include "../headers/GetTexture.h"

const int VERTICALSHIFT = 40, HORIZONTALSHIFT = 710;
int boardWidth, boardHeight;
std::fstream log;

Board::Board(SDL_Renderer *renderer, int BLOCKSIZE)
{
    std::fstream init_state;

    init_state.open("./game_states/initial_state.txt", std::ios::in);

    if (!init_state.is_open())
    {
        std::cout << "error opening file" << std::endl;
    }
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            init_state >> valueGrid[i][j];
            visibleGrid[i][j] = {HORIZONTALSHIFT + (j * BLOCKSIZE), VERTICALSHIFT + (i * BLOCKSIZE), BLOCKSIZE, BLOCKSIZE};
            if (init_state.eof())
            {
                break;
            }
        }
        if (init_state.eof())
        {
            break;
        }
    }
    init_state.close();

    time_t t = time(0);
    tm *now = localtime(&t);
    std::string file_name = "./game_states/" + std::to_string(now->tm_year + 1900) + std::to_string(now->tm_mon + 1) + std::to_string(now->tm_mday) + std::to_string(now->tm_hour) + std::to_string(now->tm_min) + ".txt";
    log.open(file_name, std::ios::out);
    log << "Game played on " << now->tm_year + 1900 << "/" << now->tm_mon + 1 << "/" << now->tm_mday << " " << now->tm_hour << ":" << now->tm_min << std::endl;

    boardHeight = BLOCKSIZE * 20;
    boardWidth = BLOCKSIZE * 10;
    background = {HORIZONTALSHIFT, VERTICALSHIFT, boardWidth, boardHeight};
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &background);

    SDL_Texture *baseTile = GetTexture(renderer, "./assets/img/block.png");
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            log << valueGrid[i][j] << " ";
            if (valueGrid[i][j] != 0)
            {
                SDL_SetTextureColorMod(baseTile, 255, 255, 0);
                SDL_RenderCopy(renderer, baseTile, NULL, &visibleGrid[i][j]);
            }
        }
        log << std::endl;
    }
    SDL_RenderPresent(renderer);
}
Board::~Board()
{
    log.close();
};