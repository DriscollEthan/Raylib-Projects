#include "../raylib-cpp/include/raylib-cpp.hpp"

int main()
{
	//Variable Initialization
	int ScreenWidth = 800;
	int ScreenHeight = 800;
	raylib::Window Window(ScreenWidth, ScreenHeight, "Default Window");

	//Main Game Loop
	while (!Window.ShouldClose())
	{
		//Variable Reset Location

		//Update Look For Input

		//Variable Updates

		//Draw
		while (Window.Drawing())
		{
			Window.ClearBackground(BLACK);
		}
	}
	//END OF MAIN GAME LOOP

	return 0;
}