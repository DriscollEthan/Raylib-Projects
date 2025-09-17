#include "Gunner.h"

/* CONSTRUCTORS & DESTRUCTORS */

//DEFAULT CONSTRUCTOR
Gunner::Gunner(Driscoll::Vector2D _position, raylib::Image _texture, Driscoll::Vector2D _origin, Driscoll::Vector2D _scale, float _radius, float _rotation, float _speed) : Player(_position, _texture, _origin, _scale, _radius, _rotation, _speed)
{
	WhichBulletToUse = 0;
	ScaleMult = _scale;
	BulletsInPool = nullptr;
}

//Copy Constructor
Gunner::Gunner(const Gunner& _other)
{
	E_Position = _other.E_Position;
	E_Texture = new raylib::TextureUnmanaged(_other.E_Texture->GetData());
	E_Origin = _other.E_Origin;
	E_Scale = _other.E_Scale;
	E_Radius = _other.E_Radius;
	E_MovementVector = _other.E_MovementVector;
	E_Speed = _other.E_Speed;
	E_Rotation = _other.E_Rotation;
	WhichBulletToUse = _other.WhichBulletToUse;
	ScaleMult = _other.E_Scale;
}

//Copy Assignment
Gunner Gunner::operator=(const Gunner& _other)
{
	E_Position = _other.E_Position;
	E_Texture = new raylib::TextureUnmanaged(_other.E_Texture->GetData());
	E_Origin = _other.E_Origin;
	E_Scale = _other.E_Scale;
	E_Radius = _other.E_Radius;
	E_MovementVector = _other.E_MovementVector;
	E_Speed = _other.E_Speed;
	E_Rotation = _other.E_Rotation;
	WhichBulletToUse = _other.WhichBulletToUse;
	ScaleMult = _other.E_Scale;
	return *this;
}

//Destructor
Gunner::~Gunner()
{
	if (BulletsInPool != nullptr)
	{
		delete[] BulletsInPool;
	}
}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* FUNCTIONS */

/* OBJECT VIRTUAL FUNCTION OVERRIDES */
//Begin Play: Called Before Start of Main Game Loop && MUST BE USER CALLED
void Gunner::BeginPlay()
{
	Player::BeginPlay();

	//Init Vars
	BulletsInPool = new Bullet[MAX_BULLETS_IN_POOL]();

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
			++WhichBulletToUse;
			if (WhichBulletToUse >= MAX_BULLETS_IN_POOL)
			{
				WhichBulletToUse = 0;
			}
			break;
		}
	}
	//Look Functionality
	Driscoll::Vector2D mousePosition = GetMousePosition();
	Rotate((atan2f((mousePosition.y - E_Position.y), (mousePosition.x - E_Position.x)) * Driscoll::Rad2Deg) + 90.0f);
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

void Gunner::SetScale(Driscoll::Vector2D _newScale)
{
	E_Scale = ScaleMult * _newScale;
}