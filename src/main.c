/*******************************************************************************************
*
*   raylib [textures] example - Background scrolling
*
*   This example has been created using raylib 2.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2019 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
#include "common.h"
#include "player.h"
#include "background.h"
#include "objects.h"
#define PHYSAC_IMPLEMENTATION
#define PHYSAC_DEBUG
#include "physac.h"
#include <sys/time.h>

struct timeval current_time[2];
player_t player;
Camera2D camera = { 0 };
int score;
int loop_time;

void update(){
    UpdatePhysics();    
    camera.target.x = player.body->position.x;
    background_update(&player);  
    player_update(&player);
    objects_update(&player);
}


void draw(){
    BeginDrawing();

    BeginMode2D(camera);

    background_draw();

    objects_draw();

    player_draw(&player);

    EndMode2D();
    
    DrawCircleV(GetMousePosition(), 3, RED);

    DrawText(TextFormat("Score: %d ", score), SCREEN_WIDTH - 250, 2 , 30, DARKBLUE);

    DrawText(TextFormat("FPS: %d ",GetFPS()), 5, 0, 10, GOLD);
    DrawText(TextFormat("player: x:%f y:%f", player.body->position.x, player.body->position.y), 5, 10, 10, GOLD);
    DrawText(TextFormat("Mouse_Screen: x:%f y:%f", GetMousePosition().x, GetMousePosition().y), 5, 20, 10, GOLD);
    DrawText(TextFormat("Grapple Objective: x:%f y:%f", player.grapple.objective.x, player.grapple.objective.y), 5, 30, 10, GOLD);
    DrawText(TextFormat("Grapple Position: x:%f y:%f", player.grapple.hook->position.x, player.grapple.hook->position.y), 5, 40, 10, GOLD);
    DrawText(TextFormat("Camera Target: x:%f y:%f", camera.target.x, camera.target.y), 5, 50, 10, GOLD);
    DrawText(TextFormat("Camera Offset: x:%f y:%f", camera.offset.x, camera.offset.y), 5, 60, 10, GOLD);
    DrawText(TextFormat("Camera Combined: x:%f y:%f", camera.target.x + camera.offset.x, camera.target.y + camera.offset.y), 5, 70, 10, GOLD);
    DrawText(TextFormat("Loop Time: %dus", loop_time), 5, 80, 10, GOLD);

    EndDrawing();
}

void init(){
    ClosePhysics();
    SetPhysicsGravity(0.0f, GRAVITY);
    InitPhysics();

    background_init();
    player_init(&player);
    objects_init();

    score = 0;

    camera.target.x = player.body->position.x;
    camera.target.y = 0;
    // camera.offset = (Vector2){ SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f };
    camera.offset = (Vector2){SCREEN_WIDTH/5.0f,0};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

}

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Grapple Game");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    init();

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {

        if (IsKeyPressed(KEY_R)){
            init();
        }
        gettimeofday(&current_time[0], NULL);
        update();


        draw();
        gettimeofday(&current_time[1], NULL);
        loop_time = current_time[1].tv_usec  - current_time[0].tv_usec;
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    ClosePhysics();
    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}





