#include "Player.h"

/* CONSTRUCTORS & DESTRUCTORS */

//DEFAULT CONSTRUCTOR
Player::Player() : Entity()
{
	MovementVector = Driscoll::Vector2D();
}

/*	Variable Constructors */

//SET Position Only
Player::Player(Driscoll::Vector2D _position) : Entity(_position)
{

}

//SET Texture BY IMAGE Only
Player::Player(raylib::Image _texture) : Entity(_texture)
{

}

//SET Radius Only
Player::Player(float _radius)
{

}

//Set Position & Texture by IMAGE Only
Player::Player(Driscoll::Vector2D _position, raylib::Image _texture) : Entity(_position, _texture)
{

}

//Set Position & Radius
Player::Player(Driscoll::Vector2D _position, float _radius) : Entity(_position, _radius)
{

}

//Set Texture BY IMAGE Only & Radius
Player::Player(raylib::Image _texture, float _radius) : Entity(_texture, _radius)
{

}

//Set Postion, Texture BY IMAGE Only, & Radius
Player::Player(Driscoll::Vector2D _position, raylib::Image _texture, float _radius) : Entity(_position, _texture, _radius)
{

}

//Copy Constructor
Player::Player(const Player& _other) 
{
	E_Position = _other.E_Position;
	E_Texture = new raylib::TextureUnmanaged(_other.E_Texture->GetData());
	E_Radius = _other.E_Radius;
}

//Copy Assignment
Player Player::operator=(const Player& _other)
{
	E_Position = _other.E_Position;
	E_Texture = new raylib::TextureUnmanaged(_other.E_Texture->GetData());
	E_Radius = _other.E_Radius;
	return *this;
}

//Destructor
Player::~Player()
{
	Entity::~Entity();
}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* FUNCTIONS */

/* OBJECT VIRTUAL FUNCTION OVERRIDES */
//Begin Play: Called Before Start of Main Game Loop && MUST BE USER CALLED
void Player::BeginPlay()
{

}

//Update: Called Every Tick in the Update Section && MUST BE USER CALLED
void Player::Update()
{
}

//Draw: Called Every Tick in the Draw Section && MUST BE USER CALLED
void Player::Draw()
{
	Entity::Draw();
}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* PLAYER SPECIFIC GET FUNCTIONS */
