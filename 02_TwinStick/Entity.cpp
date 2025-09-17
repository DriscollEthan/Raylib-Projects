#include "Entity.h"

/* CONSTRUCTORS & DESTRUCTORS */

//DEFAULT CONSTRUCTOR
Entity::Entity(Driscoll::Vector2D _position, raylib::Image _texture, float _radius, float _rotation, float _speed)
{
	E_Position = _position;
	E_Texture = new raylib::TextureUnmanaged(_texture);
	E_Radius = _radius;
	E_MovementVector = Driscoll::Vector2D();
	E_Rotation = _rotation;
	E_Speed = _speed;
}

//Copy Constructor
Entity::Entity(const Entity& _other)
{
	E_Position = _other.E_Position;
	E_Texture = new raylib::TextureUnmanaged(_other.E_Texture->GetData());
	E_Radius = _other.E_Radius;
	E_MovementVector = _other.E_MovementVector;
	E_Speed = _other.E_Speed;
	E_Rotation = _other.E_Rotation;
}

//Copy Assignment
Entity Entity::operator=(const Entity& _other)
{
	E_Position = _other.E_Position;
	E_Texture = new raylib::TextureUnmanaged(_other.E_Texture->GetData());
	E_Radius = _other.E_Radius;
	E_MovementVector = _other.E_MovementVector;
	E_Speed = _other.E_Speed;
	E_Rotation = _other.E_Rotation;
	return *this;
}

//Destructor
Entity::~Entity()
{
	if (E_Texture != nullptr)
	{
		delete E_Texture;
	}
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
	if (E_Texture != nullptr)
	{
		Driscoll::Vector2D offset = Driscoll::Vector2D();
		offset.x = (E_Texture->GetWidth() / 2.0f);
		offset.y = (E_Texture->GetHeight() / 2.0f);
		E_Texture->Draw(E_Position - offset, E_Rotation);
	}
}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* ENTITY SPECIFIC GET FUNCTIONS */	
//Get Position
Driscoll::Vector2D Entity::GetPosition()
{
	return E_Position;
}

//Get Texture
raylib::TextureUnmanaged * Entity::GetTexture()
{
	return E_Texture;
}

//Get Radius
float Entity::GetRadius()
{
	return E_Radius;
}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* ENTITY SPECIFIC GET FUNCTIONS */

//Set Position
void Entity::SetPosition(Driscoll::Vector2D _newPosition)
{
	E_Position = _newPosition;
}

//Set Texture BY IMAGE only
void Entity::SetTexture(raylib::Image _textureImage)
{
	if (E_Texture == nullptr)
	{
		E_Texture = new raylib::TextureUnmanaged(_textureImage);
	}
	else
	{
		delete E_Texture;
		E_Texture = E_Texture = new raylib::TextureUnmanaged(_textureImage);
	}
}

//Set Radius
void Entity::SetRadius(float _newRadius)
{
	E_Radius = _newRadius;
}
