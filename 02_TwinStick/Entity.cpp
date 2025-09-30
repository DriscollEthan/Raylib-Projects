#include "Entity.h"
#include "DriscollMathUtils.h"
#include <iostream>

/* CONSTRUCTORS & DESTRUCTORS */

//DEFAULT CONSTRUCTOR
Entity::Entity(Driscoll::LocalData2D _localData, size_t _textureLocation, Driscoll::Vector2D _origin, float _radius, float _speed)
{
	LocalData = _localData;
	E_Origin = _origin;
	Radius = _radius;
	E_MovementVector = Driscoll::Vector2D();
	E_Speed = _speed;
}

//Copy Constructor
Entity::Entity(const Entity& _other)
{

	E_Origin = _other.E_Origin;
	Radius = _other.Radius;
	E_MovementVector = _other.E_MovementVector;
	E_Speed = _other.E_Speed;
}

//Copy Assignment
Entity Entity::operator=(const Entity& _other)
{
	E_Origin = _other.E_Origin;
	Radius = _other.Radius;
	E_MovementVector = _other.E_MovementVector;
	E_Speed = _other.E_Speed;
	return *this;
}

//Destructor
Entity::~Entity()
{

}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* FUNCTIONS */

/* OBJECT VIRTUAL FUNCTION OVERRIDES */
//Begin Play: Called Before Start of Main Game Loop && MUST BE USER CALLED
void Entity::BeginPlay()
{
	Object::BeginPlay();
}

//Update: Called Every Tick in the Update Section && MUST BE USER CALLED
void Entity::Update()
{
	Object::Update();
}

//Draw: Called Every Tick in the Draw Section && MUST BE USER CALLED
void Entity::Draw()
{
	if (bIsAlive)
	{
		Object::Draw();
		//	Driscoll::Vector2D offset = {};
		//	offset.x -= E_Texture->GetWidth() / 2.0f;
		//	offset.y -= E_Texture->GetHeight() / 2.0f;
		//	E_Texture->Draw(E_Position - offset, E_Rotation);
		//
		//	std::cout << E_Position - offset << std::endl;
		GetTextureManagerRef()->GetTexture(TextureIndex).Draw(raylib::Rectangle(0, 0, (float)GetTextureManagerRef()->GetTexture(TextureIndex).GetWidth(), (float)GetTextureManagerRef()->GetTexture(TextureIndex).GetHeight()),						// SourceRec
			raylib::Rectangle(E_Position.x, E_Position.y, (float)GetTextureManagerRef()->GetTexture(TextureIndex).GetWidth() * E_Scale.x, (float)GetTextureManagerRef()->GetTexture(TextureIndex).GetHeight() * E_Scale.y),	// DestRec
			Driscoll::Vector2D((float)GetTextureManagerRef()->GetTexture(TextureIndex).GetWidth() * E_Origin.x * E_Scale.x, (float)GetTextureManagerRef()->GetTexture(TextureIndex).GetHeight() * E_Origin.y * E_Scale.y),		// Origin
			E_Rotation,	// Rotation
			Driscoll::Color::White() // Tint
		);
	}
}

void Entity::GotHit()
{
	std::cout << "thing \n";
}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* ENTITY SPECIFIC GET FUNCTIONS */	
//Get Position
Driscoll::Vector2D Entity::GetPosition()
{
	return E_Position;
}

//Get Radius
float Entity::GetRadius()
{
	return E_Radius;
}

bool Entity::CollisionCheck(Entity* _otherObject)
{
	if (CheckCollisionCircles(E_Position, E_Radius, _otherObject->E_Position, _otherObject->E_Radius))
	{
		GotHit();
		_otherObject->GotHit();
		return true;
	}
	return false;
}

bool Entity::GetIsAlive()
{
	return bIsAlive;
}


/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* ENTITY SPECIFIC SET FUNCTIONS */


//Set Position
void Entity::SetPosition(Driscoll::Vector2D _newPosition)
{
	E_Position = _newPosition;
}

//Set Scale
void Entity::SetScale(Driscoll::Vector2D _newScale)
{
	E_Scale = _newScale;
}

//Set Radius
void Entity::SetRadius(float _newRadius)
{
	E_Radius = _newRadius;
}

void Entity::SetIsAlive(bool _isAlive)
{
	bIsAlive = _isAlive;
}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* ENTITY ONLY FUNCTIONS */
//Move Entity
void Entity::Move()
{
	E_Position += E_MovementVector.SafeNormalised() * (E_Speed * GetFrameTime() * 100.0f);
	E_Position = Driscoll::Vector2D::WrapVector2D(E_Position, Driscoll::Vector2D(0, 0), GVO.GetScreenSize());
}

//Rotate Entity
void Entity::Rotate(float _newRotation)
{
	E_Rotation = _newRotation;
}