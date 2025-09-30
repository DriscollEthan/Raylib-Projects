#include "Entity.h"
#include <iostream>

/* CONSTRUCTORS & DESTRUCTORS */

//DEFAULT CONSTRUCTOR
Entity::Entity(Driscoll::Vector2D _position, size_t _textureLocation, Driscoll::Vector2D _origin, Driscoll::Vector2D _scale, float _radius, float _rotation, float _speed)
{
	E_Position = _position;
	E_TextureLocation = _textureLocation;
	E_Origin = _origin;
	E_Scale = _scale;
	E_Radius = _radius;
	E_MovementVector = Driscoll::Vector2D();
	E_Rotation = _rotation;
	E_Speed = _speed;
	E_TextureManagerRef = nullptr;
}

//Copy Constructor
Entity::Entity(const Entity& _other)
{
	E_Position = _other.E_Position;
	E_TextureLocation = _other.E_TextureLocation;
	E_Origin = _other.E_Origin;
	E_Scale = _other.E_Scale;
	E_Radius = _other.E_Radius;
	E_MovementVector = _other.E_MovementVector;
	E_Speed = _other.E_Speed;
	E_Rotation = _other.E_Rotation;
	E_TextureManagerRef = _other.E_TextureManagerRef;
}

//Copy Assignment
Entity Entity::operator=(const Entity& _other)
{
	E_Position = _other.E_Position;
	E_TextureLocation = _other.E_TextureLocation;
	E_Origin = _other.E_Origin;
	E_Scale = _other.E_Scale;
	E_Radius = _other.E_Radius;
	E_MovementVector = _other.E_MovementVector;
	E_Speed = _other.E_Speed;
	E_Rotation = _other.E_Rotation;
	E_TextureManagerRef = _other.E_TextureManagerRef;
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

	GVO = GlobalVariableObject();
}

//Update: Called Every Tick in the Update Section && MUST BE USER CALLED
void Entity::Update()
{
	Object::Update();
}

//Draw: Called Every Tick in the Draw Section && MUST BE USER CALLED
void Entity::Draw()
{
	Object::Draw();
	//	Driscoll::Vector2D offset = {};
	//	offset.x -= E_Texture->GetWidth() / 2.0f;
	//	offset.y -= E_Texture->GetHeight() / 2.0f;
	//	E_Texture->Draw(E_Position - offset, E_Rotation);
	//
	//	std::cout << E_Position - offset << std::endl;
	GetTextureManagerRef()->GetTexture(E_TextureLocation).Draw(raylib::Rectangle(0, 0, (float)GetTextureManagerRef()->GetTexture(E_TextureLocation).GetWidth(), (float)GetTextureManagerRef()->GetTexture(E_TextureLocation).GetHeight()),						// SourceRec
			raylib::Rectangle(E_Position.x, E_Position.y, (float)GetTextureManagerRef()->GetTexture(E_TextureLocation).GetWidth() * E_Scale.x, (float)GetTextureManagerRef()->GetTexture(E_TextureLocation).GetHeight() * E_Scale.y),	// DestRec
			Driscoll::Vector2D((float)GetTextureManagerRef()->GetTexture(E_TextureLocation).GetWidth() * E_Origin.x * E_Scale.x, (float)GetTextureManagerRef()->GetTexture(E_TextureLocation).GetHeight() * E_Origin.y * E_Scale.y),		// Origin
			E_Rotation,	// Rotation
			Driscoll::Color::White() // Tint
		);
}

void Entity::GotHit()
{
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

bool Entity::CollisionCheck(Entity& _otherObject)
{
	if (CheckCollisionCircles(E_Position, E_Radius, _otherObject.E_Position, _otherObject.E_Radius))
	{
		GotHit();
		_otherObject.GotHit();
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

void Entity::SetTextureManagerRef(TextureManager* _newRef)
{
	E_TextureManagerRef = _newRef;
}

void Entity::SetTexturePosition(size_t _newPosition)
{
	E_TextureLocation = _newPosition;
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
	E_Position = Wrap(E_Position, Driscoll::Vector2D(0, 0), GVO.GetScreenSize());
}

//Rotate Entity
void Entity::Rotate(float _newRotation)
{
	E_Rotation = _newRotation;
}

//Wrap Vector
Driscoll::Vector2D Entity::Wrap(Driscoll::Vector2D _currentVector, Driscoll::Vector2D _min, Driscoll::Vector2D _max)
{
	//Over Max on X-Axis Wrapper
	if (_currentVector.x > _max.x)
	{
		float overFlow = _currentVector.x - _max.x;
		if (overFlow > _max.x)
		{
			overFlow /= _max.x;
			int overFlowTruncated = overFlow;

			overFlow -= overFlowTruncated;

			_currentVector.x = overFlow * _max.x;
		}
		else
		{
			_currentVector.x = overFlow;
		}
	}
	//Under Min on X-Axis Wrapper
	else if (_currentVector.x < _min.x)
	{
		float overFlow = _max.x - _currentVector.x;

		if (overFlow > _max.x)
		{
			overFlow /= _max.x;
			int overFlowTruncated = overFlow;

			overFlow -= overFlowTruncated;

			_currentVector.x = _max.x - overFlow;
		}
		else
		{
			_currentVector.x = overFlow;
		}
	}
	//Over Max on Y-Axis Wrapper
	if (_currentVector.y > _max.y)
	{
		float overFlow = _currentVector.y - _max.y;
		if (overFlow > _max.y)
		{
			overFlow /= _max.y;
			int overFlowTruncated = overFlow;

			overFlow -= overFlowTruncated;

			_currentVector.y = overFlow * _max.y;
		}
		else
		{
			_currentVector.y = overFlow;
		}
	}
	//Under Min on Y-Axis Wrapper
	else if (_currentVector.y < _min.y)
	{
		float overFlow = _max.y - _currentVector.y;

		if (overFlow > _max.y)
		{
			overFlow /= _max.y;
			int overFlowTruncated = overFlow;

			overFlow -= overFlowTruncated;

			_currentVector.y = _max.y - overFlow;
		}
	}

	return _currentVector;
}

TextureManager* Entity::GetTextureManagerRef()
{
	if (!E_TextureManagerRef)
	{
		std::cout << "[1;31mWARNING: NO TEXTURE MANAGER REF SET IN ENTITY: RETURN NULLPTR \033[0m" << std::endl;
	}
	return E_TextureManagerRef;
}
