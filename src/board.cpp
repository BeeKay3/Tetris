#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include "../headers/board.h"
#include "../headers/GetTexture.h"
#include "../headers/Tetromino.h"

Board::Board(SDL_Renderer *Renderer)
{
    BLOCKSIZE = 50;
    boardHeight = BLOCKSIZE * 20;
    boardWidth = BLOCKSIZE * 10;
    VERTICALSHIFT = 40;
    HORIZONTALSHIFT = 710;
    INITIAL_X = 910;
    INITIAL_Y = 40;
    background = {HORIZONTALSHIFT, VERTICALSHIFT, boardWidth, boardHeight};
    renderer = Renderer;
    baseTile = GetTexture(renderer, "./assets/img/block.png");
    tetrominoTile = GetTexture(renderer, "assets/img/block.png");
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
    game_state.open(file_name, std::ios::out);
    game_state << "Game played on " << now->tm_year + 1900 << "/" << now->tm_mon + 1 << "/" << now->tm_mday << " " << now->tm_hour << ":" << now->tm_min << std::endl;
}

Board::~Board()
{
    game_state.close();
};

void Board::game()
{
    SDL_Event e;
    bool quit = false;
    Uint64 currentTicks;
    const SDL_Point INITIAL_POS = {INITIAL_X, INITIAL_Y};
    SDL_Point pos = INITIAL_POS;
    SDL_Rect currentTetromino[4];

    Tetromino t(renderer, BLOCKSIZE, tetrominoTile);
    t.update(pos, t.random(), currentTetromino);

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
            else if (e.type == SDL_KEYDOWN)
            {
                if (e.key.keysym.sym == SDLK_SPACE)
                {
                    t.rotate(currentTetromino);
                    if (collisionBlocks(currentTetromino))
                    {
                        t.rotate(currentTetromino);
                        t.rotate(currentTetromino);
                        t.rotate(currentTetromino);
                    }
                }
                else if (e.key.keysym.sym == SDLK_z)
                {
                    t.update(INITIAL_POS, t.random(), currentTetromino);
                    pos = INITIAL_POS;
                }
                else if (e.key.keysym.sym == SDLK_LEFT)
                {
                    if (!outOfLeftBounds(currentTetromino))
                    {
                        pos.x -= 50;
                        t.update(pos, currentTetromino);
                        if (collisionBlocks(currentTetromino))
                        {
                            pos.x += 50;
                            t.update(pos, currentTetromino);
                        }
                    }
                }
                else if (e.key.keysym.sym == SDLK_RIGHT)
                {
                    if (!outOfRightBounds(currentTetromino))
                    {
                        pos.x += 50;
                        t.update(pos, currentTetromino);
                        if (collisionBlocks(currentTetromino))
                        {
                            pos.x -= 50;
                            t.update(pos, currentTetromino);
                        }
                    }
                }
                else if (e.key.keysym.sym == SDLK_DOWN)
                {
                    pos.y += BLOCKSIZE;
                    t.update(pos, currentTetromino);

                    if (collisionBlocks(currentTetromino))
                    {
                        pos.y -= BLOCKSIZE;
                        t.update(pos, currentTetromino);
                        insert(currentTetromino, t.getShape(), &quit);
                        lineClear();
                        updateLog();
                        t.update(INITIAL_POS, t.random(), currentTetromino);
                        pos = INITIAL_POS;
                    }
                }
                else if (e.key.keysym.sym == SDLK_UP)
                {
                    bool drop = true;
                    while (drop)
                    {
                        pos.y += BLOCKSIZE;
                        t.update(pos, currentTetromino);

                        if (collisionBlocks(currentTetromino))
                        {
                            pos.y -= BLOCKSIZE;
                            t.update(pos, currentTetromino);
                            insert(currentTetromino, t.getShape(), &quit);
                            lineClear();
                            updateLog();
                            t.update(INITIAL_POS, t.random(), currentTetromino);
                            pos = INITIAL_POS;
                            drop = false;
                        }
                        else if (collisionGround(currentTetromino))
                        {
                            insert(currentTetromino, t.getShape(), &quit);
                            lineClear();
                            updateLog();
                            t.update(INITIAL_POS, t.random(), currentTetromino);
                            pos = INITIAL_POS;
                            drop = false;
                        }
                    }
                }
            }
        }

        update();
        t.render();
        SDL_RenderPresent(renderer);

        if (SDL_GetTicks64() - currentTicks >= 1000)
        {
            currentTicks = SDL_GetTicks64();
            pos.y += BLOCKSIZE;
            t.update(pos, currentTetromino);

            if (collisionBlocks(currentTetromino))
            {
                pos.y -= BLOCKSIZE;
                t.update(pos, currentTetromino);
                insert(currentTetromino, t.getShape(), &quit);
                lineClear();
                updateLog();
                t.update(INITIAL_POS, t.random(), currentTetromino);
                pos = INITIAL_POS;
            }
            else if (collisionGround(currentTetromino))
            {
                insert(currentTetromino, t.getShape(), &quit);
                lineClear();
                updateLog();
                t.update(INITIAL_POS, t.random(), currentTetromino);
                pos = INITIAL_POS;
            }
        }

        if (quit == true)
        {
            TTF_Font *roboto;
            roboto = TTF_OpenFont("Roboto-Regular.ttf", 80);
            SDL_Surface *death_text = TTF_RenderText_Blended(roboto, "You Dead! :P", {255, 83, 112, 255});
            SDL_Texture *death_msg = SDL_CreateTextureFromSurface(renderer, death_text);
            SDL_Rect death_rect = {710, 300, death_text->w, death_text->h};
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, death_msg, NULL, &death_rect);
            SDL_RenderPresent(renderer);
            SDL_Delay(3000);
            SDL_FreeSurface(death_text);
            SDL_DestroyTexture(death_msg);
        }
    }
}

void Board::update()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
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
    game_state << std::endl;
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            game_state << valueGrid[i][j] << " ";
        }
        game_state << std::endl;
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