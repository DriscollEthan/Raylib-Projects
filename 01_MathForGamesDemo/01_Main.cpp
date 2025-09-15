#include "../raylib-cpp/include/raylib-cpp.hpp"
#include "Object.h"
#include "Player.h"
#include "Collectable.h"
#include <iostream> //std::cout and Logging 


int main()
{
	//Variable Initialization:
	int ScreenWidth = 1000;
	int ScreenHeight = 600;
	raylib::Window Window(ScreenWidth, ScreenHeight, "Default Window");
	raylib::Vector2 Grid(5, 3);
	int const TotalGridSegments = 15;
	Player* CurrentPlayer = new Player();
	Collectable CollectableObjects[TotalGridSegments];

	raylib::Image CollectableImage;
	CollectableImage.Load("Resources/Dollar-Gold-Coin-PNG.png");

	//Init Collectable Object Grid
	for (int i = 0; i < TotalGridSegments; ++i)
	{
		int j = i / Grid.x;

		float xP = (i + 1) / Grid.x;
		while (xP > 1)
		{
			xP -= 1;  
		}
		int xPos = xP * Grid.x;

		switch (j)
		{
		case 0:
			CollectableObjects[i].Image = CollectableImage;
			CollectableObjects[i].Position = raylib::Vector2((((ScreenWidth / Grid.x) * xPos) - 100), (100));
			CollectableObjects[i].OverrideHitBoxSize(CollectableImage.GetSize());
			break;

		case 1:
			CollectableObjects[i].Image = CollectableImage;
			CollectableObjects[i].Position = raylib::Vector2((((ScreenWidth / Grid.x) * xPos) / 2), (300));
			CollectableObjects[i].OverrideHitBoxSize(CollectableImage.GetSize());
			break;

		case 2:
			CollectableObjects[i].Image = CollectableImage;
			CollectableObjects[i].Position = raylib::Vector2((((ScreenWidth / Grid.x) * xPos) / 2), (500));
			CollectableObjects[i].OverrideHitBoxSize(CollectableImage.GetSize());
			break;
		}
	}

	/*** *** ***/

	SetTargetFPS(60);

	/*** *** ***/

	//Main Game Loop and Entry Point
	while (!Window.ShouldClose())
	{
		//Variable Resets

		/*** *** ***/

		//Update Look For Input

		/*** *** ***/

		//Variable Updates

		/*** *** ***/

		//Draw
		BeginDrawing();

		for (int i = 0; i < TotalGridSegments; ++i)
		{
			DrawCircleV(CollectableObjects[i].Position / 2, 25, YELLOW);
			//ImageDrawCircleV(&CollectableObjects[i].Image, CollectableObjects[i].Position, 25, WHITE);
		}

		ClearBackground(DARKGRAY);

		EndDrawing();
	}

	/*** *** ***/

	//END OF MAIN GAME LOOP
	delete CurrentPlayer;

	/*** *** ***/

	//END *** ***
	return 0;
}