#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include "../headers/board.h"

Board::Board(SDL_Renderer *renderer, int BLOCKSIZE)
{
    background = {710, 40, 500, 1000};
    std::fstream init_state;

    init_state.open("./game_states/initial_state.txt", std::ios::in);

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            init_state >> grid[i][j];
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

    std::fstream log;
    time_t t = time(0);
    tm *now = localtime(&t);
    // year mon mday hour min
    std::string file_name = "./game_states/" + std::to_string(now->tm_year + 1900) + std::to_string(now->tm_mon + 1) + std::to_string(now->tm_mday) + std::to_string(now->tm_hour) + std::to_string(now->tm_min) + ".txt";
    log.open(file_name, std::ios::out);
    log << "Game played on " << now->tm_year + 1900 << "/" << now->tm_mon + 1 << "/" << now->tm_mday << " " << now->tm_hour << ":" << now->tm_min << "\n";
    log.close();

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &background);
    SDL_RenderPresent(renderer);
}
Board::~Board(){};