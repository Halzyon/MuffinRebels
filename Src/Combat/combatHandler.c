#include "combatHandler.h"
#include "../Character/diceHandler.h"

void declare_combatants(GameObject* const priority, GameObject* const defendant)
{
	priority_go->this_character = NULL;
	priority_go->this_enemy = NULL;

	defending_go->this_character = NULL;
	defending_go->this_enemy = NULL;

	//TODO: deep copy
	priority_go = &priority;
	defending_go = &defendant;
	
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

	if (priority_go->this_character != NULL)
	{
		for (int i = 0; i < priority_go->this_character->dice_size; ++i)
		{
			attacker_sum += roll_dice(priority_go->this_character->dice[i]);
		}
	}
	else if (priority_go->this_enemy != NULL)
	{
		for (int i = 0; i < priority_go->this_enemy->dice_size; ++i)
		{
			attacker_sum += roll_dice(priority_go->this_enemy->dice[i]);
		}
	}

	if (defending_go->this_character != NULL)
	{
		for (int i = 0; i < defending_go->this_character->dice_size - 1; ++i)
		{
			attacker_sum += roll_dice(defending_go->this_character->dice[i]);
		}
	}
	else if (defending_go->this_enemy != NULL)
	{
		for (int i = 0; i < defending_go->this_enemy->dice_size - 1; ++i)
		{
			attacker_sum += roll_dice(defending_go->this_enemy->dice[i]);
		}
	}
	
	combatants_present = 0;
	return 0;
}
