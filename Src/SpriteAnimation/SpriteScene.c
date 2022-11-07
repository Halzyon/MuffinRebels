#include "spriteAnimation.h"
Sprite* ash;
void SpriteScene_init(void)
{

	ash = CreateSprite("Assets/poke.png", 4, 4, true, true);

	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

}

void SpriteScene_update(void)
{
	UpdateSprite(ash, CP_System_GetDt());
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	//CP_Image_Draw(logo, 0.f, 0.f, CP_Image_GetWidth(logo), CP_Image_GetHeight(logo), 255);
	RenderSprite(ash);

	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_Terminate();
	}

}

void SpriteScene_exit(void)
{
	CP_Image_Free(&ash->go.image);
	free(ash);
}