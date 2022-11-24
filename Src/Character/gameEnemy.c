#include <stdlib.h>
#include <cprocessing.h>
#include "gameEnemy.h"
#include "gameChar.h"
#include "../Combat/combatHandler.h"
#include "gameMap.h"

double wait_delta;
extern int enemykilled;
void UpdateEnemy(Enemy* en, float dt, bool move)
{
	if (!en->sp->go.isAlive)
		return;
	CP_Vector charPos = get_character()->sp->go.position;
	CP_Vector enemyPos = en->sp->go.position;

	if (en->enemyState == PATROL_UPDOWN_STATE)
	{
		if (!en->b_direction && charPos.y + 1 == enemyPos.y && charPos.x == enemyPos.x)
		{//player is on top of enemy and enemy is facing ontop
			en->b_combat = true;
			en->enemyState = ATTACK_STATE;

			if (!combatants_present)
				declare_combatants(en, en->enemyState);
		}
		else if (en->b_direction && charPos.y - 1 == enemyPos.y && charPos.x == enemyPos.x)
		{//player is on top of enemy and enemy is facing ontop
			en->b_combat = true;
			en->enemyState = ATTACK_STATE;
		}
	}
	else if (en->enemyState == PATROL_LEFTRIGHT_STATE)
	{
		if (!en->b_direction && charPos.y == enemyPos.y && charPos.x + 1 == enemyPos.x)
		{//player is on top of enemy and enemy is facing ontop
			en->b_combat = true;
		}
		else if (en->b_direction && charPos.y == enemyPos.y && charPos.x - 1 == enemyPos.x)
		{//player is on top of enemy and enemy is facing ontop
			en->b_combat = true;
		}
	}

	UpdateSprite(en->sp, dt);//update enemy spriteanimation
	if (!move || !en->sp->go.isAlive || en->b_combat || en->energy <= 0)
		return;

	if (wait_delta < 1.0)
	{
		wait_delta += dt * 2.0;
		return;
	}
	else
		wait_delta = 0.0;

	--en->energy;

	if (en->enemyState == PATROL_UPDOWN_STATE)
	{
		int steps = en->steps;

		if (en->b_direction)
		{
			steps = -steps;
			en->sp->renderMode = en->sp->spriteStates[FORWARD];
		}
		else
			en->sp->renderMode = en->sp->spriteStates[BACKWARD];

		en->sp->go.position.y += steps;

		++en->movement;
		if (en->movement >= en->patrolRange)
		{
			en->b_direction = !en->b_direction;
			en->movement = 0;
		}

	}
	else if (en->enemyState == PATROL_LEFTRIGHT_STATE)
	{
		int steps = en->steps;
		if (en->b_direction)
		{
			steps = -steps;
			en->sp->renderMode = en->sp->spriteStates[LEFT];
		}
		else
			en->sp->renderMode = en->sp->spriteStates[RIGHT];

		en->sp->go.position.x += steps;

		++en->movement;
		if (en->movement >= en->patrolRange)
		{
			en->b_direction = !en->b_direction;
			en->movement = 0;
		}
	}

	if (en->enemyState == PATROL_UPDOWN_STATE)
	{
		if (!en->b_direction && charPos.y + 1 == enemyPos.y && charPos.x == enemyPos.x)
		{//player is on top of enemy and enemy is facing ontop
			en->b_combat = true;
			en->enemyState = ATTACK_STATE;
			if (!combatants_present)
				declare_combatants(en, en->enemyState);
		}
		else if (en->b_direction && charPos.y - 1 == enemyPos.y && charPos.x == enemyPos.x)
		{//player is on top of enemy and enemy is facing ontop
			en->b_combat = true;
			en->enemyState = ATTACK_STATE;
		}
	}
	else if (en->enemyState == PATROL_LEFTRIGHT_STATE)
	{
		if (!en->b_direction && charPos.y == enemyPos.y && charPos.x + 1 == enemyPos.x)
		{//player is on top of enemy and enemy is facing ontop
			en->b_combat = true;
		}
		else if (en->b_direction && charPos.y == enemyPos.y && charPos.x - 1 == enemyPos.x)
		{//player is on top of enemy and enemy is facing ontop
			en->b_combat = true;
		}
	}
	
}

void UpdateCombat(Enemy* en, float dt)
{
	if (!en->b_combat || !en->sp->go.isAlive)
		return;

	declare_combatants(en, en->enemyState);

	//dont need change enemy state back to patrol as its either
	//player die or enemy die
	if (en->hp <= 0)
	{
		en->sp->go.isAlive = false;
		++enemykilled;
		combatants_present = 0;
	}
}

Enemy* CreateEnemy(void)
{
	Enemy* newEnemy = malloc(sizeof(Enemy));

	if (newEnemy)
	{
		newEnemy->hp = 5;
		newEnemy->energy = 8;
		newEnemy->dice[0] = e_std_D6;
		newEnemy->dice_size = 1; //number of usable dice

		for (int i = 1; i < MAX_DICE; ++i)
		{
			newEnemy->dice[i] = -1;
		}
		newEnemy->enemyState = PATROL_UPDOWN_STATE;
		newEnemy->b_direction = true;
		newEnemy->movement = 0;
		newEnemy->steps = 1;
		newEnemy->patrolRange = 3;

		newEnemy->sp = CreateSprite("Assets/ene.png", 4, 4, true, false);
		newEnemy->b_combat = false;

		//sprite animation init
		newEnemy->sp->spriteStates[RIGHT] = 2;
		newEnemy->sp->spriteStates[BACKWARD] = 1;
		newEnemy->sp->spriteStates[LEFT] = 3;
		newEnemy->sp->spriteStates[FORWARD] = 0;
	}
	return newEnemy;
}

void ChangeState(Enemy* en, ENEMY_STATE state)
{
	en->enemyState = state;
	en->movement = 0;
	en->b_direction = true;
}

void FreeEnemy(Enemy* en)
{
	
	CP_Image_Free(en->sp->go.image);
	free(en->sp);
	free(en);
}