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
void splash_screen_init(void)
{
	logo = CreateSprite("Assets/DigiPen_Singapore_WEB_RED.png", 1, 1, false, false);
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
	CP_System_SetWindowSize(1280, 720);
	CP_Settings_BlendMode(CP_BLEND_ALPHA);

	alpha = 0;
	speed = 255 / TIMETAKEN;

	logo->go.scale = CP_Vector_Set(0.8, 0.8);
	logo->go.position = CP_Vector_Set(0, 720* 0.5 - logo->go.size.y * 0.5);
}

void splash_screen_update(void)
{
	//get the delta time between each frame
	float dt = CP_System_GetDt();
	//algorithm for logo fade in and out

	alpha = alpha % 256 + speed * dt;
	//To Quit the game
	if (CP_Input_KeyDown(KEY_ESCAPE) || CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_Terminate();
	}
	logo->go.alpha = alpha;
	if (alpha > 254)
	{
		GameStateSetNextScene(GAME_SCENE);
	}
	//Render
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	//Render LOGO
	RenderSprite(logo);

	//RENDER CIRCLE
	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawCircle(CP_Input_GetMouseX(), CP_Input_GetMouseY(), 50.f);
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