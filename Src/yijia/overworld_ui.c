#include <cprocessing.h>
#include "SpriteAnimation/spriteAnimation.h"
#include "../yijia/overworld_ui.h"

Sprite* gradientramp; 
Sprite* buttonpressed;
Sprite* button;
Sprite* settings_icon;
Sprite* lvl1icon;
Sprite* lvl2icon;
Sprite* lvl3icon;
CP_Font myFont; 
int alpha; 

void overworld_init(void) {
	myFont = CP_Font_Load("Assets/Kenney Pixel.ttf");
	gradientramp = CreateSprite("Assets/gradientramp.png", 1, 1, false, false);
	buttonpressed = CreateSprite("Assets/buttonpressed.png", 1, 1, false, false);
	button = CreateSprite("Assets/button.png", 1, 1, false, false);
	settings_icon = CreateSprite("Assets/settings_icon.png", 1, 1, false, false);
	lvl1icon = CreateSprite("Assets/lvl1icon.png", 1, 1, false, false);
	lvl2icon= CreateSprite("Assets/lvl2icon.png", 1, 1, false, false);
	lvl3icon = CreateSprite("Assets/lvl3icon.png", 1, 1, false, false);
	CP_System_SetWindowSize(1280, 720); 
	CP_Settings_ImageMode(CP_POSITION_CORNER);  

	//settings_icon->go.position.x = 35;
	//settings_icon->go.position.y = 26;
	settings_icon->go.position.x = CP_System_GetWindowWidth() - 50.0f;
	settings_icon->go.position.y = 50.0f;

	
}


void overworld_update(void) {
	//CP_Graphics_ClearBackground(CP_Color_Create(128, 128, 128, 255));
	//RenderSprite(gradientramp);

	RenderSprite(settings_icon); //render top first

	//LEVEL 1 BUTTON
	button->go.position.x = 442;
	button->go.position.y = 145;
	RenderSprite(button);

	//LEVEL 2 BUTTON
	button->go.position.x = 442;
	button->go.position.y = 314;
	RenderSprite(button); 

	//LEVEL 3 BUTTON
	button->go.position.x = 442;
	button->go.position.y = 483;
	RenderSprite(button); 

	////LEVEL 1 BUTTON PRESSED
	//buttonpressed->go.position.x = 442;
	//buttonpressed->go.position.y = 145;
	//RenderSprite(buttonpressed);

	////LEVEL 2 BUTTON PRESSED
	//buttonpressed->go.position.x = 442;
	//buttonpressed->go.position.y = 314;
	//RenderSprite(buttonpressed);

	////LEVEL 3 BUTTON PRESSED
	//buttonpressed->go.position.x = 442;
	//buttonpressed->go.position.y = 483;
	//RenderSprite(buttonpressed);
	
	//LEVEL 1 TXT ICON
	lvl1icon->go.position.x = 575;
	lvl1icon->go.position.y = 175;
	RenderSprite(lvl1icon);

	//LEVEL 2 TXT ICON
	lvl2icon->go.position.x = 575;
	lvl2icon->go.position.y = 345;
	RenderSprite(lvl2icon);

	//LEVEL 3 TXT ICON
	lvl3icon->go.position.x = 575;
	lvl3icon->go.position.y = 512;
	RenderSprite(lvl3icon);

	
}


void overworld_shutdown(void) {


}