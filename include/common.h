#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <math.h>
#include "raylib.h"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 1200

#define GRAPPLE_SPEED 25.0f

#define VEC2_ADD(v1, v2) (Vector2){v1.x + v2.x, v1.y + v2.y}
#define VEC2_SUB(v1, v2) (Vector2){v1.x - v2.x, v1.y - v2.y}
#define VEC2_MUL(v1, v2) (Vector2){v1.x * v2.x, v1.y * v2.y}
#define VEC2_DIV(v1, v2) (Vector2){v1.x / v2.x, v1.y / v2.y}

Vector2 top_left_to_centre(Vector2 top_left, Vector2 size);
Vector2 centre_to_top_left(Vector2 centre, Vector2 size);

#endif