#ifndef combat_handler_h
#define combat_handler_h
#include "../GameObject/gameObject.h"


GameObject* priority_go; //priority will always be counted as attacking while the combat while defend

GameObject* defending_go;

int combatants_present;

void declare_combatants(GameObject* const priority, GameObject* const defendant);

int combat_phase(void);


#endif // !combat_handler_h
