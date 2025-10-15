#pragma once
#include "Player.h"
#include "Gunner.h"

enum EUpgradeType
{
	EBullet,
	ETank,
	ETurret,
	ENone
};

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
	Driscoll::Vector2D BulletScale;

	Timer ShootingTimer;

	//Input Arrays:
		//Movement: (WASD), (ARROW KEYS)
		FInput MovementInput[8];

		//Shoot: (Left Click) (Space Bar)
		FInput ShootInput[2];

		//Pause (Esc) (End)
		FInput PauseInput[2];
		bool bShouldPause;

	//Health
		float Health;

		float DamageToTake;

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

	void CheckPauseInput();

	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* Character SPECIFIC GET FUNCTIONS */

	Gunner* GetTurretRef();

	float GetHealth();

	bool bIsHit();

	bool GetLastHit();

	bool GetShouldPause();

	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* Character SPECIFIC SET FUNCTIONS */
	void SetHealth(float _maxHealth);

	void SetShouldBePaused(bool _shouldBePaused);

	void IncreaseDifficulty(int _round);

	void UpgradePlayer(EUpgradeType _type, int _currentRound);

};

