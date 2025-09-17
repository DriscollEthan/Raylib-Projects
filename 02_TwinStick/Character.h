#pragma once
#include "Player.h"

class Character : public Player
{
public:
	/* CONSTRUCTORS & DESTRUCTORS */
	//DEFAULT CONSTRUCTOR
	Character();

	/*Variable Constructors*/
	//SET Position Only
	Character(Driscoll::Vector2D _position);

	//SET Texture BY IMAGE Only
	Character(raylib::Image _texture);

	//SET Radius Only
	Character(float _radius);

	//Set Position & Texture BY IMAGE Only
	Character(Driscoll::Vector2D _position, raylib::Image _texture);

	//Set Position & Radius
	Character(Driscoll::Vector2D _position, float _radius);

	//Set Texture & Radius
	Character(raylib::Image _texture, float _radius);

	//Set Position, Texture, & Radius
	Character(Driscoll::Vector2D _position, raylib::Image _texture, float _radius);

	//COPY CONSTRUCTOR
	Character(const Character& _other);

	//COPY ASSIGNMENT
	Character operator =(const Character& _other);

	//DESTRUCTOR
	~Character();

protected:
	/* VARIABLES */
	//TURRET POINTER


	//Input Arrays:
		//Movement: (WASD), (ARROW KEYS)
	FInput MovementInput[8];


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

	/* Character SPECIFIC GET FUNCTIONS */


	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* Character SPECIFIC SET FUNCTIONS */

};

