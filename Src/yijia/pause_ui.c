#include "cprocessing.h"
#include "SpriteAnimation/spriteAnimation.h"
#include "../UI/UtilsUI/ui_utils.h"
#include"pause_ui .h"

CP_Font myFont;   
Sprite* pausedpopup;
Sprite* arrow1icon;
Sprite* arrow2icon;
Sprite* arrow3icon;
Sprite* exit_icon;
Sprite* settings_icon;
Sprite* gamepaused; 
int alpha;

void gamepaused_init(void) {
	myFont = CP_Font_Load("Assets/Kenney Pixel.ttf");
	pausedpopup = CreateSprite("Assets/pausedpopup.png", 1, 1, false, false);
	arrow1icon = CreateSprite("Assets/arrowicon.png", 1, 1, false, false);
	arrow2icon = CreateSprite("Assets/arrowicon.png", 1, 1, false, false);
	arrow3icon = CreateSprite("Assets/arrowicon.png", 1, 1, false, false);
	exit_icon = CreateSprite("Assets/exit_icon.png", 1, 1, false, false);
	settings_icon = CreateSprite("Assets/settings_icon.png", 1, 1, false, false);
	gamepaused = CreateSprite("Assets/gamepaused.png", 1, 1, false, false);
	CP_System_SetWindowSize(1280, 720);
	CP_Settings_ImageMode(CP_POSITION_CENTER);

	//POSITIONS
	settings_icon->go.position.x = CP_System_GetWindowWidth()- 50;
	settings_icon->go.position.y = 50;

	pausedpopup->go.position.x = CP_System_GetWindowWidth()-640;
	pausedpopup->go.position.y = 360;

	exit_icon->go.position.x = CP_System_GetWindowWidth()-330;
	exit_icon->go.position.y = 220;

	gamepaused->go.position.x = CP_System_GetWindowWidth()-640;
	gamepaused->go.position.y = 260; 
	
}


void gamepaused_update(void) {
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	
	//RENDER ICONS 
	RenderSprite(settings_icon); 
	RenderSprite(pausedpopup);
	RenderSprite(arrow3icon);
	RenderSprite(arrow2icon);
	RenderSprite(arrow1icon);
	RenderSprite(exit_icon);
	RenderSprite(gamepaused);


	arrow1icon->go.position.x = CP_System_GetWindowWidth() - 730;
	arrow1icon->go.position.y = 330;

	arrow2icon->go.position.x = CP_System_GetWindowWidth() - 730;
	arrow2icon->go.position.y = 390;

	arrow3icon->go.position.x = CP_System_GetWindowWidth() - 730;
	arrow3icon->go.position.y = 450;


	//RENDER TEXT
	CP_Font_Set(myFont);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255)); //original text color
	CP_Settings_TextSize(60.0f); //change the text size
	//CP_Font_DrawText("GAME PAUSED",500, 250); //Settings text 

	CP_Font_Set(myFont);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255)); //original text color
	CP_Settings_TextSize(45.0f); //change the text size
	CP_Font_DrawText("Restart", 590, 340); //Settings text 
	CP_Font_DrawText("Resume", 590, 400); //Settings text 
	CP_Font_DrawText("Exit", 590, 460); //Settings text 
	}


void gamepaused_shutdown(void) {

	}