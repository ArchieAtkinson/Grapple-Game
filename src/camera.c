#include "common.h"
#include "camera.h"
#include "player.h"

void camera_init(Camera2D *camera, player_t *player){
    camera->rotation = 0.0f;
    camera->zoom = 1.0f;

    camera->offset = (Vector2){ SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f };
    camera->target = (Vector2){player->position.x, SCREEN_HEIGHT/2};
}

void camera_update(Camera2D *camera, player_t *player){
    camera->target.y = player->position.y;

    if (camera->target.y > SCREEN_HEIGHT/2){
        camera->target.y = SCREEN_HEIGHT/2;
    }
}