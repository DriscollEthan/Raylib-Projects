#include "../raylib-cpp/include/raylib-cpp.hpp"

int main()
{
	//Variable Initialization:
	int ScreenWidth = 800;
	int ScreenHeight = 800;
	raylib::Window Window(ScreenWidth, ScreenHeight, "Default Window");

	/*** *** ***/

	SetTargetFPS(60);

	/*** *** ***/

	//Main Game Loop and Entry Point
	while (!Window.ShouldClose())
	{
		//Variable Reset Location

		/*** *** ***/

		//Update Look For Input

		/*** *** ***/

		//Variable Updates

		/*** *** ***/

		//Draw
		BeginDrawing();

		ClearBackground(DARKGRAY);

		EndDrawing();
	}

	/*** *** ***/

	//END OF MAIN GAME LOOP

	/*** *** ***/

	//END *** ***
	return 0;
}