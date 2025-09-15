#include "../raylib-cpp/include/raylib-cpp.hpp"
#include <iostream>

raylib::Vector2 Wrap(raylib::Vector2 _currentVector, raylib::Vector2 _min, raylib::Vector2 _max)
{
	//Over Max on X-Axis Wrapper
	if (_currentVector.x > _max.x)
	{
		float overFlow = _currentVector.x - _max.x;
		if (overFlow > _max.x)
		{
			overFlow /= _max.x;
			int overFlowTruncated = overFlow;

			overFlow -= overFlowTruncated;

			_currentVector.x = overFlow * _max.x;
		}
		else
		{
			_currentVector.x = overFlow;
		}
	}
	//Under Min on X-Axis Wrapper
	else if (_currentVector.x < _min.x)
	{
		float overFlow = _max.x - _currentVector.x;

		if (overFlow > _max.x)
		{
			overFlow /= _max.x;
			int overFlowTruncated = overFlow;

			overFlow -= overFlowTruncated;

			_currentVector.x = _max.x - overFlow;
		}
		else
		{
			_currentVector.x = overFlow;
		}
	}
	//Over Max on Y-Axis Wrapper
	if (_currentVector.y > _max.y)
	{
		float overFlow = _currentVector.y - _max.y;
		if (overFlow > _max.y)
		{
			overFlow /= _max.y;
			int overFlowTruncated = overFlow;

			overFlow -= overFlowTruncated;

			_currentVector.y = overFlow * _max.y;
		}
		else
		{
			_currentVector.y = overFlow;
		}
	}
	//Under Min on Y-Axis Wrapper
	else if (_currentVector.y < _min.y)
	{
		float overFlow = _max.y - _currentVector.y;

		if (overFlow > _max.y)
		{
			overFlow /= _max.y;
			int overFlowTruncated = overFlow;

			overFlow -= overFlowTruncated;

			_currentVector.y = _max.y - overFlow;
		}
	}

	return _currentVector;
}

raylib::Vector2 Movement(raylib::Vector2 _curPos, raylib::Vector2 _movementVector, raylib::Vector2 _max)
{
	_curPos += _movementVector;

	//Wrapper for Max Values
	_curPos = Wrap(_curPos, raylib::Vector2(0, 0), _max);
	return _curPos;
}

int main()
{
	//Initialization
	int ScreenWidth = 800;
	int ScreenHeight = 800;
	raylib::Color TextColor = raylib::Color::Green();
	raylib::Window Window(ScreenWidth, ScreenHeight, "Basic Window");
	raylib::Text Text("Congrats! I created my first window!");
	raylib::Vector2 PlayerPosition(0, 0);
	float MovementSpeed = 1.0f;
	raylib::Vector2 MovementVector(0, 0);

	SetTargetFPS(60);

	//Main Game Loop
	while (!Window.ShouldClose())
	{
		//Variable Reset Location
		MovementVector = (0, 0);

		//Update Look For Input
		// 
		//MOVEMENT INPUT
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

		//UPDATE TEXT AND CHANGE TEXT MOVEMENT SPEED INPUT
		if (IsKeyPressed(KEY_SPACE))
		{
			if (TextColor == raylib::Color::Green())
			{
				TextColor = raylib::Color::Pink();
				Text.SetText("Brand New Input!");
			}
			else
			{
				TextColor = raylib::Color::Green();
				Text.SetText("Congrats! I created my first window!");
			}
		}
		if (IsKeyReleased(KEY_SPACE))
		{
			MovementSpeed += 0.5f;
		}
		//Variable Updates
		MovementVector *= MovementSpeed;
		PlayerPosition = Movement(PlayerPosition, MovementVector, raylib::Vector2(ScreenWidth, ScreenHeight));

		//Draw
		while (Window.Drawing())
		{
			Window.ClearBackground(DARKGRAY);
			TextColor.DrawText(Text.GetText(), PlayerPosition.x, PlayerPosition.y, 20);
		}
	}
	//END OF MAIN GAME LOOP

	return 0;
}