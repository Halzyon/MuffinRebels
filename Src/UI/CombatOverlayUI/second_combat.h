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

void bottom_display(int player_roll, int enemy_roll);

void generate_dice(int num_roll, dice_types dice_rolled, float dice_posX, float dice_posY, float scale);

void enemy_ui(CP_Vector position, dice_types enemy_dice, int enemys_roll, float enemy_dice_scale);

void cut_in();

void health_bar(int remaining_hp);

void enemy_health_bar(int enemy_hp, CP_Vector position);

void inventory_window(int num_item, float position_X);

void second_exit(void);


#endif //!SECOND_COMBAT_H