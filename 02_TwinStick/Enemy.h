#pragma once
#include "Entity.h"
#include "Timer.h"

#include "Gunner.h"

struct CustomTimer
{
	float TimerLength;

	float TimerDeviation;

	Timer InternalTimer;

	CustomTimer()
	{
		TimerLength = TimerDeviation = 0.0f; 
		InternalTimer = {};
	}

	CustomTimer(float _length, float _deviation)
	{
		TimerLength = _length;
		TimerDeviation = _deviation;
		InternalTimer = {};
	}

	CustomTimer(const CustomTimer& _other)
	{
		TimerLength = _other.TimerLength;
		TimerDeviation = _other.TimerDeviation;
		_other.InternalTimer;
	}

	CustomTimer& operator =(const CustomTimer& _other)
	{
		TimerLength = _other.TimerLength;
		TimerDeviation = _other.TimerDeviation;
		_other.InternalTimer;
		return *this;
	}

	void CustomSetTimer(float _length, float _deviation)
	{
		TimerLength = _length;
		TimerDeviation = _deviation;
		ResetTimer(); 
	}

	void ResetTimer()
	{
		TimerLength -= TimerDeviation;

		float min = 0 - TimerDeviation;
		float max = 0 + TimerDeviation;
		TimerDeviation = GetRandomValue(min, max);

		TimerLength += TimerDeviation;

		InternalTimer.SetTimerInSeconds(0.0f, TimerLength);
	}

	bool TimerUpdate(float _deltaSeconds)
	{
		return InternalTimer.RunTimer(_deltaSeconds);
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

	void SetTimer(float _length, float _deviation);

	void SetRandomLocation();

	void MoveToRandomLocation();

	Gunner* GetTurretRef();

	float GetHealth();

	void SetHealth(float _maxHealth);

protected:
	Gunner* Turret;

	Entity* PlayerRef;

	CustomTimer ShootingTimer;

	Driscoll::Vector2D RandomMoveToLocation;

	float BulletSpeed;
	
	float BulletLifetime;

	float Health; 

	bool bLastHit;

	bool bFlipFlop;

	float SwitchingColorTime;
};

