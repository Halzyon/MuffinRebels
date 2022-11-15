#include "cprocessing.h"
#include <stdbool.h>
#include "../yijia/credits.h"
#include "../UI/UtilsUI/ui_utils.h"
#include "../UI/CombatOverlayUI/combat_overlay.h"
#include "GameStateManager.h"

CP_Font myFont;
asset creditstxt; 
int alpha;


void credits_init() {
myFont = CP_Font_Load("Assets/KenneyPixel.ttf");
get_image_size_set("Assets/creditstxt.png", &creditstxt);
CP_Settings_ImageMode(CP_POSITION_CENTER);

creditstxt.position.x = 100;
creditstxt.position.y = 50;

}


void credits_update() {
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	RenderAsset(creditstxt,255);
	if (CP_Input_KeyDown(KEY_ESCAPE))
		GameStateSetNextScene(MAINMENU_SCENE);
}

void credits_exit() {

}

