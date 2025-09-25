#pragma once
#include "Entity.h"

enum EState
{
	None,
	Inactive,
	Active
};

class Bullet : public Entity
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
	Bullet(Driscoll::Vector2D _position = { 0,0 }, size_t _texturePosition = 0, Driscoll::Vector2D _origin = { 0,0 }, Driscoll::Vector2D _scale = { 1,1 }, float _radius = 0.0f, float _rotation = 0.0f, float _speed = 1.0f);

	//COPY CONSTRUCTOR
	Bullet(const Bullet& _other);

	//COPY ASSIGNMENT
	Bullet operator =(const Bullet& _other);

	//DESTRUCTOR
	virtual ~Bullet();

protected:
	/* VARIABLES */
	EState CurrentState;

	float TimeAlive;

	float TimeToLive;

public:
	/* FUNCTIONS */

	/* OBJECT VIRTUAL FUNCTION OVERRIDES */
	//Begin Play: Called Before Start of Main Game Loop && MUST BE USER CALLED
	virtual void BeginPlay() override;

	//Update: Called Every Tick in the Update Section && MUST BE USER CALLED
	virtual void Update() override;

	//Draw: Called Every Tick in the Draw Section && MUST BE USER CALLED
	virtual void Draw() override;

	virtual bool CollisionCheck(Entity& _otherObject) override;

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

};

