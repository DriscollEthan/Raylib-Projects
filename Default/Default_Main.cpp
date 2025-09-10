#include "../raylib-cpp/raylib-cpp/include/raylib-cpp.hpp"
#include <iostream>

int main()
{
	//Initialization
	int ScreenWidth = 800;
	int ScreenHeight = 450;
	raylib::Color TextColor = raylib::Color::Green();
	raylib::Window Window(ScreenWidth, ScreenHeight, "Basic Window");
	raylib::Text Text("Congrats! I created my first window!");

	SetTargetFPS(60);

	//Main Game Loop
	while (!Window.ShouldClose())
	{
		//Update
		if (IsKeyPressed(KEY_SPACE))
		{
			if (TextColor == raylib::Color::Green())
			{
				TextColor = raylib::Color::Red();
			}
			else
			{
				TextColor = raylib::Color::Green();
			}
		}
		//Variable Updates

		//Draw
		while (Window.Drawing())
		{
			Window.ClearBackground(RAYWHITE);
			TextColor.DrawText(Text.GetText(), 190, 200, 20);
		}
	}

	return 0;
}