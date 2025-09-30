#include <iostream>																//DEBUGGING

#include "../raylib-cpp/include/raylib-cpp.hpp"		//RAYLIB CPP

#include "DriscollMathUtils.h"										//CUSTOM Math Library

#include "GlobalVariableObject.h"									//Global Variables Meant for Access in Multiple Classes

#include "GameManager.h"													//Game Manager Class

int main()
{
	//Variable Initialization:
	//RAYLIB WINDOW
	GlobalVariables GlobalVars = {};
		raylib::Window Window(GlobalVars.ScreenX, GlobalVars.ScreenY, "Twin Stick Shooter");

	//Player Setup
		GameManager* GameMode = new GameManager();

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
			Window.ClearBackground(DARKGRAY);

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