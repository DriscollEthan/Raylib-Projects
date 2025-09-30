#include "Character.h"
#include <iostream> //std::cout DEBUG

/* CONSTRUCTORS & DESTRUCTORS */

//DEFAULT CONSTRUCTOR
Character::Character(Driscoll::Vector2D _position, size_t _texturePosition, Driscoll::Vector2D _origin, Driscoll::Vector2D _scale, float _radius, float _rotation, float _speed) : Player(_position, _texturePosition, _origin, _scale, _radius, _rotation, _speed)
{
	Turret = nullptr;
	EnemyRefs = nullptr;
	EnemyCount = 0;
}

//Copy Constructor
Character::Character(const Character& _other)
{
	Turret = nullptr;
	E_Position = _other.E_Position;
	TextureIndex = _other.TextureIndex;
	Origin = _other.Origin;
	E_Scale = _other.E_Scale;
	E_Radius = _other.E_Radius;
	MovementVector = _other.MovementVector;
	Speed = _other.Speed;
	E_Rotation = _other.E_Rotation;
	TextureManagerRef = _other.TextureManagerRef;
	EnemyRefs = _other.EnemyRefs;
	EnemyCount = _other.EnemyCount;
}

//Copy Assignment
Character Character::operator=(const Character& _other)
{
	Turret = nullptr;
	E_Position = _other.E_Position;
	TextureIndex = _other.TextureIndex;
	Origin = _other.Origin;
	E_Scale = _other.E_Scale;
	E_Radius = _other.E_Radius;
	MovementVector = _other.MovementVector;
	Speed = _other.Speed;
	E_Rotation = _other.E_Rotation;
	TextureManagerRef = _other.TextureManagerRef;
	EnemyCount = _other.EnemyCount;
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
	Turret = new Gunner(E_Position, 1, { 0.5f, 1 }, { (E_Scale.x / 2.0f), E_Scale.y }, 0, E_Rotation, 0, 60, 2);
	Turret->SetTextureManagerRef(GetTextureManagerRef());

	//Setup Input Keybinds
	{
		//Setup Movement Variables
		MovementInput[0] = FInput(E_IsKeyDown, KEY_W, 0);
		MovementInput[1] = FInput(E_IsKeyDown, KEY_S, 1);
		MovementInput[2] = FInput(E_IsKeyDown, KEY_A, 2);
		MovementInput[3] = FInput(E_IsKeyDown, KEY_D, 3);
		MovementInput[4] = FInput(E_IsKeyDown, KEY_UP, 0);
		MovementInput[5] = FInput(E_IsKeyDown, KEY_DOWN, 1);
		MovementInput[6] = FInput(E_IsKeyDown, KEY_LEFT, 2);
		MovementInput[7] = FInput(E_IsKeyDown, KEY_RIGHT, 3);

		//Setup Shoot Variables
		ShootInput[0] = FInput(E_IsMouseButtonPressed, MOUSE_BUTTON_LEFT, 0);
		ShootInput[1] = FInput(E_IsKeyPressed, KEY_SPACE, 0);
	}

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

	//Get Shoot Input
	for (int i = 0; i < 2; ++i)
	{
		FInputReturnStruct inputReturn = Input(ShootInput[i]);
		if (inputReturn.bIsInput)
		{
			Turret->Shoot(BulletSpeed, BulletLifetime);
			break;
		}
	}

	//Using the newly Updated Movement Vector, call movement.
	Move();

	//Update Turret Vars
	//Look
	Driscoll::Vector2D mousePosition = GetMousePosition();
	Turret->SetLocalRotation((atan2f((mousePosition.y - E_Position.y), (mousePosition.x - E_Position.x)) * Driscoll::Deg2Rad) + 90.0f);

	//Turret Position and Scale
	Turret->SetLocalPosition(E_Position);
	Turret->SetScale(E_Scale);

	Turret->Update();
}

//Draw: Called Every Tick in the Draw Section && MUST BE USER CALLED
void Character::Draw()
{
	Player::Draw();
	Turret->Draw();
}

void Character::GotHit()
{
	std::cout << "PlayerHit \n";
	SetIsAlive(false);
}

bool Character::BulletHitEnemy(Entity* _enemy)
{
	return Turret->CollisionCheck(_enemy);
}

Gunner* Character::GetTurretRef()
{
	return Turret;
}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* Character SPECIFIC GET FUNCTIONS */

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* Character SPECIFIC SET FUNCTIONS */

void Character::SetEnemyRefs(Entity* _enemyRefs, size_t _count)
{
	EnemyRefs = _enemyRefs;
	EnemyCount = _count;
}