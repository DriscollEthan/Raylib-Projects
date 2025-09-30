#include "Entity.h"
#include "DriscollMathUtils.h"
#include <iostream>

/* CONSTRUCTORS & DESTRUCTORS */

//DEFAULT CONSTRUCTOR
Entity::Entity(Driscoll::Vector2D _position, size_t _textureLocation, Driscoll::Vector2D _origin, Driscoll::Vector2D _scale, float _radius, float _rotation, float _speed)
{
	E_Position = _position;
	TextureIndex = _textureLocation;
	E_Origin = _origin;
	E_Scale = _scale;
	E_Radius = _radius;
	E_MovementVector = Driscoll::Vector2D();
	E_Rotation = _rotation;
	E_Speed = _speed;
	TextureManagerRef = nullptr;
}

//Copy Constructor
Entity::Entity(const Entity& _other)
{
	E_Position = _other.E_Position;
	TextureIndex = _other.TextureIndex;
	E_Origin = _other.E_Origin;
	E_Scale = _other.E_Scale;
	E_Radius = _other.E_Radius;
	E_MovementVector = _other.E_MovementVector;
	E_Speed = _other.E_Speed;
	E_Rotation = _other.E_Rotation;
	TextureManagerRef = _other.TextureManagerRef;
}

//Copy Assignment
Entity Entity::operator=(const Entity& _other)
{
	E_Position = _other.E_Position;
	TextureIndex = _other.TextureIndex;
	E_Origin = _other.E_Origin;
	E_Scale = _other.E_Scale;
	E_Radius = _other.E_Radius;
	E_MovementVector = _other.E_MovementVector;
	E_Speed = _other.E_Speed;
	E_Rotation = _other.E_Rotation;
	TextureManagerRef = _other.TextureManagerRef;
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

	GVO = GlobalVariables();
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