#ifndef SECOND_COMBAT_H
#define SECOND_COMBAT_H

#include "cprocessing.h"
#include "../../Character/diceHandler.h"
#include "combat_overlay.h"

void second_init(void);

void second_init_dicePos(void);

void second_init_rollPos(void);

void second_update(void);

void second_dice_powerup(int* rng_num, int num_dice[], int powerup_turns);

void second_choose_to_roll_dice(int* num_roll, int num_dice[]);

void generate_dice(int num_roll, asset dice, float dice_posX, float dice_posY, float scale);

void health_bar(int remaining_hp);

void inventory_window(int num_item, float position_X);

void second_exit(void);


#endif //!SECOND_COMBAT_H