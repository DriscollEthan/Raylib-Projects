#pragma once

#include "Object.h"
#include "DriscollMathUtils.h"
#include "GlobalVariableObject.h"
#include "TextureManager.h"

//STRUCT OF LOCAL DATA
struct LocalData2D
{
	Driscoll::Vector2D LocalPosition;
	float LocalRotation;
	Driscoll::Vector2D LocalScale;

	LocalData2D()
	{
		LocalPosition = { 0, 0 };
		LocalRotation = 0;
		LocalScale = { 1, 1 };
	}

	LocalData2D(Driscoll::Vector2D _position, float _rotation, Driscoll::Vector2D _scale)
	{
		LocalPosition = _position;
		LocalRotation = _rotation;
		LocalScale = _scale;
	}

	LocalData2D(const LocalData2D& _other)
	{
		LocalPosition = _other.LocalPosition;
		LocalRotation = _other.LocalRotation;
		LocalScale = _other.LocalScale;
	}

	LocalData2D operator =(const LocalData2D& _other)
	{
		LocalPosition = _other.LocalPosition;
		LocalRotation = _other.LocalRotation;
		LocalScale = _other.LocalScale;
		return *this;
	}
};

struct HitboxData
{
	Driscoll::Vector2D Position;
	float HitboxRadius;

	HitboxData()
	{
		Position = {};
		HitboxRadius = 0.f;
	}

	HitboxData(float _radius)
	{
		HitboxRadius = _radius;
	}

	HitboxData(const HitboxData& _other)
	{
		Position = _other.Position;
		HitboxRadius = _other.HitboxRadius;
	}

	HitboxData operator =(const HitboxData& _other)
	{
		Position = _other.Position;
		HitboxRadius = _other.HitboxRadius;
		return *this;
	}

	void SetHitbox(Driscoll::Vector2D _position, float _radius)
	{
		Position = _position;
		HitboxRadius = _radius;
	}

#ifdef RAYLIB_H
	// implicit Collision Checks with Raylib
	bool CheckCollision(HitboxData& _other)
	{
		return CheckCollisionCircles(Position, HitboxRadius, _other.Position, _other.HitboxRadius);
	}

	bool CheckCollision(HitboxData& _lhs, HitboxData& _rhs)
	{
		return _lhs.CheckCollision(_rhs);
	}
#endif
};

class Entity : public Object
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
		*/
	Entity(LocalData2D _localData = {}, size_t _textureLocation = 0, Driscoll::Vector2D _origin = { 0,0 }, HitboxData _hitbox = {}, float _speed = 1.0f);

	//COPY CONSTRUCTOR
	Entity(const Entity& _other);

	//COPY ASSIGNMENT
	Entity operator =(const Entity& _other);

	//DESTRUCTOR
	virtual ~Entity();
	
protected:
	/* VARIABLES */

	//Draw Data
		LocalData2D LocalData;
		//Origin Offset (0-1)
		Driscoll::Vector2D Origin;
		Driscoll::Matrix3 LocalMatrix;
		Driscoll::Matrix3 WorldMatrix;

	//Collision Data
		HitboxData Hitbox;

	//Movement Data
		Driscoll::Vector2D MovementVector;
		float Speed;

	//Parent Data
		Entity* Parent;

	//Other Data
		bool bIsAlive = true;

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
	 * Get Radius:
	 *Returns Current Radius in a float
	 */
	HitboxData& GetHitbox();

	/**
		* Collision Check
		* Takes in Another Entity to Check Collision With
		*Returns bool Is Colliding
		*/
	bool CollisionCheck(HitboxData& _otherHitbox);

	//Is this Entity 'Alive'
	bool GetIsAlive();

	/*
	 *	Get My Local Matrix:
	 *	Returns Local Matrix in a Matrix3
	 *	Multiplies My Translation Matrix, by My RotationZ Matrix, by my Scale Matrix.
	 */
	Driscoll::Matrix3 GetLocalMatrix();

	/*
	 *	Get My World Matrix:
	 *	Returns My Local Matrix * My Parent Matrix in a Matrix3 || My Local Matrix3 if I don't have a Parent
	 */
	Driscoll::Matrix3 GetWorldMatrix();

	/*
	 *	Get My World Position:
	 *	Returns a Vector2D of my World Position
	 */
	Driscoll::Vector2D GetWorldPosition();

	/*
	 *	Get My World Matrix:
	 *	Returns a Float of my World Rotation
	 */
	float GetWorldRotation();

	/*
	 *	Get My World Matrix:
	 *	Returns a Vector2D of my World Scale
	 */
	Driscoll::Vector2D GetWorldScale();

	/*** ------------------------------------------------------------------ *** ------------------------------------------------------------------ ***/

	/* ENTITY SPECIFIC SET FUNCTION */

	//Draw Data
		//Set Local Position
		void SetLocalPosition(Driscoll::Vector2D _newPosition);
		//Set Local Scale
		void SetLocalScale(Driscoll::Vector2D _newScale);
		//Set Local Rotation IN RADIANS
		void SetLocalRotation(float _newRotation);


	//Set Hitbox
		//Set Hitbox Radius
		void SetHitboxRadius(float _newRadius);
		//Set Hitbox Location
		void SetHitboxLocation(Driscoll::Vector2D _newPosition);

	//Movement
		//Move
		void Move();

	//Other
		//SetIsAlive
		void SetIsAlive(bool _isAlive);
		//Set Parent
		void SetParent(Entity* _newParent);

};

