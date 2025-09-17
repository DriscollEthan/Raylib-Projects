#include "Player.h"

/* CONSTRUCTORS & DESTRUCTORS */

//DEFAULT CONSTRUCTOR
Player::Player(Driscoll::Vector2D _position, raylib::Image _texture, float _radius, float _rotation, float _speed) : Entity(_position, _texture, _radius, _rotation, _speed)
{

}

//Copy Constructor
Player::Player(const Player& _other) 
{
	E_Position = _other.E_Position;
	E_Texture = new raylib::TextureUnmanaged(_other.E_Texture->GetData());
	E_Radius = _other.E_Radius;
	E_MovementVector = _other.E_MovementVector;
	E_Speed = _other.E_Speed;
	E_Rotation = _other.E_Rotation;
}

//Copy Assignment
Player Player::operator=(const Player& _other)
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
	E_Speed = 2.5f;

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
	}

	return returnValue;
}


/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* PLAYER SPECIFIC GET FUNCTIONS */

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* PLAYER SPECIFIC SET FUNCTIONS */

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* PLAYER ONLY FUNCTIONS */
void Player::Move()
{
	E_Position += E_MovementVector.SafeNormalised() * (E_Speed * GetFrameTime() * 100.0f);
	E_Position = Wrap(E_Position, Driscoll::Vector2D(0, 0), GVO.GetScreenSize());
}

void Player::Rotate(float _newRotation)
{
	E_Rotation = _newRotation;
}

Driscoll::Vector2D Player::Wrap(Driscoll::Vector2D _currentVector, Driscoll::Vector2D _min, Driscoll::Vector2D _max)
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