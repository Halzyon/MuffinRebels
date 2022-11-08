#include "combatHandler.h"
#include "../Character/diceHandler.h"

void declare_combatants(GameObject* const priority, GameObject* const defendant)
{
	priority_go = &priority;
	defending_go = &defendant;
	
	combatants_present = 1;
}

int combat_phase(void)
{
	//if combatants have not been set and/or you have changed combatants, always init;
	if (!combatants_present)
		return 1;

	// attackers roll for max dice
	// roll + sum
	// defenders take total number of dice - 1
	// roll + sum
	// decrease health of difference of whoever is lower
	
	combatants_present = 0;
	return 0;
}
