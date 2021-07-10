#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"
#include "player.h"


void camera_init(Camera2D *camera, player_t *player);
void camera_update(Camera2D *camera, player_t *player);

#endif