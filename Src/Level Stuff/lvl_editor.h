/*-------------------------------------------------------------------------------------

	File: lvl_editor.h
	Project: 1401 Game Project - Game Name: DiceRebels
	Authors: Foong Jun Wei (f.junwei@digipen.edu)

	All content � 2022 DigiPen Institute of Technology Singapore, all rights reserved

---------------------------------------------------------------------------------------*/

#ifndef LVL_EDITOR_H
#define LVL_EDITOR_H

#include "lvl_manager.h"
#include "../Character/gameMap.h"

void editor_init(void);
void editor_update(void);
void editor_exit(void);

//void loadSprites(void);

CP_Image level_sprites[NUM_TYPES_TILE];

#endif // LVL_EDITOR_H
