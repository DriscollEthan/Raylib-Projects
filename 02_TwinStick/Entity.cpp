#include "Entity.h"

/* CONSTRUCTORS & DESTRUCTORS */

//DEFAULT CONSTRUCTOR
Entity::Entity()
{
	E_Position = Driscoll::Vector2D();
	E_Texture = nullptr;
	E_Radius = float();
}

/*	Variable Constructors */

//SET Position Only
Entity::Entity(Driscoll::Vector2D _position)
{
	E_Position = _position;
	E_Texture = nullptr;
	E_Radius = float();
}

//SET Texture BY IMAGE Only
Entity::Entity(raylib::Image _texture)
{
	E_Position = Driscoll::Vector2D();
	E_Texture = new raylib::TextureUnmanaged(_texture);
	E_Radius = float();
}

//SET Radius Only
Entity::Entity(float _radius)
{
	E_Position = Driscoll::Vector2D();
	E_Texture = nullptr;
	E_Radius = _radius;
}

//Set Position & Texture by IMAGE Only
Entity::Entity(Driscoll::Vector2D _position, raylib::Image _texture)
{
	E_Position = _position;
	E_Texture = new raylib::TextureUnmanaged(_texture);
	E_Radius = float();
}

//Set Position & Radius
Entity::Entity(Driscoll::Vector2D _position, float _radius)
{
	E_Position = _position;
	E_Texture = nullptr;
	E_Radius = _radius;
}

//Set Texture BY IMAGE Only & Radius
Entity::Entity(raylib::Image _texture, float _radius)
{
	E_Position = Driscoll::Vector2D();
	E_Texture = new raylib::TextureUnmanaged(_texture);
	E_Radius = _radius;
}

//Set Postion, Texture BY IMAGE Only, & Radius
Entity::Entity(Driscoll::Vector2D _position, raylib::Image _texture, float _radius)
{
	E_Position = _position;
	E_Texture = new raylib::TextureUnmanaged(_texture);
	E_Radius = _radius;
}

//Copy Constructor
Entity::Entity(const Entity& _other)
{
	E_Position = _other.E_Position;
	E_Texture = new raylib::TextureUnmanaged(_other.E_Texture->GetData());
	E_Radius = _other.E_Radius;
}

//Copy Assignment
Entity Entity::operator=(const Entity& _other)
{
	E_Position = _other.E_Position;
	E_Texture = new raylib::TextureUnmanaged(_other.E_Texture->GetData());
	E_Radius = _other.E_Radius;
	return *this;
}

//Destructor
Entity::~Entity()
{
	delete E_Texture;
}


/* FUNCTIONS */

/* OBJECT VIRTUAL FUNCTION OVERRIDES */
//Begin Play: Called Before Start of Main Game Loop && MUST BE USER CALLED
void Entity::BeginPlay()
{
}

//Update: Called Every Tick in the Update Section && MUST BE USER CALLED
void Entity::Update()
{
}

//Draw: Called Every Tick in the Draw Section && MUST BE USER CALLED
void Entity::Draw()
{
	if (E_Texture != nullptr)
	{
		E_Texture->Draw(E_Position);
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
