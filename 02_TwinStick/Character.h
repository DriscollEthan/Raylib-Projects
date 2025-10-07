#pragma once
#include "Player.h"
#include "Gunner.h"

class Character : public Player
{
public:
	/* CONSTRUCTORS & DESTRUCTORS */
	/**
		* DEFAULT CONSTRUCTOR:
		* Parameters:
		* LocalData as a Driscoll::LocalData	| Default: Pos = 0,0; Rot = 0; Scale = 1,1;
		* TextureIndex as size_t							| Default: 0
		* Hitbox as a HitboxData							| Default: Position = 0, Radius = 0;
		* Speed as a float										| Default: 1.0
		* BulletSpeed as a float							| Default 0.0
		* BulletLifetime as a float						| Default 0.0
		*/
	Character(LocalData2D _localData = {}, size_t _texturePosition = 0, Driscoll::Vector2D _origin = { 0,0 }, HitboxData _hitbox = {}, float _speed = 1.0f, float _bulletLifetime = 0.0f, float _bulletSpeed = 0.0f);

	//COPY CONSTRUCTOR
	Character(const Character& _other);

	//COPY ASSIGNMENT
	Character operator =(const Character& _other);

	//DESTRUCTOR
	virtual ~Character();

protected:
	/* VARIABLES */
	//TURRET POINTER
	Gunner* Turret; 

	float BulletSpeed;
	float BulletLifetime;

	Timer ShootingTimer;

	//Input Arrays:
		//Movement: (WASD), (ARROW KEYS)
		FInput MovementInput[8];

		//Shoot: (Left Click) (Space Bar)
		FInput ShootInput[2];

	//Health
		int Health;

		bool bLastHit;

		bool bFlipFlop;

		Timer SwitchingColorTimer;

		bool bShowHit;

		Timer HitColorShowingTimer;

		Timer SwitchHitColorTimer;

	//Dead Stuff
		Timer DeadExplosionCountingTimer;
		int ExplosionIterationCount;


public:
	/* FUNCTIONS */

	/* OBJECT VIRTUAL FUNCTION OVERRIDES */
	//Begin Play: Called Before Start of Main Game Loop && MUST BE USER CALLED
	virtual void BeginPlay() override;

	//Update: Called Every Tick in the Update Section && MUST BE USER CALLED
	virtual void Update() override;

	//Draw: Called Every Tick in the Draw Section && MUST BE USER CALLED
	virtual void Draw() override;

	virtual void GotHit() override;

	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* Character SPECIFIC GET FUNCTIONS */

	Gunner* GetTurretRef();

	float GetHealth();

	bool bIsHit();

	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* Character SPECIFIC SET FUNCTIONS */
	void SetHealth(float _maxHealth);

};

