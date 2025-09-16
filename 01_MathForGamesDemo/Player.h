#pragma once

#include "Object.h"

class Player : public Object
{
public:
	//Constructors and Destructors
	Player();

	Player(raylib::Image _image);

	Player(Player& const _other);

	Player operator=(Player& const _other);

	~Player();

private:
	//Variables
	bool bIsWrapAroundScreen;

public:
	//Functions
	void Movement(Driscoll::Vector2D _movementVector, raylib::Vector2 _screenSize, float _speed);

	void ShouldWrapAroundScreen(bool _bShouldWrap);

	raylib::Vector2 Wrap(raylib::Vector2 _currentVector, raylib::Vector2 _min, raylib::Vector2 _max);

	raylib::Vector2 CurrentPosition();
};

