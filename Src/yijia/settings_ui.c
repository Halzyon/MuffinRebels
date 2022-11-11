#include "cprocessing.h"
#include <stdbool.h>
#include "../UI/UtilsUI/ui_utils.h"
#include "SpriteAnimation/spriteAnimation.h"
#include "brightness_Settings_ui.h"

Sprite* exitsetting_icon;
Sprite* settingsbg;
Sprite* brightness_icon;
Sprite* save_icon;
Sprite* SoundOn_icon;
CP_Font myFont;
int alpha;

void settings_init(void){
	//OPENFILE
	myFont = CP_Font_Load("Assets/Kenney Pixel.ttf");
	settingsbg= CreateSprite("Assets/settingsbg.png", 1, 1, false, false);
	exitsetting_icon = CreateSprite("Assets/exitsetting_icon.png", 1, 1, false, false);
	brightness_icon = CreateSprite("Assets/brightness_icon.png", 1, 1, false, false);
	save_icon = CreateSprite("Assets/save_icon.png", 1, 1, false, false);
	SoundOn_icon = CreateSprite("Assets/SoundOn_icon.png", 1, 1, false, false);

	CP_System_SetWindowSize(1280, 720);
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	
	//POSITIONS
	exitsetting_icon->go.position.x = CP_System_GetWindowWidth() - 440;
	exitsetting_icon->go.position.y = 170;

	settingsbg->go.position.x = CP_System_GetWindowWidth() - 640;
	settingsbg->go.position.y = 360;

	brightness_icon->go.position.x = CP_System_GetWindowWidth() - 810;
	brightness_icon->go.position.y = 565;

	save_icon->go.position.x = CP_System_GetWindowWidth() - 460;
	save_icon->go.position.y = 565;

	SoundOn_icon->go.position.x = CP_System_GetWindowWidth() - 635;
	SoundOn_icon->go.position.y = 565;
} 

void settings_update(void) { 
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	//RENDER ICONS
	RenderSprite(settingsbg);
	RenderSprite(exitsetting_icon);
	RenderSprite(brightness_icon);
	RenderSprite(save_icon);
	RenderSprite(SoundOn_icon);


}


void settings_shutdown(void) {

}