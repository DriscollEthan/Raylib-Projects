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

	Timer& operator =(const Timer& _other)
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
	Enemy(LocalData2D _localData = {}, size_t _texturePosition = 0, Driscoll::Vector2D _origin = { 0,0 }, HitboxData _hitbox = {}, float _speed = 1.0f, float _bulletLifetime = 0.0f, float _bulletSpeed = 0.0f);

	Enemy(const Enemy& _other);

	Enemy& operator = (const Enemy& _other);

  ~Enemy();

  virtual void BeginPlay() override;

  virtual void Update() override;

  virtual void Draw() override;

	virtual void GotHit() override;

	void SetPlayerRef(Entity* _playerRef);

	void SetTimer(Timer _newTimer);

	void SetRandomLocation();

	void MoveToRandomLocation();

	Gunner* GetTurretRef();

	float GetHealth();

	void SetHealth(float _maxHealth);

protected:
	Gunner* Turret;

	Entity* PlayerRef;

	Timer ShootingTimer;

	Driscoll::Vector2D RandomMoveToLocation;

	float BulletSpeed;
	
	float BulletLifetime;

	float Health; 

	bool bLastHit;

	bool bFlipFlop;

	int SwitchingFrameCounter;
};

