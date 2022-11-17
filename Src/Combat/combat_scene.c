#include "combat_scene.h"
#include "../GameStateManager.h"

CP_BOOL isInit = false;

CP_BOOL transitionEnd = false;
CP_Image transition_img;
CP_Vector transitionPos;
CP_Vector transitionSize;

CP_BOOL sceneSet = false;

CP_Image player; // @TODO need to find stuff for it
CP_Vector playerPos;
CP_Vector targetPlayerPos;

CP_Image enemy; // @TODO need to find stuff for it
CP_Vector enemyPos;
CP_Vector targetEnemyPos;

CP_BOOL battleOver = false;

void move_to(CP_Vector* curr, CP_Vector dst);

const double speedowagon = 1500.0; // transition speed
const double speedowagon2 = 1500.0;

#ifndef _MSC_VER // for linux/all other compilers and apparently release mode
#define FILEPATH "Assets/"
#endif

#ifdef _MSC_VER // for visual studios/microsoft compiler
#pragma warning(disable : 4996) // microsoft wants you to use their fopen_s but it is not portable at all
//and not really taht much safer lol
#define FILEPATH "Assets/"
#define _CRTDBG_MAP_ALLOC
#endif       



void combat_scene_init()
{

	//do stuff
	// load images!
	transition_img = CP_Image_Load(FILEPATH "transition.png");
	transitionSize.x = CP_Image_GetWidth(transition_img);
	transitionSize.y = CP_Image_GetHeight(transition_img);
	transitionPos.x = 0;
	transitionPos.y = 0;

	playerPos = CP_Vector_Set(CP_System_GetWindowWidth() + 100, CP_System_GetWindowHeight() - CP_System_GetWindowHeight() / 5);
	enemyPos = CP_Vector_Set(-100.f ,0.f);

	targetPlayerPos = CP_Vector_Set(CP_System_GetWindowWidth() / 5, CP_System_GetWindowHeight() - CP_System_GetWindowHeight() / 5);
	targetEnemyPos = CP_Vector_Set(CP_System_GetWindowWidth() - CP_System_GetWindowWidth() / 5, 0.f);

	transitionEnd = false;
	sceneSet = false;
	battleOver = false;
	isInit = true;
}

void combat_scene_update()
{
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	if (!battleOver)
	{
		if (!transitionEnd)
		{
			transitionPos.x -= speedowagon * CP_System_GetDt();

			// continue doing the transition
			CP_Image_Draw(transition_img, transitionPos.x, transitionPos.y, transitionSize.x, transitionSize.y, 255);
			if (transitionPos.x <= -transitionSize.x)
			{
				transitionEnd = true;
			}
		}
		else
		{
			if (!sceneSet)
			{
				if (!CP_Vector_Distance(playerPos, targetPlayerPos) && !CP_Vector_Distance(enemyPos, targetEnemyPos))
				{
					sceneSet = true;
				}
				else
				{
					move_to(&playerPos, targetPlayerPos);
					move_to(&enemyPos, targetEnemyPos);
				}
			}
			else
			{
				// combat logic?
				// draw combat UI?
			}
			// do other combat stuff
			CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
			CP_Graphics_DrawRect(playerPos.x, playerPos.y, 100, 200);

			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
			CP_Graphics_DrawRect(enemyPos.x, enemyPos.y, 100, 200);
		}
	}
	else
	{
		if (!transitionEnd)
		{
			// move the transition thing back onto screen
			transitionPos.x += speedowagon * CP_System_GetDt();

			// continue doing the transition
			CP_Image_Draw(transition_img, transitionPos.x, transitionPos.y, transitionSize.x, transitionSize.y, 255);
			if (transitionPos.x >= 0)
			{
				transitionEnd = true;
			}
		}
		else if (!sceneSet)
		{
			// move away 
			transitionPos.x -= speedowagon * CP_System_GetDt();

			// continue doing the transition
			CP_Image_Draw(transition_img, transitionPos.x, transitionPos.y, transitionSize.x, transitionSize.y, 255);
			if (transitionPos.x <= -transitionSize.x)
			{
				sceneSet = true;
			}
		}
	}
	//if (getCombatState())
	//{
	//	combat_scene_exit();
	//}
}

void combat_scene_exit()
{
	CP_Image_Free(transition_img);
}

void start_combat_scene()
{
	if (!isInit)
	{
		combat_scene_init();
	}
}

void move_to(CP_Vector* curr, CP_Vector dst)
{
	if (CP_Vector_Distance(*curr, dst) <= 100.f)
	{
		curr->x = dst.x;
		curr->y = dst.y;
	}
	else
	{
		double dt = CP_System_GetDt();
		CP_Vector dir = CP_Vector_Normalize(CP_Vector_Set(dst.x - curr->x, dst.y - curr->y));
		curr->x += dir.x * speedowagon2 * dt;
		curr->y += dir.y * speedowagon2 * dt;
	}
}

void battleEnd()
{
	battleOver = true;
	sceneSet = false;
	transitionEnd = false;

	combatants_present = 0;
}

CP_BOOL getCombatState()
{
	return battleOver;
}