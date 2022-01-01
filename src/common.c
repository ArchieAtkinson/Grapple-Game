#include "common.h"
#include "raymath.h"


Rectangle body_to_rec(PhysicsBody body){
    Rectangle rec = {
    .x = GetPhysicsShapeVertex(body, 3).x,
    .y = GetPhysicsShapeVertex(body, 3).y,
    .width = Vector2Distance(GetPhysicsShapeVertex(body, 1), GetPhysicsShapeVertex(body, 2)),
    .height = Vector2Distance(GetPhysicsShapeVertex(body, 2), GetPhysicsShapeVertex(body, 3)),
    };
    return rec;
}   

int ran_int_range(int lower, int upper){
    return (rand() % (upper - lower + 1)) + lower;
}

Vector2 world_to_screen(Vector2 world){
    world.x = world.x - camera.target.x + camera.offset.x;
    return world;
}

Rectangle centre_to_rec(Vector2 centre, float width, float height){
    Rectangle rec = {
    .x = centre.x - width/2.0f,
    .y =  centre.y - height/2.0f,
    .width = width,
    .height = height,
    };
    return rec;    
}