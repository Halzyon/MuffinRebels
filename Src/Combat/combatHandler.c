#include "combatHandler.h"
#include "../Character/diceHandler.h"

void declare_combatants(Enemy* const enemy, int enemy_combat_mode)
{
	//enemy combat mode tells me what mode the player should be in
	the_enemy = &enemy;

	get_character()->combat_mode = !enemy_combat_mode; //if 0 - attacking, if 1 - defending;
	
	combatants_present = 1;
}

int combat_phase(void)
{
	//if combatants have not been set and/or you have changed combatants, always init;
	if (!combatants_present)
		return 1;

	// TODO: implement pseudo code
	// attackers roll for max dice
	// roll + sum
	// defenders take total number of dice - 1
	// roll + sum
	// decrease health of difference of whoever is lower

	int attacker_sum = 0;
	int defender_sum = 0;

	if (get_character()->combat_mode == CHAR_ATTACKING)
	{
		for (int i = 0; i < get_character()->dice_size; ++i)
		{
			attacker_sum += roll_dice(get_character()->dice[i]);
		}
	}
	else if (the_enemy->combat_mode == ENEMY_ATTACKING)
	{
		for (int i = 0; i < the_enemy->dice_size; ++i)
		{
			attacker_sum += roll_dice(the_enemy->dice[i]);
		}
	}
	else if (get_character()->combat_mode == CHAR_DEFENDING)
	{
		//the -1 in size while defending can be changed next time
		for (int i = 0; i < get_character()->dice_size - 1; ++i)
		{
			defender_sum += roll_dice(get_character()->dice[i]);
		}
	}
	else if (the_enemy->combat_mode == ENEMY_DEFENDING)
	{
		for (int i = 0; i < the_enemy->dice_size - 1; ++i)
		{
			defender_sum += roll_dice(the_enemy->dice[i]);
		}
	}

	if (attacker_sum > defender_sum) //attacker damage delt
	{
		if (get_character()->combat_mode == CHAR_ATTACKING)
		{
			the_enemy->hp -= (attacker_sum - defender_sum);
		}
		else if (the_enemy->combat_mode == ENEMY_ATTACKING)
		{
			get_character()->hp -= (attacker_sum - defender_sum);
		}
	}
	else if (attacker_sum < defender_sum) //defender damage delt
	{
		if (get_character()->combat_mode == CHAR_ATTACKING)
		{
			get_character()->hp += (attacker_sum - defender_sum);
		}
		else if (the_enemy->combat_mode == ENEMY_ATTACKING)
		{
			the_enemy->hp += (attacker_sum - defender_sum);
		}
	}
	//else it will be a perfect parry

	get_character()->combat_mode = CHAR_NONE;
	the_enemy->combat_mode = CHAR_NONE;
	
	combatants_present = 0;
	return 0;
}
