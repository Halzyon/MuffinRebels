#include "cprocessing.h"
#include <stdbool.h>
#include "../UI/UtilsUI/ui_utils.h"
#include "../yijia/mainmenu.h"
#include "../UI/CombatOverlayUI/combat_overlay.h"

asset button;
asset button1pressed;
asset button2;
asset button2pressed;
asset button3;
asset button3pressed;
asset settings;
asset creditstxt;
asset exittxtlarge;
asset startxt;
int alpha; 

void mainmenu_init() {
	
	get_image_size_set("Assets/button.png", &button);
	get_image_size_set("Assets/button2.png", &button2);
	get_image_size_set("Assets/button3.png", &button3);
	get_image_size_set("Assets/button1pressed.png", &button1pressed);
	get_image_size_set("Assets/button2pressed.png", &button2pressed);
	get_image_size_set("Assets/button3pressed.png", &button3pressed);
	get_image_size_set("Assets/combat_overlay_ui/settings.png", &settings);
	get_image_size_set("Assets/creditstxt.png", &creditstxt);
	get_image_size_set("Assets/exittxtlarge.png", &exittxtlarge);
	get_image_size_set("Assets/startxt.png", &startxt);
	CP_System_SetWindowSize(1280, 720);
	CP_Settings_ImageMode(CP_POSITION_CENTER);

	//positions
	settings.position.x = CP_System_GetWindowWidth() - 50;
	settings.position.y = 50;

	button.position.x = CP_System_GetWindowWidth() - 640;
	button.position.y = 220;

	button2.position.x = CP_System_GetWindowWidth() - 640;
	button2.position.y = 370;

	button3.position.x = CP_System_GetWindowWidth() - 640;
	button3.position.y = 520;

	button1pressed.position.x = CP_System_GetWindowWidth() - 640;
	button1pressed.position.y = 220;

	button2pressed.position.x = CP_System_GetWindowWidth() - 640;
	button2pressed.position.y = 370;

	button3pressed.position.x = CP_System_GetWindowWidth() - 640;
	button3pressed.position.y = 520;

	creditstxt.position.x = CP_System_GetWindowWidth() - 640;
	creditstxt.position.y = 365;

	startxt.position.x = CP_System_GetWindowWidth() - 640;
	startxt.position.y = 215;

	exittxtlarge.position.x = CP_System_GetWindowWidth() - 640;
	exittxtlarge.position.y = 515;
	
}


void mainmenu_update() {

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	//SETTINGS ICON - open settings_ui

	RenderAsset(settings, 255);
	//if (mouse_in_rect(settings_icon.position.x, settings_icon.position.y, settings_icon.size.x, settings_icon.size.y) == 1)
	//{
	//	//open settings pop up
	//}
	RenderAsset(button, 255);
	if (mouse_in_rect(button.position.x, button.position.y, button.size.x - 200, button.size.y - 200) == 1)	 //-100 to reduce the size of area of detection 
	{
		RenderAsset(button1pressed, 255);
		if (CP_Input_MouseClicked())
		{
			button.clicked = !button.clicked;
		}
		//if (button.clicked == 1 )
		//{
		//	//level 1 
		//}
	}

	//LVL 2 BUTTON 
	RenderAsset(button2, 255);
	if (mouse_in_rect(button2.position.x, button2.position.y, button2.size.x - 200, button2.size.y - 200) == 1)	 //-100 to reduce the size of area of detection 
	{
		RenderAsset(button2pressed, 255);
		if (CP_Input_MouseClicked())
		{
			button2.clicked = !button2.clicked;
		}
		//if (button2.clicked == 1 )
		//{
		//	//level 2
		//}
	}

	RenderAsset(button3, 255);
	if (mouse_in_rect(button3.position.x, button3.position.y, button3.size.x - 200, button3.size.y - 200) == 1)	 //-100 to reduce the size of area of detection 
	{
		RenderAsset(button3pressed, 255);
		if (CP_Input_MouseClicked())
		{
			button3.clicked = !button3.clicked;
		}
		//if (button3.clicked == 1 )
		//{
		//	//level 3
		//}

	}

	RenderAsset(startxt, 255);
	RenderAsset(exittxtlarge, 255);
	RenderAsset(creditstxt, 255);

}


void mainmenu_exit() {

}

void RenderAsset(asset render, int opacity)
{
	CP_Image_Draw(render.image, render.position.x, render.position.y, render.size.x, render.size.y, opacity);
}