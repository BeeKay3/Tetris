#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include "../headers/board.h"
#include "../headers/GetTexture.h"
#include "../headers/Tetromino.h"

const int VERTICALSHIFT = 40, HORIZONTALSHIFT = 710;
int boardWidth, boardHeight;
std::fstream log;

Board::Board(SDL_Renderer *Renderer, int BLOCKSIZE)
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
    renderer = Renderer;
    baseTile = GetTexture(renderer, "./assets/img/block.png");
}

Board::~Board()
{
    log.close();
};

void Board::update()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &background);
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (valueGrid[i][j] != 0)
            {
                if (valueGrid[i][j] == 1)
                {
                    SDL_SetTextureColorMod(baseTile, 60, 248, 251);
                    SDL_RenderCopy(renderer, baseTile, NULL, &visibleGrid[i][j]);
                }
                else if (valueGrid[i][j] == 2)
                {
                    SDL_SetTextureColorMod(baseTile, 255, 204, 0);
                    SDL_RenderCopy(renderer, baseTile, NULL, &visibleGrid[i][j]);
                }
                else if (valueGrid[i][j] == 3)
                {
                    SDL_SetTextureColorMod(baseTile, 231, 9, 212);
                    SDL_RenderCopy(renderer, baseTile, NULL, &visibleGrid[i][j]);
                }
                else if (valueGrid[i][j] == 4)
                {
                    SDL_SetTextureColorMod(baseTile, 7, 106, 182);
                    SDL_RenderCopy(renderer, baseTile, NULL, &visibleGrid[i][j]);
                }
                else if (valueGrid[i][j] == 5)
                {
                    SDL_SetTextureColorMod(baseTile, 236, 159, 5);
                    SDL_RenderCopy(renderer, baseTile, NULL, &visibleGrid[i][j]);
                }
                else if (valueGrid[i][j] == 6)
                {
                    SDL_SetTextureColorMod(baseTile, 168, 233, 28);
                    SDL_RenderCopy(renderer, baseTile, NULL, &visibleGrid[i][j]);
                }
                else if (valueGrid[i][j] == 7)
                {
                    SDL_SetTextureColorMod(baseTile, 246, 3, 3);
                    SDL_RenderCopy(renderer, baseTile, NULL, &visibleGrid[i][j]);
                }
            }
        }
    }
}

void Board::updateLog()
{
    log << std::endl;
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            log << valueGrid[i][j] << " ";
        }
        log << std::endl;
    }
}

bool Board::collisionGround(SDL_Rect piece[4])
{
    for (int i = 0; i < 4; i++)
    {
        if (piece[i].y >= 990)
            return true;
    }
    return false;
}

bool Board::outOfLeftBounds(SDL_Rect piece[4])
{
    for (int i = 0; i < 4; i++)
    {
        if (piece[i].x <= 710)
        {
            return true;
        }
    }
    return false;
}

bool Board::outOfRightBounds(SDL_Rect piece[4])
{
    for (int i = 0; i < 4; i++)
    {
        if (piece[i].x >= 1160)
        {
            return true;
        }
    }
    return false;
}

bool Board::collisionBlocks(SDL_Rect piece[4])
{
    for (int i = 0; i < 4; i++)
    {
        size_t x = (piece[i].x - 710) / 50;
        size_t y = (piece[i].y - 40) / 50;
        if (valueGrid[y][x] != 0)
        {
            return true;
        }
    }
    return false;
}

void Board::insert(SDL_Rect piece[4], shape color, bool *dead)
{
    for (int i = 0; i < 4; i++)
    {
        if (piece[i].y <= 40)
        {
            *dead = true;
        }
        size_t x = (piece[i].x - 710) / 50;
        size_t y = (piece[i].y - 40) / 50;
        valueGrid[y][x] = color + 1;
    }
}

int Board::lineClear()
{
    int num = 0;
    for (int i = 19; i > 0; i--)
    {
        if (valueGrid[i][0] != 0 && valueGrid[i][1] != 0 && valueGrid[i][2] != 0 && valueGrid[i][3] != 0 && valueGrid[i][4] != 0 && valueGrid[i][5] != 0 && valueGrid[i][6] != 0 && valueGrid[i][7] != 0 && valueGrid[i][8] != 0 && valueGrid[i][9] != 0)
        {
            if (num == 0)
            {
                update();
                SDL_RenderPresent(renderer);
                SDL_Delay(200);
            }
            num++;
            for (int k = i; k > 0; k--)
            {
                for (int j = 0; j < 10; j++)
                {
                    valueGrid[k][j] = valueGrid[k - 1][j];
                }
            }
            i++;
        }
    }
    return num;
}