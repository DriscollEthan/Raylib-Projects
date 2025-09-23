#pragma once
#include "Entity.h"
#include "Gunner.h"

struct Timer
{
	float TimerLength;

	float TimerDeviation;

	float CurrentTimer;

	bool TimerOver()
	{
		return CurrentTimer >= TimerLength;
	}

	void ResetTimer(float _newTime, float _randomDeviation)
	{
		CurrentTimer = 0.0f;

		float min = 0 - _randomDeviation;
		float max = 0 + _randomDeviation;
		TimerDeviation = GetRandomValue(min, max);

		TimerLength = _newTime + TimerDeviation;
	}

	void TimerUpdate()
	{
		CurrentTimer += GetFrameTime();
	}
};

class Enemy : public Entity
{
public:
	/* CONSTRUCTORS & DESTRUCTORS */
		/**
			* DEFAULT CONSTRUCTOR:
			* Parameters:
			* Position as a Driscoll::Vector2D	| Default: 0,0
			* Texture as an Image								| Default: Default Constructor
			* Radius as a Float									| Default: 0.0
			* Rotation as a Float								| Default: 0.0
			* Speed as a flaot									| Default: 1.0
			*/
	Enemy(Driscoll::Vector2D _position = { 0,0 }, raylib::Image _texture = {}, Driscoll::Vector2D _origin = { 0,0 }, Driscoll::Vector2D _scale = { 1,1 }, float _radius = 0.0f, float _rotation = 0.0f, float _speed = 1.0f);

  ~Enemy();

  virtual void BeginPlay() override;

  virtual void Update() override;

  virtual void Draw() override;

	void SetPlayerRef(Entity* _playerRef);

protected:
	Gunner* Turret;

	Entity* PlayerRef;
};

