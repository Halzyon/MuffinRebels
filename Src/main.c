#include "cprocessing.h"
#include "FileIO/fileIO.h"
#include "FileIO/serialization.h"

    

CP_Image logo;
 
void game_init(void)
{
	logo = CP_Image_Load("Assets/DigiPen_Singapore_WEB_RED.png");
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

	CP_System_SetWindowSize(CP_Image_GetWidth(logo), CP_Image_GetHeight(logo));
}

void game_update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(0,0,0,255));
	CP_Image_Draw(logo, 0.f, 0.f, CP_Image_GetWidth(logo), CP_Image_GetHeight(logo), 255);
	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_Terminate();
	}
	
}

void game_exit(void)
{
	CP_Image_Free(&logo);
}




int main(void)
{
	//printf("%s\n",readFile("data12.dat"));
	ExampleStruct ex;
	Buffer * b = newBuffer();
	//reserveSpace(b, sizeof(ExampleStruct));

	ex.str = "kill meAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	ex.var1 = -2531;
	ex.var2 = -69.1239817;

	serialize_Ex(ex, b);
	//readSerialize_Ex(b, &ex);

	init_IO();
	writeFile("data16.dat", b->data, "w");

	ExampleStruct ex2;
	char* c = readFile("data16.dat");
	readSerialize_Ex(c, &ex2);

	//ex2.str = "";
	clearBuffer(b);
	serialize_Ex(ex2, b);
	writeFile("data15.dat", b->data, "w");
	/*printf("%d\n", ex2.var1);
	printf("%.32lf\n", ex2.var2);*/

	exit_IO();
	//free(ex);
	closeBuffer(b);
	//free(b);



	
	// @TODO CRASHING A LOT AT EXIT IN RELEASE PROBLEMS IS THE SERIALIZATION CODE
	return 0;
}
