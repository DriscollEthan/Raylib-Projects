#include "Player.h"

Player::Player() : Object()
{
	bIsWrapAroundScreen = false;
}

Player::Player(raylib::Image _image)
{
	Image = _image;

	Hitbox = raylib::Rectangle(raylib::Vector2(0, 0), raylib::Vector2(Image.width, Image.height));

	Position = raylib::Vector2(0, 0);
	bIsWrapAroundScreen = false;
}

Player::Player(Player& const _other)
{
	Image = _other.Image;
	Hitbox = _other.Hitbox;
	Position = _other.Position;
	bIsWrapAroundScreen = _other.bIsWrapAroundScreen;
}

Player Player::operator=(Player& const _other)
{
	Image = _other.Image;
	Hitbox = _other.Hitbox;
	Position = _other.Position;
	bIsWrapAroundScreen = _other.bIsWrapAroundScreen;
	return *this;
}

Player::~Player()
{
}

void Player::Movement(Driscoll::Vector2D _movementVector, raylib::Vector2 _screenSize, float _speed)
{
	std::cout << "Current Position: " << Position << std::endl;;

	Position += _movementVector.SafeNormalised() * _speed;

	if (bIsWrapAroundScreen)
	{
		Position = Wrap(Position, raylib::Vector2(0, 0), _screenSize);
	}

	OverrideHitBoxSize(Hitbox.GetSize());

	std::cout << "End Position: " << Position << std::endl;
}

void Player::ShouldWrapAroundScreen(bool _bShouldWrap)
{
	bIsWrapAroundScreen = _bShouldWrap;
}

raylib::Vector2 Player::Wrap(raylib::Vector2 _currentVector, raylib::Vector2 _min, raylib::Vector2 _max)
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

raylib::Vector2 Player::CurrentPosition()
{
	return Position;
}
