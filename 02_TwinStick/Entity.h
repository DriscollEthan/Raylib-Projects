#pragma once

#include "Object.h"
#include "../raylib-cpp/include/raylib-cpp.hpp"		//RAYLIB CPP
#include "Vector2D.h"

class Entity : public Object
{
public:
	/* CONSTRUCTORS & DESTRUCTORS */
	//DEFAULT CONSTRUCTOR
	Entity();

	/*Variable Constructors*/
	//SET Position Only
	Entity(Driscoll::Vector2D _position);
	
	//SET Texture BY IMAGE Only
	Entity(raylib::Image _texture);

	//SET Radius Only
	Entity(float _radius);

	//Set Position & Texture BY IMAGE Only
	Entity(Driscoll::Vector2D _position, raylib::Image _texture);

	//Set Position & Radius
	Entity(Driscoll::Vector2D _position, float _radius);

	//Set Texture & Radius
	Entity(raylib::Image _texture, float _radius);

	//Set Position, Texture, & Radius
	Entity(Driscoll::Vector2D _position, raylib::Image _texture, float _radius);

	//COPY CONSTRUCTOR
	Entity(const Entity& _other);

	//COPY ASSIGNMENT
	Entity operator =(const Entity& _other);

	//DESTRUCTOR
	~Entity();
	
protected:
	/* VARIABLES */

	Driscoll::Vector2D E_Position;

	raylib::TextureUnmanaged * E_Texture;

	float E_Radius;

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
	raylib::TextureUnmanaged * GetTexture();

	 /**
	 * Get Radius
	 *Returns Current Radius in a float
	 */
	float GetRadius();

	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* ENTITY SPECIFIC SET FUNCTION */
	//Set Position
	void SetPosition(Driscoll::Vector2D _newPosition);

	//Set Texture BY IMAGE Only
	void SetTexture(raylib::Image _textureImage);

	//Set Radius
	void SetRadius(float _newRadius);
};

