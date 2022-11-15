#include "spriteAnimation.h"
#include "../Character/gameMap.h"

Sprite* CreateSprite(char* imgPath, UINT8 row, UINT8 col, bool SPRITESHEET, bool b_continuous)
{
	Sprite* newSprite = malloc(sizeof(Sprite));
	if (newSprite)
	{
		newSprite->go.image = CP_Image_Load(imgPath);
		if (!newSprite->go.image)
			LOG("ERROR LOADING IMAGE FROM FILE %s", imgPath);
		newSprite->col = col;
		newSprite->row = row;
		newSprite->go.size.x = CP_Image_GetWidth(newSprite->go.image) / newSprite->col;
		newSprite->go.size.y = CP_Image_GetHeight(newSprite->go.image) / newSprite->row;
		newSprite->id = 0;
		newSprite->time = 0.15;
		newSprite->time_elapsed = 0;
		newSprite->go.position = CP_Vector_Zero();
		newSprite->go.speed = 0;
		newSprite->go.scale = CP_Vector_Set(1, 1);
		newSprite->spriteStates[CONTINUOUS] = b_continuous;
		newSprite->renderMode = 0;
		newSprite->moved = false;
		newSprite->go.isAlive = true;
		newSprite->go.alpha = 255;
	}
		

	//if the spritesheet has multiple different sprits according to row(Y axis) do this
	/*ewSprite->spriteStates[RIGHT] = 2;
	newSprite->spriteStates[BACKWARD] = 0;
	newSprite->spriteStates[LEFT] = 1;
	newSprite->spriteStates[FORWARD] = 3;*/

	return newSprite;
}

void UpdateSprite(Sprite* sprite, float dt)
{
	if (sprite == NULL || !sprite->go.isAlive)
		return;
	sprite->time_elapsed += dt;

	/* to switch between columns when rendering spritesheet
	if (CP_Input_KeyDown(KEY_S))
	{
		sprite->direction = CP_Vector_Add(CP_Vector_Set(0, 1), sprite->direction);
		sprite->renderMode = sprite->spriteStates[BACKWARD];
		sprite->moved = 1;
	}
	*/

	if (sprite->time_elapsed >= sprite->time)
	{

		sprite->time_elapsed -= sprite->time;
		sprite->id++;
		if (sprite->id >= sprite->col)
		{
			sprite->id = 0;
			if (sprite->spriteStates[CONTINUOUS])
			{
				sprite->renderMode++;
				if (sprite->renderMode >= sprite->row)
					sprite->renderMode = 0;

			}
		}		
		sprite->tL.v[0] = sprite->id * sprite->go.size.x;
		sprite->tL.v[1] = sprite->renderMode * sprite->go.size.y;
		sprite->bR = CP_Vector_Add(sprite->tL, sprite->go.size);
	}
}

void RenderSprite(Sprite* sprite)
{	
	//CP_Color color;
	//color.
	if (sprite != NULL && sprite->go.isAlive)	
		CP_Image_DrawSubImage(sprite->go.image, sprite->go.position.x, sprite->go.position.y, sprite->go.size.x * sprite->go.scale.x, sprite->go.size.y * sprite->go.scale.y, sprite->tL.x, sprite->tL.y, sprite->bR.x, sprite->bR.y, sprite->go.alpha);
}

void RenderSpriteOnMap(Sprite* sprite, game_map* gm)
{
	if (sprite != NULL && sprite->go.isAlive)
	{
		float gridsize = CP_System_GetWindowHeight() / gm->height;
		float x = sprite->go.position.x * gridsize;
		float y = sprite->go.position.y * gridsize;
		
		CP_Image_DrawSubImage(sprite->go.image, x, y, sprite->go.size.x * sprite->go.scale.x, sprite->go.size.y * sprite->go.scale.y, sprite->tL.x, sprite->tL.y, sprite->bR.x, sprite->bR.y,255);

	}

}

