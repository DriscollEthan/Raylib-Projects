#pragma once
#include "Entity.h"

enum EState
{
	None,
	Inactive,
	Active,
	Explosion,
	NonDeadlyExplosion
};

class Bullet : public Entity
{
public:
	/* CONSTRUCTORS & DESTRUCTORS */
	/**
		/**
		* DEFAULT CONSTRUCTOR: 
		* Parameters:
		* LocalData as a Driscoll::LocalData	| Default: Pos = 0,0; Rot = 0; Scale = 1,1;
		* TextureIndex as size_t							| Default: 0
		* Hitbox as a HitboxData							| Default: Position = 0, Radius = 0;
		* Speed as a float										| Default: 1.0
		*/
	Bullet(LocalData2D _localData = {}, size_t _textureLocation = 0, Driscoll::Vector2D _origin = { 0,0 }, HitboxData _hitbox = {}, float _speed = 1.0f);

	//COPY CONSTRUCTOR
	Bullet(const Bullet& _other);

	//COPY ASSIGNMENT
	Bullet operator =(const Bullet& _other);

	//DESTRUCTOR
	virtual ~Bullet();

protected:
	/* VARIABLES */
	EState CurrentState;

	Timer LivingTimer;

	Timer ExplosionTimer;

	int ExplosionIterations;

public:
	/* FUNCTIONS */

	/* OBJECT VIRTUAL FUNCTION OVERRIDES */
	//Begin Play: Called Before Start of Main Game Loop && MUST BE USER CALLED
	virtual void BeginPlay() override;

	//Update: Called Every Tick in the Update Section && MUST BE USER CALLED
	virtual void Update() override;

	//Draw: Called Every Tick in the Draw Section && MUST BE USER CALLED
	virtual void Draw() override;

	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* BULLET INPUT FUNCTIONS */


	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* BULLET SPECIFIC GET FUNCTIONS */
	EState GetCurrentState();
	
	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* BULLET SPECIFIC SET FUNCTIONS */
	void SetCurrentState(EState _newState);

	void SetTimeToLive(float _newTimeToLive);

	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* BULLET ONLY FUNCTIONS */
	void SpawnBullet(Driscoll::Vector2D _spawnPosition, Driscoll::Vector2D _movementVector, float _speed, float _timeToLive);

	void IncreaseDifficulty(int _round);

};

