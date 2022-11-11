#ifndef GAME_ENEMY_H
#define GAME_ENEMY_H
#include "cprocessing.h"

#include "../SpriteAnimation/spriteAnimation.h"
#include "../Character/diceHandler.h"

#define MAX_DICE 5


typedef struct 
{
	Sprite* sp;

	int hp;
	int energy;
	unsigned int dice_size;
	unsigned char enemyState;
	bool b_direction;
	unsigned int movement;
	unsigned int patrolRange;
	int steps;

} Enemy;

typedef enum
{
	PATROL_UPDOWN_STATE,
	PATROL_LEFTRIGHT_STATE,
	ATTACK_STATE,
	DEFEND_STATE,
	MAX_ENEMY_STATE
}ENEMY_STATE;

void UpdateEnemy(Enemy* en, float dt, bool move);

void UpdateCombat(Enemy* en, float dt);

void ChangeState(Enemy* en, ENEMY_STATE state);

Enemy* CreateEnemy(void);
void FreeEnemy(Enemy*);

#endif // !GAME_ENEMY_H
