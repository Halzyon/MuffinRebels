#include "combatHandler.h"
#include "../Character/diceHandler.h"
#include "../Character/gameEnemy.h"
#include "../UI/CombatOverlayUI/second_combat.h"
#include "../Items/itemHandler.h"

void declare_combatants(Enemy* const enemy, int enemy_combat_mode)
{
	if (combatants_present)
		return;

	printf("Combat declared, \n");
	//enemy combat mode tells me what mode the player should be in
	the_enemy = enemy;

	switch (the_enemy->enemyState)
	{
		case ATTACK_STATE:
			get_character()->combat_mode = CHAR_DEFENDING;
			if (get_character()->dice_size - 1 <= the_enemy->dice_size)
			{
				max_combat_size = get_character()->dice_size - 1;
			}
			else
				max_combat_size = the_enemy->dice_size;
			break;
		case DEFEND_STATE:
			get_character()->combat_mode = CHAR_ATTACKING;
			if (the_enemy->dice_size - 1 <= get_character()->dice_size)
			{
				max_combat_size = the_enemy->dice_size - 1;
			}
			else
				max_combat_size = get_character()->dice_size;
			break;
		default:
			break;
	}

	if (max_combat_size <= 0)
		max_combat_size = 1;
	
	combatants_present = 1;

	attacker_sum = 0;
	defender_sum = 0;
}

int combat_phase(void)
{
	//if combatants have not been set and/or you have changed combatants, always init;
	if (combatants_present)
	{
		// TODO: implement pseudo code
		// attackers roll for max dice
		// roll + sum
		// defenders take total number of dice - 1
		// roll + sum
		// decrease health of difference of whoever is lower

		// ALT MECHANICS
		// each player choses which dice they want to roll from their list
		// then compare the values of the dice you roll and take away the health
		// then go on to the next dice until someone got no more dice
		// then restart until someone dies

		if (attacker_sum != 0 && defender_sum != 0)
		{
			//damage
			if (attacker_sum > defender_sum) //attacker damage delt
			{
				if (get_character()->combat_mode == CHAR_ATTACKING)
				{
					if (current_powerup == LEATHER_SKIN)
						the_enemy->hp -= (attacker_sum - defender_sum);
					else
					{
						the_enemy->hp -= (attacker_sum - defender_sum) + get_character()->modifier;
						--get_character()->mod_duration;
					}
				}
				else if (the_enemy->enemyState == ATTACK_STATE)
				{
					if (get_character()->modifier > 0 && current_powerup == LEATHER_SKIN)
					{
						get_character()->modifier -= (attacker_sum - defender_sum);
						--get_character()->mod_duration;
					}
					else
						get_character()->hp -= (attacker_sum - defender_sum);
				}
			}
			else if (attacker_sum < defender_sum) //defender damage delt
			{
				if (get_character()->combat_mode == CHAR_ATTACKING)
				{
					if (get_character()->modifier > 0 && current_powerup == LEATHER_SKIN)
					{
						get_character()->modifier += (attacker_sum - defender_sum);
						--get_character()->mod_duration;
					}
					else
						get_character()->hp += (attacker_sum - defender_sum);
				}
				else if (the_enemy->enemyState == ATTACK_STATE)
				{
					if (current_powerup == LEATHER_SKIN)
						the_enemy->hp += (attacker_sum - defender_sum);
					else
					{
						the_enemy->hp += (attacker_sum - defender_sum) + get_character()->modifier;
						--get_character()->mod_duration;
					}
				}
				
			}
			//else it will be a perfect parry

			//reset state
			combatants_present = 0;

			get_character()->combat_mode = CHAR_NONE;


			return 0;
		}

		if (get_character()->mod_duration <= 0 || (current_powerup == LEATHER_SKIN && get_character()->modifier <= 0))
		{
			reset_modifier();
		}
	}

	return 1;
}
