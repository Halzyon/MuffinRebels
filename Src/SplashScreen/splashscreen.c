/*-------------------------------------------------------------------------------------

	File: splashscreen.c
	Project: 1401 Game Project - Game Name: DiceRebels
	Author: Muhammad Hazim Bin Gazali (m.bingazali@digipen.edu)
			Foong Jun Wei (f.junwei@digipen.edu)

	All content ? 2022 DigiPen Institute of Technology Singapore, all rights reserved

---------------------------------------------------------------------------------------*/

#include "cprocessing.h"
#include "splashscreen.h"
#include <stdio.h>
#include "../GameStateManager.h"
#include "../SpriteAnimation/spriteAnimation.h"

unsigned char alpha; // variable to set for alpha image
float speed; // speed in seconds
#define TIMETAKEN 2 //time taken to go from transparent to opaque
bool paused = false;
Sprite* logo;
Sprite* gameLogo;
bool flip = false;
bool nextLogo = false;
bool nextScene = false;
char logoAlpha = 0;

void splash_screen_init(void)
{
	logo = CreateSprite("Assets/DigiPen_Singapore_WEB_RED.png", 1, 1, false, false);
	gameLogo = CreateSprite("Assets/credit1.png", 1, 1, false, false);
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
	CP_System_SetWindowSize(1280, 720);
	CP_Settings_BlendMode(CP_BLEND_ALPHA);

	alpha = 0;
	speed = 255 / TIMETAKEN;

	logo->go.scale = CP_Vector_Set(0.8f, 0.8f);
	logo->go.position = CP_Vector_Set(0.f, 720 * 0.5f - logo->go.size.y * 0.5f);
	gameLogo->go.scale = CP_Vector_Set(1, 1);
	gameLogo->go.position = CP_Vector_Set((float)(CP_System_GetWindowWidth() / 2 - CP_Image_GetWidth(gameLogo->go.image) / 2) , 720 * 0.5f - logo->go.size.y * 0.5f);
	gameLogo->go.alpha = 0;
}

void splash_screen_update(void)
{
	//get the delta time between each frame
	float dt = CP_System_GetDt();
	//algorithm for logo fade in and out
	int oldalpha = alpha;
	alpha += (unsigned char)(speed * dt);

	logo->go.alpha = alpha;
	if (nextLogo)
	{
		 logoAlpha += (char)(speed * dt);
		 gameLogo->go.alpha = (float)(abs(logoAlpha) * 2);
		 if (gameLogo->go.alpha >= 254)
			 flip = true;
		 if (gameLogo->go.alpha <= 2 && flip)
			 nextScene = true;
	}
	else if (oldalpha > alpha)
	{
		nextLogo = true;
	}
	
	if (nextScene)
	{
		GameStateSetNextScene(MAINMENU_SCENE);
	}
	//Render
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	//Render LOGO
	if (!nextLogo)
		RenderSprite(logo);
	else
		RenderSprite(gameLogo);

	//RENDER CIRCLE
	
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

	if (CP_Input_KeyTriggered(KEY_P))
	{
		if(!paused)
			GameStateSetNextSubScene(SPRITEANIMATION_SCENE, true);
		else
			GameStateSetNextSubScene(MAX_SCENE, true);
		paused = !paused;
	}
}

void splash_screen_exit(void)
{
	CP_Image_Free(&logo->go.image);
}