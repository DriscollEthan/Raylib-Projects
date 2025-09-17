#include "Character.h"

/* CONSTRUCTORS & DESTRUCTORS */

//DEFAULT CONSTRUCTOR
Character::Character() : Player()
{
	MovementVector = Driscoll::Vector2D();
	Speed = 1.0f;
}

/*	Variable Constructors */

//SET Position Only
Character::Character(Driscoll::Vector2D _position) : Player(_position)
{
	MovementVector = Driscoll::Vector2D();
	Speed = 1.0f;
}

//SET Texture BY IMAGE Only
Character::Character(raylib::Image _texture) : Player(_texture)
{
	MovementVector = Driscoll::Vector2D();
	Speed = 1.0f;
}

//SET Radius Only
Character::Character(float _radius) : Player(_radius)
{
	MovementVector = Driscoll::Vector2D();
	Speed = 1.0f;
}

//Set Position & Texture by IMAGE Only
Character::Character(Driscoll::Vector2D _position, raylib::Image _texture) : Player(_position, _texture)
{
	MovementVector = Driscoll::Vector2D();
	Speed = 1.0f;
}

//Set Position & Radius
Character::Character(Driscoll::Vector2D _position, float _radius) : Player(_position, _radius)
{
	MovementVector = Driscoll::Vector2D();
	Speed = 1.0f;
}

//Set Texture BY IMAGE Only & Radius
Character::Character(raylib::Image _texture, float _radius) : Player(_texture, _radius)
{
	MovementVector = Driscoll::Vector2D();
	Speed = 1.0f;
}

//Set Postion, Texture BY IMAGE Only, & Radius
Character::Character(Driscoll::Vector2D _position, raylib::Image _texture, float _radius) : Player(_position, _texture, _radius)
{
	MovementVector = Driscoll::Vector2D();
	Speed = 1.0f;
}

//Copy Constructor
Character::Character(const Character& _other)
{
	E_Position = _other.E_Position;
	E_Texture = new raylib::TextureUnmanaged(_other.E_Texture->GetData());
	E_Radius = _other.E_Radius;
	MovementVector = _other.MovementVector;
	Speed = _other.Speed;
}

//Copy Assignment
Character Character::operator=(const Character& _other)
{
	E_Position = _other.E_Position;
	E_Texture = new raylib::TextureUnmanaged(_other.E_Texture->GetData());
	E_Radius = _other.E_Radius;
	MovementVector = _other.MovementVector;
	Speed = _other.Speed;
	return *this;
}

//Destructor
Character::~Character()
{

}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* FUNCTIONS */

/* OBJECT VIRTUAL FUNCTION OVERRIDES */
//Begin Play: Called Before Start of Main Game Loop && MUST BE USER CALLED
void Character::BeginPlay()
{
	Player::BeginPlay();

	//Init Vars
	Speed = 2.5f;
	GVO = GlobalVariableObject();

	//Setup Input Keybinds
	{
		MovementInput[0] = FInput(E_IsKeyDown, KEY_W, 0);
		MovementInput[1] = FInput(E_IsKeyDown, KEY_S, 1);
		MovementInput[2] = FInput(E_IsKeyDown, KEY_A, 2);
		MovementInput[3] = FInput(E_IsKeyDown, KEY_D, 3);
		MovementInput[4] = FInput(E_IsKeyDown, KEY_UP, 0);
		MovementInput[5] = FInput(E_IsKeyDown, KEY_DOWN, 1);
		MovementInput[6] = FInput(E_IsKeyDown, KEY_LEFT, 2);
		MovementInput[7] = FInput(E_IsKeyDown, KEY_RIGHT, 3);
	}

}

//Update: Called Every Tick in the Update Section && MUST BE USER CALLED
void Character::Update()
{
	//Call Parent Update
	Player::Update();

	//Get Movement Input
	for (int i = 0; i < 8; ++i)
	{
		FInputReturnStruct inputReturn = Input(MovementInput[i]);
		if (inputReturn.bIsInput)
		{
			switch (inputReturn.Index)
			{
			case 0:
				MovementVector.y -= 1;
				break;
			case 1:
				MovementVector.y += 1;
				break;
			case 2:
				MovementVector.x -= 1;
				break;
			case 3:
				MovementVector.x += 1;
				break;
			}
		}
	}
	//Using the newly Updated Movement Vector, call movement.
	Move();
}

//Draw: Called Every Tick in the Draw Section && MUST BE USER CALLED
void Character::Draw()
{
	Player::Draw();
}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* Character SPECIFIC GET FUNCTIONS */

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* Character SPECIFIC SET FUNCTIONS */