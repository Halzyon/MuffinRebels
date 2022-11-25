#include "cprocessing.h"
#include "../yijia/gameOver.h"
#include "../UI/UtilsUI/ui_utils.h"
#include "SpriteAnimation/spriteAnimation.h"
#include "settings_ui.h"

//Game Over and win page

asset win;
asset gameover;
int alpha;

void gameTransition_init(void) {
	get_image_size_set("Assets/win.png", &win);
	get_image_size_set("Assets/gameover.png", &gameover);

	//position
	/*win.position.x = CP_System_GetWindowWidth() - 640;
	win.position.y = 360;*/

	win.position.x = 0;
	win.position.y = 360;

	gameover.position.x = 0;
	gameover.position.y = 360;

	/*gameover.position.x = CP_System_GetWindowWidth() - 640;
	gameover.position.y = 360;*/

	// TODO: pause the bgm here

}


void gameTransition_update(void) {
	//win
	RenderAsset(win, 255);
	go_to_animation(CP_System_GetWindowWidth() /2.0f, CP_System_GetWindowHeight() /2.0f, &win.position);

	//gameover
	RenderAsset(gameover, 255);
	go_to_animation(CP_System_GetWindowWidth() / 2.0f, CP_System_GetWindowHeight() / 2.0f, &gameover.position); 

}


void gameTransition_shutdown(void) {

}


