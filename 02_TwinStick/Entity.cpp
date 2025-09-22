#include "Entity.h"
#include <iostream>

/* CONSTRUCTORS & DESTRUCTORS */

//DEFAULT CONSTRUCTOR
Entity::Entity(Driscoll::Vector2D _position, raylib::Image _texture, Driscoll::Vector2D _origin, Driscoll::Vector2D _scale, float _radius, float _rotation, float _speed)
{
	E_Position = _position;
	if (_texture.IsValid())
	{
		E_Texture = _texture;
	}
	else
	{
		E_Texture.Load("Resources/DEFAULT.png"); \
			std::cout << "WARNING: AN ENTITY WAS CONSTRUCTED WITHOUT A VALID IMAGE, USING DEFAULT IMAGE \n";
	}
	E_Origin = _origin;
	E_Scale = _scale;
	E_Radius = _radius;
	E_MovementVector = Driscoll::Vector2D();
	E_Rotation = _rotation;
	E_Speed = _speed;
}

//Copy Constructor
Entity::Entity(const Entity& _other)
{
	E_Position = _other.E_Position;
	E_Texture = _other.E_Texture;
	E_Origin = _other.E_Origin;
	E_Scale = _other.E_Scale;
	E_Radius = _other.E_Radius;
	E_MovementVector = _other.E_MovementVector;
	E_Speed = _other.E_Speed;
	E_Rotation = _other.E_Rotation;
}

//Copy Assignment
Entity Entity::operator=(const Entity& _other)
{
	E_Position = _other.E_Position;
	E_Texture = _other.E_Texture;
	E_Origin = _other.E_Origin;
	E_Scale = _other.E_Scale;
	E_Radius = _other.E_Radius;
	E_MovementVector = _other.E_MovementVector;
	E_Speed = _other.E_Speed;
	E_Rotation = _other.E_Rotation;
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

		E_Texture.Draw(raylib::Rectangle(0, 0, (float)E_Texture.GetWidth(), (float)E_Texture.GetHeight()),						// SourceRec
			raylib::Rectangle(E_Position.x, E_Position.y, (float)E_Texture.GetWidth() * E_Scale.x, (float)E_Texture.GetHeight() * E_Scale.y),	// DestRec
			Driscoll::Vector2D((float)E_Texture.GetWidth() * E_Origin.x * E_Scale.x, (float)E_Texture.GetHeight() * E_Origin.y * E_Scale.y),		// Origin
			E_Rotation,	// Rotation
			raylib::Color::White() // Tint
		);
}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* ENTITY SPECIFIC GET FUNCTIONS */	
//Get Position
Driscoll::Vector2D Entity::GetPosition()
{
	return E_Position;
}

//Get Texture
raylib::Texture Entity::GetTexture()
{
	return E_Texture;
}

//Get Radius
float Entity::GetRadius()
{
	return E_Radius;
}

bool Entity::CollisionCheck(Entity& _otherObject)
{
	return CheckCollisionCircles(E_Position, E_Radius, _otherObject.E_Position, _otherObject.E_Radius);
}


/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* ENTITY SPECIFIC SET FUNCTIONS */


//Set Position
void Entity::SetPosition(Driscoll::Vector2D _newPosition)
{
	E_Position = _newPosition;
}

void Entity::SetScale(Driscoll::Vector2D _newScale)
{
	E_Scale = _newScale;
}

//Set Texture BY IMAGE only
void Entity::SetTexture(raylib::Image _textureImage)
{
	E_Texture = _textureImage;
}

//Set Radius
void Entity::SetRadius(float _newRadius)
{
	E_Radius = _newRadius;
}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* PLAYER ONLY FUNCTIONS */
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
