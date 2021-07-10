#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "player.h"

#define BANK_WIDTH 50

void background_update(player_t *player, Rectangle *left_bank, Rectangle *right_bank);
void background_draw(Rectangle *left_bank, Rectangle *right_bank);
void background_init(Rectangle *left_bank, Rectangle *right_bank);

#endif