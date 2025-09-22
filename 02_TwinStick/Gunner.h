#pragma once
#include "Player.h"
#include "Bullet.h"

class Gunner : public Player
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
	Gunner(Driscoll::Vector2D _position = { 0,0 }, raylib::Image _texture = {}, Driscoll::Vector2D _origin = { 0,0 }, Driscoll::Vector2D _scale = { 1,1 }, float _radius = 0.0f, float _rotation = 0.0f, float _speed = 1.0f);
	
	Gunner(const Gunner& _other);

	Gunner operator=(const Gunner& _other);

	//DESTRUCTOR
	virtual ~Gunner();

protected:
	/* VARIABLES */
	//Array of Bullets || USE OBJECT POOLING WITH HEAP MEMORY
	class Bullet* BulletsInPool;

	const int MAX_BULLETS_IN_POOL = 60; //MAX_BULLETS_IN_POOL Should Equal: (Limetime * 10) + 10  ||  For adding a minor buffer from obtainably max by about 5 and not having too many objects spawned, based on speed clicking.  

	int WhichBulletToUse;

	Driscoll::Vector2D ScaleMult;

	//Input Arrays:
		//Movement: (WASD), (ARROW KEYS)
	FInput ShootInput[2];


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

	/* Gunner SPECIFIC GET FUNCTIONS */


	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* Gunner SPECIFIC SET FUNCTIONS */

	virtual void SetScale(Driscoll::Vector2D _newScale) override;

};

