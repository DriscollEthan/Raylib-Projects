#pragma once
#include "Entity.h"


class Player : public Entity
{
public:
	/* CONSTRUCTORS & DESTRUCTORS */
	//DEFAULT CONSTRUCTOR
	Player();

	/*Variable Constructors*/
	//SET Position Only
	Player(Driscoll::Vector2D _position);

	//SET Texture BY IMAGE Only
	Player(raylib::Image _texture);

	//SET Radius Only
	Player(float _radius);

	//Set Position & Texture BY IMAGE Only
	Player(Driscoll::Vector2D _position, raylib::Image _texture);

	//Set Position & Radius
	Player(Driscoll::Vector2D _position, float _radius);

	//Set Texture & Radius
	Player(raylib::Image _texture, float _radius);

	//Set Position, Texture, & Radius
	Player(Driscoll::Vector2D _position, raylib::Image _texture, float _radius);

	//COPY CONSTRUCTOR
	Player(const Player& _other);

	//COPY ASSIGNMENT
	Player operator =(const Player& _other);

	//DESTRUCTOR
	~Player();

protected:
	/* VARIABLES */
	//TURRET POINTER

	Driscoll::Vector2D MovementVector;

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

	/* ENTITY SPECIFIC GET FUNCTIONS */

};

