#ifndef H_GAMESCENE_H
#define H_GAMESCENE_H

#include "cprocessing.h"
#include <stdio.h>
#include "../GameStateManager.h"
#include "../SpriteAnimation/spriteAnimation.h"

#define MAP1_SIZE 15
#define MAP2_SIZE 20
#define MAP3_SIZE 30
#define NUM_MAPS 3

void game_init(void);
void game_update(void);
void game_exit(void);

unsigned char getEnemyState();

int mapOffset[NUM_MAPS];
char currLvl;

void setNextLvl(char next);

const game_map* getMap();

void engage_enemy(CP_Vector dir);

void setInitScene(bool b);
#endif