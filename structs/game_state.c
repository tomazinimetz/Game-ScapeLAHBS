#include "player.c"
#include "./SDL2/SDL.h"
#include "robot.c"

typedef struct
{
    Player player;
    Robot robots[10];
    SDL_Texture *robot_texture;
    SDL_Texture *player_textures[3];
    SDL_Renderer *renderer;
} GameState;
