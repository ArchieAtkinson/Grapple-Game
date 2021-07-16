#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

#include "raylib.h"

#include "physac.h"

extern Camera2D camera;
extern int score; 

extern struct timeval current_time[2];
extern int loop_time;
#define SCREEN_WIDTH 1920   
#define SCREEN_HEIGHT 1080

#define GRAVITY 1.0f

#define GRAPPLE_SPEED 25.0f

#define VEC2_ADD(v1, v2) (Vector2){v1.x + v2.x, v1.y + v2.y}
#define VEC2_SUB(v1, v2) (Vector2){v1.x - v2.x, v1.y - v2.y}
#define VEC2_MUL(v1, v2) (Vector2){v1.x * v2.x, v1.y * v2.y}
#define VEC2_DIV(v1, v2) (Vector2){v1.x / v2.x, v1.y / v2.y}

Rectangle body_to_rec(PhysicsBody body);
void init();
int ran_int_range(int lower, int upper);
Vector2 world_to_screen(Vector2 world);
Rectangle centre_to_rec(Vector2 centre, float width, float height);

#endif