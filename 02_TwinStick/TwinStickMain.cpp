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

		bool bRESTART = false;

		do
		{
			//Player Setup
			GameMode* TankGameMode = new GameMode();

			/*** *** ***/

			SetTargetFPS(240);

			HideCursor();

			/*** *** ***/

			//BEGIN PLAY
			TankGameMode->BeginPlay();

			/*** *** ***/

			//Main Game Loop and Entry Point
			while (!TankGameMode->ShouldShutdown())
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
			bRESTART = TankGameMode->ShouldRestart();
			
			//END OF MAIN GAME LOOP
			delete TankGameMode;

		} while (bRESTART);


	/*** *** ***/

	//END *** ***
	ShowCursor();
	return 0;
}