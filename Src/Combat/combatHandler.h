#ifndef COMBAT_HANDLER_H
#define COMBAT_HANDLER_H

#include "../Character/gameChar.h"
#include "../Character/gameEnemy.h"

Enemy* the_enemy;
int combatants_present;

/*!
 * @brief declares the combatants for the combat function to work. 
 *		  Combat function has checker to make sure that combatants are declared
 * @param priority GameObject pointer pointing to the GO that is attacking (priority)
 * @param defendant GameObject pointer pointing to the GO that is defending
*/
void declare_combatants(Enemy* const enemy, int enemy_combat_mode);

/*!
 * @brief Single-turn combat function. To be called as many times as the GO has energy
 * @param void
 * @return integer of whether the combat phase went ok
*/
int combat_phase(void);


#endif // !COMBAT_HANDLER_H
