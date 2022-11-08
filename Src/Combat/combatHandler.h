#ifndef COMBAT_HANDLER_H
#define COMBAT_HANDLER_H
#include "../GameObject/gameObject.h"
#include "../Character/gameChar.h"


GameObject* priority_go; //priority will always be counted as attacking while the combat while defend
GameObject* defending_go;
int combatants_present;

/*!
 * @brief declares the combatants for the combat function to work. 
 *		  Combat function has checker to make sure that combatants are declared
 * @param priority GameObject pointer pointing to the GO that is attacking (priority)
 * @param defendant GameObject pointer pointing to the GO that is defending
*/
void declare_combatants(GameObject* const priority, GameObject* const defendant);

/*!
 * @brief Single-turn combat function. To be called as many times as the GO has energy
 * @param void
 * @return integer of whether the combat phase went ok
*/
int combat_phase(void);


#endif // !COMBAT_HANDLER_H
