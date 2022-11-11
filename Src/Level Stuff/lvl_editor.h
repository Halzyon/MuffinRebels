/*!
 @file lvl_editor.h
 @author Foong Jun Wei (f.junwei)
 @course 
 @section 
 @tutorial 
 @date 2022-10-24
 @brief 
*//*______________________________________________________________________*/

#ifndef LVL_EDITOR_H
#define LVL_EDITOR_H

#include "lvl_manager.h"
#include "../Character/gameMap.h"

void editor_init(void);
void editor_update(void);
void editor_exit(void);

void loadSprites(void);

CP_Image level_sprites[NUM_TYPES_TILE];

#endif // LVL_EDITOR_H
