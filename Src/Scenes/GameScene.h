#ifndef H_GAMESCENE_H
#define H_GAMESCENE_H

#include "cprocessing.h"
#include <stdio.h>
#include "../GameStateManager.h"
#include "../SpriteAnimation/spriteAnimation.h"

void game_init(void);
void game_update(void);
void game_exit(void);

unsigned char getEnemyState();

int mapOffset;

const game_map* getMap();

void engage_enemy(CP_Vector dir);

#endif