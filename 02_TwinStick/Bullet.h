#pragma once
#include "Entity.h"


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
	Bullet(Driscoll::Vector2D _position = { 0,0 }, raylib::Image _texture = {}, Driscoll::Vector2D _origin = { 0,0 }, Driscoll::Vector2D _scale = { 1,1 }, float _radius = 0.0f, float _rotation = 0.0f, float _speed = 1.0f);

	//COPY CONSTRUCTOR
	Bullet(const Bullet& _other);

	//COPY ASSIGNMENT
	Bullet operator =(const Bullet& _other);

	//DESTRUCTOR
	virtual ~Bullet();

protected:
	/* VARIABLES */

	//Input Arrays:

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


	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* BULLET SPECIFIC SET FUNCTIONS */

	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* BULLET ONLY FUNCTIONS */

};

