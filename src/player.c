#include "player.h"

#define START_POS_X SCREEN_WIDTH/2.0f
#define START_POS_Y SCREEN_HEIGHT - PLAYER_SIZE/2.0f


void player_init(player_t *player){
    player->position = (Vector2){START_POS_X, START_POS_Y};

    player->grapple.speed = (Vector2){ 0, 0 };
    player->grapple.position = (Vector2){ 0, 0 };
    player->grapple.active = false;
    player->grapple.hooked = false;
}


void player_draw(player_t *player){
    DrawRectangleRec(player->rec, PINK);

    if (player->grapple.active || player->grapple.hooked){
        DrawLine(player->position.x, player->position.y, player->grapple.position.x, player->grapple.position.y, BLACK);
        DrawCircle(player->grapple.position.x, player->grapple.position.y, 3, GOLD);
    }
}

void player_update(player_t *player, Rectangle left_bank, Rectangle right_bank){
    Vector2 top_left = centre_to_top_left(player->position, (Vector2){PLAYER_SIZE, PLAYER_SIZE});
    Rectangle temp = {
    .x = top_left.x,
    .y = top_left.y,
    .width = PLAYER_SIZE,
    .height = PLAYER_SIZE,
    };
    player->rec = temp;

    float module, sideX, sideY, distance;
    grapple_t *grapple = &(player->grapple);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && grapple->active == false){
        grapple->position = player->position;
        grapple->objective = GetMousePosition();
        grapple->active = true;
        grapple->hooked = false;

        // Calculate speed
        module = sqrt( pow(grapple->objective.x - grapple->position.x, 2) +
                       pow(grapple->objective.y -  grapple->position.y, 2));

        sideX = (grapple->objective.x - grapple->position.x)*GRAPPLE_SPEED/module;
        sideY = (grapple->objective.y - grapple->position.y)*GRAPPLE_SPEED/module;

        grapple->speed = (Vector2){ sideX, sideY };
    }
    if (grapple->active)
    {
        // Update position
        grapple->position.x += grapple->speed.x;
        grapple->position.y += grapple->speed.y;

        // Distance to objective
        distance = sqrt( pow(grapple->position.x - grapple->objective.x, 2) +
                            pow(grapple->position.y - grapple->objective.y, 2));

        if(CheckCollisionCircleRec(grapple->position, 3, left_bank) || CheckCollisionCircleRec(grapple->position, 3, right_bank)){
            grapple->hooked = true;
            grapple->active = false;
        }

        if (distance < GRAPPLE_SPEED)
        {
            // Interceptor dissapears
            grapple->active = false;

        }
    }
    if (grapple->hooked){
        // Update position
            distance = sqrt( pow(grapple->position.x - player->position.x, 2) +
                            pow(grapple->position.y -  player->position.y, 2));

        if (distance < GRAPPLE_SPEED){
            grapple->hooked = false;
        }
        player->position.x += grapple->speed.x;
        player->position.y += grapple->speed.y;
    }
}