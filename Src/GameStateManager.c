/*-------------------------------------------------------------------------------------

	File: GameStateManager.c
	Project: 1401 Game Project - Game Name: DiceRebels
	Author: Muhammad Hazim Bin Gazali (m.bingazali@digipen.edu)

	All content ? 2021 DigiPen Institute of Technology Singapore, all rights reserved

---------------------------------------------------------------------------------------*/


#include "GameStateManager.h"
#include "yijia/settings_ui.h"
#include "yijia/overworld_ui.h"
#include"yijia/pause_ui.h"
#include "yijia/mainmenu.h"
#include "yijia/credits.h"
#include "yijia/tutorial.h"
#include "yijia/gameOver.h"


CP_Sound bgm;

void GameStateAddScene(SCENES scn, FunctionPtr init, FunctionPtr update, FunctionPtr exit)
{
	Scene* scne = (Scene*)malloc(sizeof(scn) + sizeof(init) + sizeof(update) + sizeof(exit));
	if (scne != NULL)
	{
		scne->scne = scn;
		scne->fnc[0] = init;
		scne->fnc[1] = update;
		scne->fnc[2] = exit;
		if (!gsm.Scenes.array)
			initArray(&gsm.Scenes, 1);	
		insertArray(&gsm.Scenes, *scne);

		LOG("SCENE %d HAVE BEEN ADDED\n", scn);
	}
	else
		LOG("SCENE %d HAVE NOT BEEN ADDED\n", scn);

}
void GameStateSetNextScene(SCENES scne)
{
	Scene* temp = NULL;
	bool foundScene = false;
	for (int i = 0; i < gsm.Scenes.used; ++i)
	{
		if ((gsm.Scenes.array + i)->scne == scne)
		{
			temp = (gsm.Scenes.array + i);
			foundScene = true;
			break;
		}
	}
	if (foundScene)
	{
		LOG("SETTING %d NEXT SCENE\n", scne);
		if(temp)
		CP_Engine_SetNextGameState(*temp->fnc[0], *temp->fnc[1], *temp->fnc[2]);
	}
	else
		LOG("FOUND NO SCENE\n");
}

void GameStateSetNextSubScene(SCENES scne, bool forced)
{
	Scene* temp;
	bool foundScene = false;
	for (int i = 0; i < gsm.Scenes.used; ++i)
	{
		if ((gsm.Scenes.array + i)->scne == scne)
		{
			temp = (gsm.Scenes.array + i);
			if(!forced)
			if (gsm.b_subScene)
				gsm.m_subScene->fnc[2];
			CP_Engine_SetPostUpdateFunction(temp->fnc[1]);
			gsm.b_subScene = true;
			gsm.m_subScene = temp;
			foundScene = true;
			break;

		}
	}
		if (foundScene)
		{
			LOG("SETTING NEXT SUB SCENE %d\n", scne);
				if(!forced)
				if(gsm.m_subScene->fnc[0])
					gsm.m_subScene->fnc[0]();
		}
		else
			LOG("FOUND NO SUB SCENE %d\n",scne);
}


void initArray(SceneArray* a, size_t initialSize) {

	a->array = malloc(initialSize * sizeof(Scene));
	a->used = 0;
	a->size = initialSize;
	
}

void insertArray(SceneArray* a, Scene element) {
	// a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
	// Therefore a->used can go up to a->size 
	if (a->used == a->size) {
		a->size *= 2;
		a->array = realloc(a->array, a->size * sizeof(Scene));
	} 
	a->array[a->used++] = element;
}

void freeArray(SceneArray* a) {
	free(a->array);
	a->array = NULL;
	a->used = a->size = 0;
}

void GameStateRun(void)
{
	
	
	gsm.b_subScene = false;
	GameStateAddScene(SPLASHSCREEN_SCENE, splash_screen_init, splash_screen_update, splash_screen_exit);
	//GameStateAddScene(SPLASHSCREEN_SCENE, editor_init, editor_update, editor_exit);
	GameStateAddScene(SPRITEANIMATION_SCENE, SpriteScene_init, SpriteScene_update, SpriteScene_exit);
	GameStateAddScene(COMBAT_OVERLAY_SCENE, combat_overlay_init, combat_overlay_update, combat_overlay_exit);	//GameStateAddScene(SPLASHSCREEN_SCENE, splash_screen_init, splash_screen_update, splash_screen_exit);
	GameStateAddScene(SETTINGS_SCENE, settings_init, settings_update, settings_shutdown);
	GameStateAddScene(OVERWORLD_UI_SCENE, overworld_init, overworld_update, overworld_shutdown);
	GameStateAddScene(PAUSE_SCENE, gamepaused_init, gamepaused_update, gamepaused_shutdown);
	GameStateAddScene(MAINMENU_SCENE, mainmenu_init, mainmenu_update, mainmenu_exit);
	GameStateAddScene(CREDITS_SCENE, credits_init, credits_update, credits_exit);
	GameStateAddScene(GAME_SCENE, game_init, game_update, game_exit);
	GameStateAddScene(BATTLE_SCENE, combat_scene_init, combat_scene_update, combat_scene_exit);
	GameStateAddScene(BATTLE_SCENE_UI, second_init, second_update, second_exit); // @TODO add this later
	GameStateAddScene(MAX_SCENE, NULL, NULL, NULL);
	GameStateAddScene(TUTORIAL_SCENE, tutorial_init, tutorial_update, tutorial_exit);// @TODO add this later 
	GameStateAddScene(GAMEOVER_SCENE, gameTransition_init, gameTransition_update, gameTransition_shutdown);

	//set first scene
	GameStateSetNextScene(SPLASHSCREEN_SCENE);

	CP_Engine_Run();


	freeArray(&gsm.Scenes);
}

void ManualUpdate(SCENES scne)
{
	for (int i = 0; i < gsm.Scenes.used; ++i)
	{
		if (gsm.Scenes.array[i].scne != scne)
			continue;

		gsm.Scenes.array[i].fnc[1]();

	}
}

CP_Sound *getBGM()
{
	return &bgm;
}
