#include "combatHandler.h"
#include "../Character/diceHandler.h"
#include "../Character/gameEnemy.h"
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
			max_combat_size = the_enemy->dice_size;
			break;
		case DEFEND_STATE:
			get_character()->combat_mode = CHAR_ATTACKING;
			max_combat_size = get_character()->dice_size;
			break;
		default:
			break;
	}
	
	combatants_present = 1;

	attacker_sum = 0;
	defender_sum = 0;

	def_max_size = max_combat_size - 1;
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

			printf("Your health: %d, enemy health: %d\n", get_character()->hp, the_enemy->hp);

			//reset state
			combatants_present = 0;

			get_character()->combat_mode = CHAR_NONE;


			return 0;
		}
	}

	return 1;
}
