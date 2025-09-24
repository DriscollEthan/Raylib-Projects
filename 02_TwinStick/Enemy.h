#pragma once
#include "Entity.h"
#include "Gunner.h"

struct Timer
{
	float TimerLength;

	float TimerDeviation;

	float CurrentTimer;

	Timer() { TimerLength = TimerDeviation = CurrentTimer = 0.0f; }

	Timer(float _length, float _deviation)
	{
		TimerLength = _length;
		TimerDeviation = _deviation;
		CurrentTimer = 0.0f;
	}

	Timer(const Timer& _other)
	{
		TimerLength = _other.TimerLength;
		TimerDeviation = _other.TimerDeviation;
		CurrentTimer = _other.CurrentTimer;
	}

	Timer operator =(const Timer& _other)
	{
		TimerLength = _other.TimerLength;
		TimerDeviation = _other.TimerDeviation;
		CurrentTimer = _other.CurrentTimer;
		return *this;
	}

	bool TimerOver()
	{
		return CurrentTimer >= TimerLength;
	}

	void ResetTimer()
	{
		CurrentTimer = 0.0f;

		TimerLength -= TimerDeviation;

		float min = 0 - TimerDeviation;
		float max = 0 + TimerDeviation;
		TimerDeviation = GetRandomValue(min, max);

		TimerLength += TimerDeviation;
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

	void SetTimer(Timer _newTimer);

	void SetRandomLocation();

	void MoveToRandomLocation();

protected:
	Gunner* Turret;

	Entity* PlayerRef;

	Timer ShootingTimer;

	Driscoll::Vector2D RandomMoveToLocation;
};

