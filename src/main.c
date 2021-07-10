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
#include "overlay.h"
#include "background.h"
#include "camera.h"

Rectangle left_bank;
Rectangle right_bank;
Camera2D camera;
player_t player;
Vector2 mouse_postion;

void update(){

    background_update(&player, &left_bank, &right_bank);
    player_update(&player, left_bank, right_bank);
    overlay_update(&mouse_postion);
    camera_update(&camera, &player);
}


void draw_2dmode(){
    
    player_draw(&player);
    
}

void draw_standard(){
    overlay_draw(&mouse_postion);

    DrawText(TextFormat("camera: x:%f y:%f", camera.target.x, camera.target.y), 5, 0, 20, BLACK);
    DrawText(TextFormat("player: x:%f y:%f",player.position.x, player.position.y), 5, 20, 20, BLACK);
    DrawText(TextFormat("Mouse: x:%f y:%f", mouse_postion.x, mouse_postion.y), 5, 40, 20, BLACK);
    DrawText(TextFormat("Grapple Objective: x:%f y:%f",player.grapple.objective.x, player.grapple.objective.y), 5, 60, 20, BLACK);
    DrawText(TextFormat("Grapple Positoin: x:%f y:%f",player.grapple.position.x, player.grapple.position.y), 5, 80, 20, BLACK);
}

void draw(){
    BeginDrawing();


    BeginMode2D(camera);

    background_draw(&left_bank, &right_bank);
    draw_2dmode();
    EndMode2D();

    draw_standard();

    EndDrawing();
}


int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [textures] example - background scrolling");
    SetWindowPosition(1800, 0);
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second


    background_init(&left_bank, &right_bank);
    player_init(&player);
    camera_init(&camera, &player);
    overlay_init();


    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        update();

        draw();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}





