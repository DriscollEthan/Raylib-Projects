#pragma once
#include "Player.h"

class Gunner : public Player
{
public:
	/* CONSTRUCTORS & DESTRUCTORS */
	//DEFAULT CONSTRUCTOR
	Gunner();

	/*Variable Constructors*/
	//SET Position Only
	Gunner(Driscoll::Vector2D _position);

	//SET Texture BY IMAGE Only
	Gunner(raylib::Image _texture);

	//SET Radius Only
	Gunner(float _radius);

	//Set Position & Texture BY IMAGE Only
	Gunner(Driscoll::Vector2D _position, raylib::Image _texture);

	//Set Position & Radius
	Gunner(Driscoll::Vector2D _position, float _radius);

	//Set Texture & Radius
	Gunner(raylib::Image _texture, float _radius);

	//Set Position, Texture, & Radius
	Gunner(Driscoll::Vector2D _position, raylib::Image _texture, float _radius);

	//COPY CONSTRUCTOR
	Gunner(const Gunner& _other);

	//COPY ASSIGNMENT
	Gunner operator =(const Gunner& _other);

	//DESTRUCTOR
	~Gunner();

protected:
	/* VARIABLES */
	//TURRET POINTER


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

};

