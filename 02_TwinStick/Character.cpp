#include "Character.h"
#include <iostream> //std::cout DEBUG

/* CONSTRUCTORS & DESTRUCTORS */

//DEFAULT CONSTRUCTOR
Character::Character(Driscoll::Vector2D _position, raylib::Image _texture, Driscoll::Vector2D _origin, Driscoll::Vector2D _scale, float _radius, float _rotation, float _speed) : Player(_position, _texture, _origin, _scale, _radius, _rotation, _speed)
{
	Turret = nullptr;
}

//Copy Constructor
Character::Character(const Character& _other)
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
Character Character::operator=(const Character& _other)
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
Character::~Character()
{
	delete Turret;
}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* FUNCTIONS */

/* OBJECT VIRTUAL FUNCTION OVERRIDES */
//Begin Play: Called Before Start of Main Game Loop && MUST BE USER CALLED
void Character::BeginPlay()
{
	Player::BeginPlay();

	//Init Vars
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

	raylib::Image turretImage;
	turretImage.Load("Resources/Turret.png");

	Turret = new Gunner(E_Position, turretImage, { 0.5, 1 }, { (E_Scale.x / 2.0f), E_Scale.y}, 0, E_Rotation, 0);

	Turret->BeginPlay();
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
				E_MovementVector.y -= 1;
				break;
			case 1:
				E_MovementVector.y += 1;
				break;
			case 2:
				E_MovementVector.x -= 1;
				break;
			case 3:
				E_MovementVector.x += 1;
				break;
			}
		}
	}
	//Using the newly Updated Movement Vector, call movement.
	Move();
	Turret->SetPosition(E_Position);
	Turret->SetScale(E_Scale);

	Turret->Update();

	E_Scale += {0.0001f, 0.0001f};
}

//Draw: Called Every Tick in the Draw Section && MUST BE USER CALLED
void Character::Draw()
{
	Player::Draw();
	Turret->Draw();
}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* Character SPECIFIC GET FUNCTIONS */

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* Character SPECIFIC SET FUNCTIONS */