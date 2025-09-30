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
		* Position as a Driscoll::Vector2D	| Default: 0,0
		* Texture as an Image								| Default: Default Constructor
		* Radius as a Float									| Default: 0.0
		* Rotation as a Float								| Default: 0.0
		* Speed as a Float									| Default: 1.0
		*/
	Character(Driscoll::Vector2D _position = { 0,0 }, size_t _texturePosition = 0, Driscoll::Vector2D _origin = { 0,0 }, Driscoll::Vector2D _scale = { 1,1 }, float _radius = 0.0f, float _rotation = 0.0f, float _speed = 1.0f);

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

	float BulletSpeed = 5.0f;
	float BulletLifetime = 5.0f;

	//Input Arrays:
		//Movement: (WASD), (ARROW KEYS)
		FInput MovementInput[8];

		//Shoot: (Left Click) (Space Bar)
		FInput ShootInput[2];

	//Enemy Refs
		Entity* EnemyRefs;
		size_t EnemyCount;

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

	bool BulletHitEnemy(Entity& _enemy);

	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* Character SPECIFIC GET FUNCTIONS */


	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* Character SPECIFIC SET FUNCTIONS */

	void SetEnemyRefs(Entity* _enemyRefs, size_t _count);

};

