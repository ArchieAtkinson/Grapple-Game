#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"

#define PLAYER_SIZE 40.0f

typedef enum{
    IN_AIR,
    HOOKED,
    WAITING,
}hook_state_t;

typedef struct{
    PhysicsBody hook;
    Vector2 speed;
    Vector2 objective;
    hook_state_t state;
} grapple_t;

typedef struct{
    grapple_t grapple;
    PhysicsBody body;
    Vector2 speed;
} player_t;

extern player_t player;

void player_update();
void player_draw();
void player_init();

#endif