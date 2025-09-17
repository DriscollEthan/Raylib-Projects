#include "Gunner.h"

/* CONSTRUCTORS & DESTRUCTORS */

//DEFAULT CONSTRUCTOR
Gunner::Gunner(Driscoll::Vector2D _position, raylib::Image _texture, float _radius, float _rotation, float _speed) : Player(_position, _texture, _radius, _rotation, _speed)
{
	
}

//Copy Constructor
Gunner::Gunner(const Gunner& _other)
{
	E_Position = _other.E_Position;
	E_Texture = new raylib::TextureUnmanaged(_other.E_Texture->GetData());
	E_Radius = _other.E_Radius;
	E_MovementVector = _other.E_MovementVector;
	E_Speed = _other.E_Speed;
	E_Rotation = _other.E_Rotation;
}

//Copy Assignment
Gunner Gunner::operator=(const Gunner& _other)
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
Gunner::~Gunner()
{

}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* FUNCTIONS */

/* OBJECT VIRTUAL FUNCTION OVERRIDES */
//Begin Play: Called Before Start of Main Game Loop && MUST BE USER CALLED
void Gunner::BeginPlay()
{
	Player::BeginPlay();

	//Init Vars
	E_Speed = 2.5f;
	GVO = GlobalVariableObject();

	//Setup Input Keybinds
	{
		ShootInput[0] = FInput(E_IsKeyDown, MOUSE_BUTTON_LEFT, 0);
		ShootInput[1] = FInput(E_IsKeyDown, KEY_SPACE, 0);
	}

}

//Update: Called Every Tick in the Update Section && MUST BE USER CALLED
void Gunner::Update()
{
	//Call Parent Update
	Player::Update();

	//Get Movement Input
	for (int i = 0; i < 2; ++i)
	{
		FInputReturnStruct inputReturn = Input(ShootInput[i]);
		if (inputReturn.bIsInput)
		{
			//Shoot Function
			break;
		}
	}
	//Look Functionality

}

//Draw: Called Every Tick in the Draw Section && MUST BE USER CALLED
void Gunner::Draw()
{
	Player::Draw();
}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* Gunner SPECIFIC GET FUNCTIONS */

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* Gunner SPECIFIC SET FUNCTIONS */