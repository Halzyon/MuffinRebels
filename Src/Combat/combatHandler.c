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

	return 0;
}
