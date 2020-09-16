#include <stdio.h>
#include "./SDL2/SDL.h"
#include "./SDL2/SDL_image.h"
#include "structs/game_state.c"
#include "assets/assets.c"

void loadPlayerSurface(Assets assets, GameState *game)
{
    SDL_Surface *player_surface = NULL;

    for (size_t i = 0; i < 3; i++)
    {
        if (i == 0)
            player_surface = IMG_Load(assets.player_walk1);

        if (i == 1)
            player_surface = IMG_Load(assets.player_walk2);

        if (i == 2)
            player_surface = IMG_Load(assets.player_walk3);

        if (player_surface == NULL)
        {
            printf("IMG_Load: %s\n", IMG_GetError());
            SDL_Quit();
            exit(1);
        }

        game->player_textures[i] = SDL_CreateTextureFromSurface(game->renderer, player_surface);
        SDL_FreeSurface(player_surface);
    }
}

void loadRobotSurface(Assets assets, GameState *game)
{
    SDL_Surface *robot_surface = NULL;
    robot_surface = IMG_Load(assets.robot_enemy);
    if (robot_surface == NULL)
    {
        printf("IMG_Load: %s\n", IMG_GetError());
        SDL_Quit();
        exit(1);
    }

    game->robot_texture = SDL_CreateTextureFromSurface(game->renderer, robot_surface);
    SDL_FreeSurface(robot_surface);
}

void loadGroundSurface(Assets assets, GameState *game)
{
    SDL_Surface *ground = NULL;
    ground = IMG_Load(assets.ground);
    if (ground == NULL)
    {
        printf("IMG_Load: %s\n", IMG_GetError());
        SDL_Quit();
        exit(1);
    }

    game->robot_texture = SDL_CreateTextureFromSurface(game->renderer, ground);
    SDL_FreeSurface(ground);
}

void loadGame(GameState *game)
{
    Assets assets = Assets_default;

    loadRobotSurface(assets, game);
    loadPlayerSurface(assets, game);
    loadGroundSurface(assets, game);

    game->player.y_position = 320 - 40;
    game->player.x_position = 240 - 40;

    for (size_t i = 0; i < 10; i++)
    {
        game->robots[i].x_position = random() % 640;
        game->robots[i].y_position = random() % 480;
    }
}

void renderScreen(SDL_Renderer *renderer, GameState *game)
{
    //set the drawing color to blue
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    SDL_RenderClear(renderer);

    //set the drawing color to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Rect playerRect = {game->player.x_position, game->player.y_position, 50, 50};
    SDL_RenderCopyEx(renderer, game->player_textures[0], NULL, &playerRect, 0, NULL, 0);

    for (size_t i = 0; i < 10; i++)
    {
        SDL_Rect robotRect = {game->robots[i].x_position, game->robots[i].y_position, 64, 64};
        SDL_RenderCopy(renderer, game->robot_texture, NULL, &robotRect);
    }

    //We are done drawing, "present" or show to the screen what we've drawn
    SDL_RenderPresent(renderer);
}

int processEvent(SDL_Window *window)
{
    SDL_Event event;
    short done = 0;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_WINDOWEVENT_CLOSE:
        {
            if (window)
            {
                SDL_DestroyWindow(window);
                window = NULL;
                done = 1;
            }
        }
        break;
        case SDL_KEYDOWN:
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                done = 1;
                break;
            }
        }
        break;
        case SDL_QUIT:
            done = 1;
            break;
        }
    }

    return done;
}

void destroyGame(SDL_Window *window, SDL_Renderer *renderer, GameState gameState)
{
    SDL_DestroyTexture(gameState.robot_texture);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

int main(int argc, char *argv[])
{
    GameState gameState;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("IMG_Load: %s\n", IMG_GetError());
    }

    window = SDL_CreateWindow("Game Window",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              640,
                              480,
                              0);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    gameState.renderer = renderer;
    loadGame(&gameState);

    short done = 0;
    while (!done)
    {
        done = processEvent(window);
        movePlayer(&(gameState.player));
        renderScreen(renderer, &gameState);
    }

    destroyGame(window, renderer, gameState);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
