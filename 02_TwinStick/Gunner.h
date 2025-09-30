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
		* LocalData as a Driscoll::LocalData	| Default: Pos = 0,0; Rot = 0; Scale = 1,1;
		* TextureIndex as size_t							| Default: 0
		* Hitbox as a HitboxData							| Default: Position = 0, Radius = 0;
		* Speed as a float										| Default: 1.0
		* MaxBulletsInPool as size_t					| Default 0
		* BulletTextureIndex as a size_t			|	Default 0
		*/
	Gunner(LocalData2D _localData = {}, size_t _textureIndex = 0, Driscoll::Vector2D _origin = { 0,0 }, HitboxData _hitbox = {}, float _speed = 1.0f, size_t _maxBulletsInPool = 0, size_t _bulletTextureIndex = 0);
	
	Gunner(const Gunner& _other);

	Gunner operator=(const Gunner& _other);

	//DESTRUCTOR
	virtual ~Gunner();

protected:
	/* VARIABLES */
	//Array of Bullets || USE OBJECT POOLING WITH HEAP MEMORY
	class Bullet* BulletsInPool;
	
	//MAX_BULLETS_IN_POOL Should Equal: (Limetime * 10) + 10  ||  For adding a minor buffer from obtainably max by about 5 and not having too many objects spawned, based on speed clicking. 
	size_t MAX_BULLETS_IN_POOL;  

	int WhichBulletToUse;

	size_t BulletTextureIndex;

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

	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* Gunner SPECIFIC FUNCTIONS */

	//BulletCollisionCheck: Checks every active Bullet against the Collision Object.
	void BulletCollisionCheck(Entity* _enemy);

	//Shoot: Shoots the next available Bullet
	void Shoot(float _speed, float _lifetime);

};

