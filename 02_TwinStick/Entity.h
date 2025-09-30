#pragma once

#include "Object.h"
#include "DriscollMathUtils.h"
#include "GlobalVariableObject.h"
#include "TextureManager.h"

class Entity : public Object
{
public:
	/* CONSTRUCTORS & DESTRUCTORS */
	/**
		* DEFAULT CONSTRUCTOR: 
		* Parameters:
		* LocalData as a Driscoll::LocalData	| Default: Pos = 0,0; Rot = 0; Scale = 1,1;
		* Texture as an Image									| Default: Default Constructor
		* Radius as a Float										| Default: 0.0
		* Rotation as a Float									| Default: 0.0
		* Speed as a flaot										| Default: 1.0
		*/
	Entity(Driscoll::LocalData2D _localData = {}, size_t _textureLocation = 0, Driscoll::Vector2D _origin = { 0,0 }, float _radius = 0.0f, float _speed = 1.0f);

	//COPY CONSTRUCTOR
	Entity(const Entity& _other);

	//COPY ASSIGNMENT
	Entity operator =(const Entity& _other);

	//DESTRUCTOR
	virtual ~Entity();
	
protected:
	/* VARIABLES */
	Driscoll::LocalData2D LocalData;

	Driscoll::Vector2D E_MovementVector;

	float Radius;

	float E_Speed;

	bool bIsAlive = true;

	//Origin Offset (0-1)
	Driscoll::Vector2D E_Origin;

public:
	/* FUNCTIONS */

	/* OBJECT VIRTUAL FUNCTION OVERRIDES */
	//Begin Play: Called Before Start of Main Game Loop && MUST BE USER CALLED
	virtual void BeginPlay() override;

	//Update: Called Every Tick in the Update Section && MUST BE USER CALLED
	virtual void Update() override;

	//Draw: Called Every Tick in the Draw Section && MUST BE USER CALLED
	virtual void Draw() override;

	//Collided: Called when Collision is detected.
	virtual void GotHit();

	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* ENTITY SPECIFIC GET FUNCTIONS */
	/**
	 * Get Position
	 *Returns Current Position in a Vector2D
	 */
	Driscoll::Vector2D GetPosition();

	 /**
	 * Get Radius:
	 *Returns Current Radius in a float
	 */
	float GetRadius();

	/**
		* Collision Check
		* Takes in Another Entity to Check Collision With
		*Returns bool Is Colliding
		*/
	virtual bool CollisionCheck(Entity* _otherObject);

	bool GetIsAlive();

	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* ENTITY SPECIFIC SET FUNCTION */
	//Set Position
	virtual void SetPosition(Driscoll::Vector2D _newPosition);

	//Set Scale
	virtual void SetScale(Driscoll::Vector2D _newScale);

	//Set Radius
	void SetRadius(float _newRadius);

	void SetIsAlive(bool _isAlive);

	void Move();

	void Rotate(float _newRotation);
};

