#include <iostream>																//DEBUGGING
#include "../raylib-cpp/include/raylib-cpp.hpp"		//RAYLIB CPP
#include "Vector2D.h"															//CUSTOM VECTOR2D
#include "GlobalVariableObject.h"									//Global Variables Meant for Access in Multiple Classes
#include "Character.h"																//Entity Class

int main()
{
	//Variable Initialization:
		//RAYLIB WINDOW
	GlobalVariableObject GVO = GlobalVariableObject();
	Driscoll::Vector2D ScreenSize = GVO.GetScreenSize();
		raylib::Window Window(ScreenSize.x, ScreenSize.y, "Twin Stick Shooter");

		//Player Setup
		raylib::Image PlayerImage; PlayerImage.Load("Resources/Dollar-Gold-Coin-PNG.png");
		Character* CurrentPlayer = new Character(Driscoll::Vector2D(500, 300), PlayerImage, 20.0f, 0.0f, 2.5f);

		//Others

	/*** *** ***/

	SetTargetFPS(60);

	/*** *** ***/

	//BEGIN PLAY
	CurrentPlayer->BeginPlay();
	
	/*** *** ***/

	//Main Game Loop and Entry Point
	while (!Window.ShouldClose())
	{
		//Update
		CurrentPlayer->Update();

		/*** *** ***/

		//Draw
		while (Window.Drawing())
		{
			ClearBackground(DARKGRAY);

			CurrentPlayer->Draw();
		}
	}

	/*** *** ***/

	//END OF MAIN GAME LOOP
	delete CurrentPlayer;
	/*** *** ***/

	//END *** ***
	return 0;
}