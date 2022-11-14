#include "cprocessing.h"
#include <stdbool.h>
#include "../yijia/credits.h"
#include "../UI/UtilsUI/ui_utils.h"
#include "../UI/CombatOverlayUI/combat_overlay.h"

CP_Font myFont;
asset creditstxt; 
int alpha;


void credits_init() {
myFont = CP_Font_Load("Assets/KenneyPixel.ttf");
get_image_size_set("Assets/creditstxt.png", &creditstxt);
CP_System_SetWindowSize(1280, 720);
CP_Settings_ImageMode(CP_POSITION_CENTER);

creditstxt.position.x = CP_System_GetWindowWidth() - 50;
creditstxt.position.y = 50;

}


void credits_update() {
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	RenderAsset(creditstxt,255);

}

void credits_exit() {

}

