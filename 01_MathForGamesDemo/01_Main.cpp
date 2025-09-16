#include <iostream> //std::cout and Logging 
#include "../raylib-cpp/include/raylib-cpp.hpp"
#include "Vector2D.h"
#include "Object.h"
#include "Player.h"
#include "Collectable.h"


int RoundedInt(float x)
{
	float y = x;
	while (y > 1)
	{
		--y;
	}

	if (y >= 0.5)
	{
		x += 0.5f;
	}
	return x;
}

int main()
{
	//Variable Initialization:
	int ScreenWidth = 1000;
	int ScreenHeight = 600;
	raylib::Window Window(ScreenWidth, ScreenHeight, "Default Window");


	Driscoll::Vector2D Grid(5, 3);
	int const TotalGridSegments = 15;

	Player* CurrentPlayer = new Player();
	CurrentPlayer->ShouldWrapAroundScreen(true);
	CurrentPlayer->OverrideHitBoxSize(5.0f);

	Collectable CollectableObjects[TotalGridSegments];

	Driscoll::Vector2D MovementVector = Driscoll::Vector2D();
	
	int TotalScore = 0;

	raylib::Vector4 newVector = { 10, 20, 15, 0 };

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

		int xPos = RoundedInt(xP * Grid.x);

		switch (j)
		{
		case 0:
			CollectableObjects[i].Image = CollectableImage;
			CollectableObjects[i].Position = raylib::Vector2((((ScreenWidth / Grid.x) * xPos) - 125), (75));
			CollectableObjects[i].OverrideHitBoxSize(CollectableImage.GetWidth() / 2.0f);
			break;

		case 1:
			CollectableObjects[i].Image = CollectableImage;
			CollectableObjects[i].Position = raylib::Vector2((((ScreenWidth / Grid.x) * xPos) - 125), (275));
			CollectableObjects[i].OverrideHitBoxSize(CollectableImage.GetWidth() / 2.0f);
			break;

		case 2:
			CollectableObjects[i].Image = CollectableImage;
			CollectableObjects[i].Position = raylib::Vector2((((ScreenWidth / Grid.x) * xPos) - 125), (475));
			CollectableObjects[i].OverrideHitBoxSize(CollectableImage.GetWidth() / 2.0f);
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
		MovementVector = { 0,0 };
		/*** *** ***/

		//Update Look For Input
		if (IsKeyDown(KEY_W))
		{
			MovementVector.y -= 1;
		}
		if (IsKeyDown(KEY_S))
		{
			MovementVector.y += 1;
		}
		if (IsKeyDown(KEY_A))
		{
			MovementVector.x -= 1;
		}
		if (IsKeyDown(KEY_D))
		{
			MovementVector.x += 1;
		}

		/*** *** ***/

		//Variable Updates
		CurrentPlayer->Movement(MovementVector, Window.GetSize(), 2.5f);

		/*** *** ***/

		//Collision Checks
		//Check Collisions for Alive coins against the Player.
		for (int i = 0; i < TotalGridSegments; ++i)
		{
			if (CollectableObjects[i].bIsAlive && CheckCollisionCircles(CollectableObjects[i].Position + Driscoll::Vector2D(0, 25), CollectableObjects[i].HitboxRadius, CurrentPlayer->Position, CurrentPlayer->HitboxRadius))
			{
				++TotalScore;
				CollectableObjects[i].bIsAlive = false;
				break;
			}
		}

		/*** *** ***/

		//Draw
		while (Window.Drawing())
		{
			//Set Background Color
			ClearBackground(DARKGRAY);

			//Draw Coins on the Screen
			for (int i = 0; i < TotalGridSegments; ++i)
			{
				if (CollectableObjects[i].bIsAlive)
				{
					DrawTexture(CollectableObjects[i].Image, CollectableObjects[i].Position.x, CollectableObjects[i].Position.y, WHITE);
				}
			}

			//Draw Score on Screen behind Player
			DrawText(TextFormat("Score: %02i", TotalScore), 10, 10, 25, WHITE);

			//Draw Player on the Screen
			DrawCircleV(CurrentPlayer->CurrentPosition(), 10, BLUE);
		}
	}

	/*** *** ***/

	//END OF MAIN GAME LOOP
	delete CurrentPlayer;

	/*** *** ***/

	//END *** ***
	return 0;
}