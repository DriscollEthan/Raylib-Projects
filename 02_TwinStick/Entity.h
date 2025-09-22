#pragma once

#include "Object.h"
#include "../raylib-cpp/include/raylib-cpp.hpp"		//RAYLIB CPP
#include "Vector2D.h"
#include "GlobalVariableObject.h"

class Entity : public Object
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
	Entity(Driscoll::Vector2D _position = { 0,0 }, raylib::Image _texture = {}, Driscoll::Vector2D _origin = { 0,0 }, Driscoll::Vector2D _scale = { 1,1 }, float _radius = 0.0f, float _rotation = 0.0f, float _speed = 1.0f);

	//COPY CONSTRUCTOR
	Entity(const Entity& _other);

	//COPY ASSIGNMENT
	Entity operator =(const Entity& _other);

	//DESTRUCTOR
	virtual ~Entity();
	
protected:
	/* VARIABLES */
	class GlobalVariableObject GVO;

	Driscoll::Vector2D E_Position;

	raylib::Texture E_Texture;

	float E_Radius;

	Driscoll::Vector2D E_MovementVector;

	float E_Rotation = 0.0f;

	float E_Speed;

	//Origin Offset (0-1)
	Driscoll::Vector2D E_Origin;

	Driscoll::Vector2D E_Scale;

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

	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* ENTITY SPECIFIC GET FUNCTIONS */
	/**
	 * Get Position
	 *Returns Current Position in a Vector2D
	 */
	Driscoll::Vector2D GetPosition();

	 /**
	 * Get Texture
	 * MUST BE CHECKED FOR NULLPTR ON CALLING
	 *Returns Pointer To Current Texture
	 */
	raylib::Texture GetTexture();

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
	virtual bool CollisionCheck(Entity& _otherObject);

	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* ENTITY SPECIFIC SET FUNCTION */
	//Set Position
	virtual void SetPosition(Driscoll::Vector2D _newPosition);

	virtual void SetScale(Driscoll::Vector2D _newScale);

	//Set Texture BY IMAGE Only
	void SetTexture(raylib::Image _textureImage);

	//Set Radius
	void SetRadius(float _newRadius);


	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/
	/* ENTITY SPECIFC FUNCTIONS */
	void Move();

	void Rotate(float _newRotation);

	Driscoll::Vector2D Wrap(Driscoll::Vector2D _currentVector, Driscoll::Vector2D _min, Driscoll::Vector2D _max);
	
};

