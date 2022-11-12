#include <cprocessing.h>
#include "SpriteAnimation/spriteAnimation.h"
#include "../yijia/overworld_ui.h"
#include <stdbool.h>
#include "../UI/UtilsUI/ui_utils.h"

asset buttonpressed;
asset button;
asset settings_icon;
asset lvl1icon;
asset lvl2icon;
asset lvl3icon; 

int alpha; 

void overworld_init(void) {
	
	CP_System_SetWindowSize(1280, 720); 
	CP_Settings_ImageMode(CP_POSITION_CENTER);  

	//get_image_size_set("Assets/exitsetting_icon.png", &exitsetting_icon);
	get_image_size_set("Assets/lvl1icon.png", &lvl1icon);
	get_image_size_set("Assets/lvl2icon.png", &lvl2icon);
	get_image_size_set("Assets/lvl3icon.png", &lvl3icon);
	get_image_size_set("Assets/buttonpressed.png", &buttonpressed);
	get_image_size_set("Assets/button.png", &button);
	get_image_size_set("Assets/settings_icon.png", &settings_icon);

	//positions

	settings_icon.position.x = CP_System_GetWindowWidth() - 50;
	settings_icon.position.y = 50;

	button.position.x = CP_System_GetWindowWidth() - 640;
	button.position.y = 240;

	buttonpressed.position.x = CP_System_GetWindowWidth() - 640;
	buttonpressed.position.y = 240;


	lvl1icon.position.x = CP_System_GetWindowWidth() - 640;
	lvl1icon.position.y = 250;

	lvl2icon.position.x = CP_System_GetWindowWidth() - 640;
	lvl2icon.position.y = 360;

	lvl3icon.position.x = CP_System_GetWindowWidth() - 640;
	lvl3icon.position.y = 460;

}


void overworld_update(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	RenderAsset(settings_icon, 255);
	RenderAsset(button, 255);
	
	/*for (int i = 0; i < 3; i++)
	{
		CP_Image_Draw(button.image, button.position.y + (i * 100), button.position.x, 396, 93, 255);
	}*/

	RenderAsset(lvl1icon, 255);
	RenderAsset(lvl2icon, 255);
	RenderAsset(lvl3icon, 255);
}


void overworld_shutdown(void) {


}



