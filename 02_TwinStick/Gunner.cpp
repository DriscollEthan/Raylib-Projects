#include "Gunner.h"

/* CONSTRUCTORS & DESTRUCTORS */

//DEFAULT CONSTRUCTOR
Gunner::Gunner() : Player()
{
	MovementVector = Driscoll::Vector2D();
	Speed = 1.0f;
}

/*	Variable Constructors */

//SET Position Only
Gunner::Gunner(Driscoll::Vector2D _position) : Player(_position)
{
	MovementVector = Driscoll::Vector2D();
	Speed = 1.0f;
}

//SET Texture BY IMAGE Only
Gunner::Gunner(raylib::Image _texture) : Player(_texture)
{
	MovementVector = Driscoll::Vector2D();
	Speed = 1.0f;
}

//SET Radius Only
Gunner::Gunner(float _radius) : Player(_radius)
{
	MovementVector = Driscoll::Vector2D();
	Speed = 1.0f;
}

//Set Position & Texture by IMAGE Only
Gunner::Gunner(Driscoll::Vector2D _position, raylib::Image _texture) : Player(_position, _texture)
{
	MovementVector = Driscoll::Vector2D();
	Speed = 1.0f;
}

//Set Position & Radius
Gunner::Gunner(Driscoll::Vector2D _position, float _radius) : Player(_position, _radius)
{
	MovementVector = Driscoll::Vector2D();
	Speed = 1.0f;
}

//Set Texture BY IMAGE Only & Radius
Gunner::Gunner(raylib::Image _texture, float _radius) : Player(_texture, _radius)
{
	MovementVector = Driscoll::Vector2D();
	Speed = 1.0f;
}

//Set Postion, Texture BY IMAGE Only, & Radius
Gunner::Gunner(Driscoll::Vector2D _position, raylib::Image _texture, float _radius) : Player(_position, _texture, _radius)
{
	MovementVector = Driscoll::Vector2D();
	Speed = 1.0f;
}

//Copy Constructor
Gunner::Gunner(const Gunner& _other)
{
	E_Position = _other.E_Position;
	E_Texture = new raylib::TextureUnmanaged(_other.E_Texture->GetData());
	E_Radius = _other.E_Radius;
	MovementVector = _other.MovementVector;
	Speed = _other.Speed;
}

//Copy Assignment
Gunner Gunner::operator=(const Gunner& _other)
{
	E_Position = _other.E_Position;
	E_Texture = new raylib::TextureUnmanaged(_other.E_Texture->GetData());
	E_Radius = _other.E_Radius;
	MovementVector = _other.MovementVector;
	Speed = _other.Speed;
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
	Speed = 2.5f;
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