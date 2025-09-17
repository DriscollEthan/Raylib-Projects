#include "Bullet.h"

/* CONSTRUCTORS & DESTRUCTORS */

//DEFAULT CONSTRUCTOR
Bullet::Bullet(Driscoll::Vector2D _position, raylib::Image _texture, Driscoll::Vector2D _origin, Driscoll::Vector2D _scale, float _radius, float _rotation, float _speed) : Entity(_position, _texture, _origin, _scale, _radius, _rotation, _speed)
{

}

//Copy Constructor
Bullet::Bullet(const Bullet& _other)
{
	E_Position = _other.E_Position;
	E_Texture = new raylib::TextureUnmanaged(_other.E_Texture->GetData());
	E_Origin = _other.E_Origin;
	E_Scale = _other.E_Scale;
	E_Radius = _other.E_Radius;
	E_MovementVector = _other.E_MovementVector;
	E_Speed = _other.E_Speed;
	E_Rotation = _other.E_Rotation;
}

//Copy Assignment
Bullet Bullet::operator=(const Bullet& _other)
{
	E_Position = _other.E_Position;
	E_Texture = new raylib::TextureUnmanaged(_other.E_Texture->GetData());
	E_Origin = _other.E_Origin;
	E_Scale = _other.E_Scale;
	E_Radius = _other.E_Radius;
	E_MovementVector = _other.E_MovementVector;
	E_Speed = _other.E_Speed;
	E_Rotation = _other.E_Rotation;
	return *this;
}

//Destructor
Bullet::~Bullet()
{

}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* FUNCTIONS */

/* OBJECT VIRTUAL FUNCTION OVERRIDES */
//Begin Play: Called Before Start of Main Game Loop && MUST BE USER CALLED
void Bullet::BeginPlay()
{
	Entity::BeginPlay();

	//Init Vars
	
}

//Update: Called Every Tick in the Update Section && MUST BE USER CALLED
void Bullet::Update()
{
	//Call Parent Update
	Entity::Update();

	//Rest Vars

}

//Draw: Called Every Tick in the Draw Section && MUST BE USER CALLED
void Bullet::Draw()
{
	Entity::Draw();
}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

	/* Bullet SPECIFIC GET FUNCTIONS */


/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

	/* Bullet SPECIFIC SET FUNCTIONS */


/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

	/* BULLET ONLY FUNCTIONS */
