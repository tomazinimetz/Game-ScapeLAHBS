typedef struct
{
    int x_position, y_position;
    short life;
} Player;

void movePlayer(Player *player)
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_LEFT])
    {
        player->x_position -= 10;
    }
    if (state[SDL_SCANCODE_RIGHT])
    {
        player->x_position += 10;
    }
    if (state[SDL_SCANCODE_UP])
    {
        player->y_position -= 10;
    }
    if (state[SDL_SCANCODE_DOWN])
    {
        player->y_position += 10;
    }
}