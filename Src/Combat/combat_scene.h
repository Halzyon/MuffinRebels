/*-------------------------------------------------------------------------------------

	File: combat_scene.h
	Project: 1401 Game Project - Game Name: DiceRebels
	Authors: Foong Jun Wei (f.junwei@digipen.edu)

	All content � 2022 DigiPen Institute of Technology Singapore, all rights reserved

---------------------------------------------------------------------------------------*/

#ifndef COMBAT_SCENE_H
#define COMBAT_SCENE_H

#include <cprocessing.h>
#include "combatHandler.h"
//#include "../Character/gameChar.h"
//#include "../Character/gameEnemy.h"


void combat_scene_init();
void combat_scene_update();
void combat_scene_exit();

void start_combat_scene();

void battleEnd();
CP_BOOL getCombatState();

CP_Vector getEnemyPos();

void beginTransition();
#endif // !COMBAT_SCENE_H
