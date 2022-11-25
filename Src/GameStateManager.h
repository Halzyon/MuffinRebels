#ifndef H_GAMESTATEMANAGER_H
#define H_GAMESTATEMANAGER_H

#include <stdlib.h>
#include "cprocessing.h"
#include <stdbool.h>
#include <stdio.h>
#include "SplashScreen/splashscreen.h"
#include "GameObject/gameObject.h"
#include "SpriteAnimation/SpriteScene.h"
#include "Scenes/GameScene.h"
#include "UI/CombatOverlayUI/combat_overlay.h"
#include "Level Stuff/lvl_editor.h"
#include "Combat/combat_scene.h"
#include "UI/CombatOverlayUI/second_combat.h"

CP_Sound *bgm;

#ifdef _DEBUG
#define LOG(ERROR_MSG, ...)  (fprintf(stderr, ERROR_MSG, ##__VA_ARGS__));
#else
#define LOG(ERROR_MSG, ...) 0
#endif


typedef enum
{
	SPLASHSCREEN_SCENE,
	SPRITEANIMATION_SCENE,
	WORLD_OVERLAY_SCENE,
	COMBAT_OVERLAY_SCENE,
	OVERWORLD_UI_SCENE,
	BATTLE_SCENE,
	BATTLE_SCENE_UI,
	MAINMENU_SCENE,
	SETTINGS_SCENE,
	CREDITS_SCENE,
	PAUSE_SCENE,
	GAME_SCENE,
	TUTORIAL_SCENE,
	MAX_SCENE
} SCENES;
typedef struct {
	UINT8 scne;
	FunctionPtr fnc[3];

}Scene;

typedef struct {
	Scene* array;
	UINT8 used;
	UINT8 size;
} SceneArray;

void initArray(SceneArray* a, size_t initialSize);

void insertArray(SceneArray* a, Scene element);

void freeArray(SceneArray* a);

struct GameStateManager
{
	SceneArray Scenes;
	Scene* m_currScene;
	Scene* m_subScene;
	
	bool b_subScene;
	bool init_subScene;
};
static struct GameStateManager gsm;

void GameStateRun(void);
void ManualUpdate(SCENES scne);
void GameStateAddScene(SCENES scne, FunctionPtr init, FunctionPtr update, FunctionPtr exit);
void GameStateSetNextScene(SCENES scne);

void GameStateSetNextSubScene(SCENES scne,bool forced);



#endif // !