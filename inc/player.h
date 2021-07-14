#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"

#define PLAYER_SIZE 50.0f

typedef enum{
    SHORT_ROPE = 25,
    MID_ROPE = 150,
    LONG_ROPE = 300,
}rope_len_t;

typedef struct{
    PhysicsBody hook;
    Vector2 speed;
    Vector2 objective;
    bool active;
    bool hooked;
} grapple_t;


typedef struct{
    grapple_t grapple;
    PhysicsBody body;
    Vector2 speed;
} player_t;

extern player_t player;
extern rope_len_t selected_rope;
extern rope_len_t current_rope;

void player_update();
void player_draw();
void player_init();

#endif