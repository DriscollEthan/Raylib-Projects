#include <iostream>																//DEBUGGING
#include "../raylib-cpp/include/raylib-cpp.hpp"		//RAYLIB CPP
#include "Vector2D.h"															//CUSTOM VECTOR2D
#include "GlobalVariableObject.h"									//Global Variables Meant for Access in Multiple Classes
#include "GameManager.h"																//Entity Class

int main()
{
	//Variable Initialization:
		//RAYLIB WINDOW
	GlobalVariableObject GVO = GlobalVariableObject();
		raylib::Window Window(GVO.GetScreenSize().x, GVO.GetScreenSize().y, "Twin Stick Shooter");

		//Player Setup
		raylib::Image PlayerImage; PlayerImage.Load("Resources/Dollar-Gold-Coin-PNG.png");
		GameManager* GameMode = new GameManager();

		//Others

	/*** *** ***/

	SetTargetFPS(60);

	/*** *** ***/

	//BEGIN PLAY
	GameMode->BeginPlay();
	
	/*** *** ***/

	//Main Game Loop and Entry Point
	while (!Window.ShouldClose())
	{
		//Update
		GameMode->Update();

		/*** *** ***/

		//Draw
		while (Window.Drawing())
		{
			ClearBackground(DARKGRAY);

			GameMode->Draw();
		}
	}

	/*** *** ***/

	//END OF MAIN GAME LOOP
	delete GameMode;
	/*** *** ***/

	//END *** ***
	return 0;
}