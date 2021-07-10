#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"

#define PLAYER_SIZE 50.0f

typedef struct{
    float circle_r;
    Vector2 speed;
    Vector2 objective;
    Vector2 position;
    bool active;
    bool hooked;
} grapple_t;

typedef struct{
    grapple_t grapple;
    Rectangle rec;
    Vector2 speed;
    Vector2 position;
} player_t;

void player_update(player_t *player, Rectangle left_bank, Rectangle right_bank);
void player_draw(player_t *player);
void player_init(player_t *player);

#endif