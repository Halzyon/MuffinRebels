#include <stdlib.h>
#include <cprocessing.h>
#include "gameEnemy.h"
#include "gameChar.h"

void UpdateEnemy(Enemy* en, float dt, bool move)
{
	UpdateSprite(en->sp, dt);//update enemy spriteanimation
	if (!move)
		return;
	
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

}

void UpdateCombat(Enemy* en, float dt)
{
	en->energy = roll_dice(e_std_D6);
	printf("Enemy dice %d\n", en->energy);

	if (en->energy <= get_character()->energy)
	{//defend
		// currently heals it 0.0
		en->enemyState = DEFEND_STATE;
		en->hp += en->energy;
	}
	else
	{// attack
		en->enemyState = ATTACK_STATE;
		get_character()->hp -= en->energy;
	}

	en->hp -= get_character()->energy;

	//dont need change enemy state back to patrol as its either
	//player die or enemy die
}

Enemy* CreateEnemy(void)
{
	Enemy* newEnemy = malloc(sizeof(Enemy));

	if (newEnemy)
	{
		newEnemy->hp = 5;
		newEnemy->energy = 2;
		newEnemy->dice_size = 5;
		newEnemy->enemyState = PATROL_UPDOWN_STATE;
		newEnemy->b_direction = true;
		newEnemy->movement = 0;
		newEnemy->steps = 1;
		newEnemy->patrolRange = 3;

		newEnemy->sp = CreateSprite("Assets/ene.png", 4, 4, true, false);

		//sprite animation init
		newEnemy->sp->spriteStates[RIGHT] = 3;
		newEnemy->sp->spriteStates[BACKWARD] = 0;
		newEnemy->sp->spriteStates[LEFT] = 2;
		newEnemy->sp->spriteStates[FORWARD] = 1;
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