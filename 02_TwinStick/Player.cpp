#include "Player.h"

/* CONSTRUCTORS & DESTRUCTORS */

//DEFAULT CONSTRUCTOR
Player::Player(Driscoll::Vector2D _position, raylib::Image _texture, Driscoll::Vector2D _origin, Driscoll::Vector2D _scale, float _radius, float _rotation, float _speed) : Entity(_position, _texture, _origin, _scale, _radius, _rotation, _speed)
{

}

//Copy Constructor
Player::Player(const Player& _other) 
{
	E_Position = _other.E_Position;
	E_Texture = _other.E_Texture.GetData();
	E_Origin = _other.E_Origin;
	E_Scale = _other.E_Scale;
	E_Radius = _other.E_Radius;
	E_MovementVector = _other.E_MovementVector;
	E_Speed = _other.E_Speed;
	E_Rotation = _other.E_Rotation;
}

//Copy Assignment
Player Player::operator=(const Player& _other)
{
	E_Position = _other.E_Position;
	E_Texture = _other.E_Texture.GetData();
	E_Origin = _other.E_Origin;
	E_Scale = _other.E_Scale;
	E_Radius = _other.E_Radius;
	E_MovementVector = _other.E_MovementVector;
	E_Speed = _other.E_Speed;
	E_Rotation = _other.E_Rotation;
	return *this;
}

//Destructor
Player::~Player()
{

}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* FUNCTIONS */

/* OBJECT VIRTUAL FUNCTION OVERRIDES */
//Begin Play: Called Before Start of Main Game Loop && MUST BE USER CALLED
void Player::BeginPlay()
{
	Entity::BeginPlay();

	//Init Vars


	//Setup Input Keybinds and Grab Mouse POS
	
}

//Update: Called Every Tick in the Update Section && MUST BE USER CALLED
void Player::Update()
{
	//Call Parent Update
	Entity::Update();

	//Rest Vars
	E_MovementVector.Zero();

	//Get Movement Input

	//Using the newly Updated Movement Vector, call movement.

}

//Draw: Called Every Tick in the Draw Section && MUST BE USER CALLED
void Player::Draw()
{
	Entity::Draw();
}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

	/* PLAYER INPUT FUNCTIONS */
FInputReturnStruct Player::Input(FInput _input)
{
	FInputReturnStruct returnValue = FInputReturnStruct();
	returnValue.Index = _input.InputIndex;
	switch (_input.InputType)
	{
	case E_IsKeyDown:
		returnValue.bIsInput = IsKeyDown(_input.Key);
		break;
	case E_IsKeyPressed:
		returnValue.bIsInput = IsKeyPressed(_input.Key);
		break;
	case E_IsKeyPressedRepeat:
		returnValue.bIsInput = IsKeyPressedRepeat(_input.Key);
		break;
	case E_IsKeyReleased:
		returnValue.bIsInput = IsKeyReleased(_input.Key);
		break;
	case E_IsKeyUp:
		returnValue.bIsInput = IsKeyUp(_input.Key);
		break;
	case E_IsMouseButtonPressed:
		returnValue.bIsInput = IsMouseButtonPressed(_input.Key);
		break;
	case E_IsMouseButtonDown:
		returnValue.bIsInput = IsMouseButtonDown(_input.Key);
		break;
	case E_IsMouseButtonReleased:
		returnValue.bIsInput = IsMouseButtonReleased(_input.Key);
		break;
	case E_IsMouseButtonUp:
		returnValue.bIsInput = IsMouseButtonUp(_input.Key);
		break;
	}

	return returnValue;
}


/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* PLAYER SPECIFIC GET FUNCTIONS */

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* PLAYER SPECIFIC SET FUNCTIONS */

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* PLAYER ONLY FUNCTIONS */