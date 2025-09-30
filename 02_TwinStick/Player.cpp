#include "Player.h"

/* CONSTRUCTORS & DESTRUCTORS */

//DEFAULT CONSTRUCTOR
Player::Player(LocalData2D _localData, size_t _textureLocation, Driscoll::Vector2D _origin, HitboxData _hitbox, float _speed) : Entity(_localData, _textureLocation, _origin, _hitbox, _speed)
{

}

//Copy Constructor
Player::Player(const Player& _other) 
{
	LocalData = _other.LocalData;
	Origin = _other.Origin;
	Hitbox = _other.Hitbox;
	MovementVector = _other.MovementVector;
	Speed = _other.Speed;
}

//Copy Assignment
Player Player::operator=(const Player& _other)
{
	LocalData = _other.LocalData;
	Origin = _other.Origin;
	Hitbox = _other.Hitbox;
	MovementVector = _other.MovementVector;
	Speed = _other.Speed;
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
	MovementVector.Zero();

	//Get Movement Input

	//Using the newly Updated Movement Vector, call movement.

}

//Draw: Called Every Tick in the Draw Section && MUST BE USER CALLED
void Player::Draw()
{
	Entity::Draw();
}

void Player::GotHit()
{
	Entity::GotHit();
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