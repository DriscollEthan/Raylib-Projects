#include <iostream>																//DEBUGGING
#include "../raylib-cpp/include/raylib-cpp.hpp"		//RAYLIB CPP
#include "Vector2D.h"															//CUSTOM VECTOR2D
#include "Entity.h"																//Entity Class

int main()
{
	//Variable Initialization:
	Driscoll::Vector2D ScreenSize(1000, 600);
	raylib::Window Window(ScreenSize.x, ScreenSize.y, "Twin Stick Shooter");

	raylib::Image PlayerImage; PlayerImage.Load("Resources/Dollar-Gold-Coin-PNG.png");
	Entity E(Driscoll::Vector2D(475.0f, 275.0f), PlayerImage);

	/*** *** ***/

	SetTargetFPS(60);

	/*** *** ***/

	//Main Game Loop and Entry Point
	while (!Window.ShouldClose())
	{
		//Update

		/*** *** ***/

		//Draw
		while (Window.Drawing())
		{
			E.Draw();
		}
	}

	/*** *** ***/

	//END OF MAIN GAME LOOP

	/*** *** ***/

	//END *** ***
	return 0;
}