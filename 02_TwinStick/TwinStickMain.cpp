#include <iostream>																//DEBUGGING

#include "../raylib-cpp/include/raylib-cpp.hpp"		//RAYLIB CPP

#include "DriscollMathUtils.h"										//CUSTOM Math Library

#include "GlobalVariableObject.h"									//Global Variables Meant for Access in Multiple Classes

#include "GameMode.h"															//Game Mode Class

int main()
{
	//Variable Initialization:
	//RAYLIB WINDOW
	GlobalVariables GlobalVars = {};
		raylib::Window Window(GlobalVars.ScreenX, GlobalVars.ScreenY, "Twin Stick Shooter");

	//Player Setup
		GameMode* TankGameMode = new GameMode();

	/*** *** ***/

	SetTargetFPS(60);

	HideCursor();

	/*** *** ***/

	//BEGIN PLAY
	TankGameMode->BeginPlay();
	
	/*** *** ***/

	//Main Game Loop and Entry Point
	while (!Window.ShouldClose())
	{
		//Update
		TankGameMode->Update();

		/*** *** ***/

		//Draw
		while (Window.Drawing())
		{
			Window.ClearBackground(DARKGRAY);

			TankGameMode->Draw();
		}
	}

	/*** *** ***/

	//END OF MAIN GAME LOOP
	delete TankGameMode;

	/*** *** ***/

	//END *** ***
	ShowCursor();
	return 0;
}