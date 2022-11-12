#include "combatHandler.h"
#include "../Character/diceHandler.h"
#include "../Character/gameEnemy.h"
void declare_combatants(Enemy* const enemy, int enemy_combat_mode)
{
	//enemy combat mode tells me what mode the player should be in
	the_enemy = enemy;

	switch (the_enemy->enemyState)
	{
		case ATTACK_STATE:
			get_character()->combat_mode = CHAR_DEFENDING;
			break;
		case DEFEND_STATE:
			get_character()->combat_mode = CHAR_ATTACKING;
			break;
		default:
			break;
	}
	
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
	else if (the_enemy->enemyState == ATTACK_STATE)
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
	else if (the_enemy->enemyState == DEFEND_STATE)
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
		else if (the_enemy->enemyState == ATTACK_STATE)
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
		else if (the_enemy->enemyState == ATTACK_STATE)
		{
			the_enemy->hp += (attacker_sum - defender_sum);
		}
	}
	//else it will be a perfect parry

	//reset states
	get_character()->combat_mode = CHAR_NONE;
	the_enemy->enemyState = PATROL_LEFTRIGHT_STATE;
	
	combatants_present = 0;
	return 0;
}
