#include "common.h"
#include "background.h"
#include "root_dir.h"

Texture2D background;
int pos[2];

void background_init(){
    background = LoadTexture(TextFormat("%s/%s",ROOT_DIR, "resources/space_bg_large.png"));
    pos[0] = 0;
    pos[1] = background.width;
}

void background_draw(){
    ClearBackground(WHITE);
    DrawTexture(background, 0, 0, WHITE);

    DrawTexture(background, pos[0], 0, WHITE);
    DrawTexture(background, pos[1], 0, WHITE);

}

void background_update(){
    int threshold_forward = pos[1] + 0.5f * background.width;
    if (threshold_forward < player.body->position.x){
        pos[0] = pos[1];
        pos[1] = pos[0] + background.width;
    }

    int threshold_backwards = pos[0] + 0.5f * background.width;
    if (threshold_backwards > player.body->position.x){
        pos[1] = pos[0];
        pos[0] = pos[1] - background.width;
    }
}