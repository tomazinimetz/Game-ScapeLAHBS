struct Assets_s
{
    char robot_enemy[30];
    char ground[30];

    //Player walk assets
    char player_walk1[30];
    char player_walk2[30];
    char player_walk3[30];

} Assets_default = {"./assets/robots/robot.png",
                    "./assets/ground/ground.png",
                    "./assets/player/walk1.png",
                    "./assets/player/walk2.png",
                    "./assets/player/walk3.png"};

typedef struct Assets_s Assets;