#include "common.h"
#include "background.h"

Texture2D cloud_texture[2];

void background_init(Rectangle *left_bank, Rectangle *right_bank){
    cloud_texture[0] = LoadTexture("resources/cloud1.png");
    cloud_texture[1] = LoadTexture("resources/cloud2.png");

    Rectangle left_bank_temp = {
        .x = 0,
        .y = -SCREEN_HEIGHT,
        .width = BANK_WIDTH,
        .height = SCREEN_HEIGHT*2.0f,
    };

    Rectangle right_bank_temp = {
        .x = SCREEN_WIDTH - BANK_WIDTH,
        .y = -SCREEN_HEIGHT,
        .width = BANK_WIDTH,
        .height = SCREEN_HEIGHT*2.0f,
    };

    *left_bank = left_bank_temp;
    *right_bank = right_bank_temp; 
}

void background_draw(Rectangle *left_bank, Rectangle *right_bank){
    ClearBackground(SKYBLUE);

    DrawRectangleGradientV(0, -SCREEN_HEIGHT, SCREEN_WIDTH/2 , SCREEN_HEIGHT*2, YELLOW, BLUE);
    DrawRectangle(SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2 , SCREEN_HEIGHT, BLUE);
    DrawRectangle(SCREEN_WIDTH/2, -SCREEN_HEIGHT, SCREEN_WIDTH/2 , SCREEN_HEIGHT, YELLOW);
    
    DrawRectangleRec(*left_bank, DARKGREEN);
    DrawRectangleRec(*right_bank, DARKGREEN);

}

void background_update(player_t *player, Rectangle *left_bank, Rectangle *right_bank){
    left_bank->y = player->position.y - SCREEN_HEIGHT;
    right_bank->y = player->position.y - SCREEN_HEIGHT;
}