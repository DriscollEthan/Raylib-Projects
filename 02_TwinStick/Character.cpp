#include "Character.h"
#include <iostream> //std::cout DEBUG

/* CONSTRUCTORS & DESTRUCTORS */

//DEFAULT CONSTRUCTOR
Character::Character(LocalData2D _localData, size_t _textureLocation, Driscoll::Vector2D _origin, HitboxData _hitbox, float _speed, float _bulletLifetime, float _bulletSpeed) : Player(_localData, _textureLocation, _origin, _hitbox, _speed)
{
	Turret = nullptr;
	BulletSpeed = _bulletSpeed;
	BulletLifetime = _bulletLifetime;
	bLastHit = false;
	bFlipFlop = true;
	SwitchingColorTime = 0.f;
}

//Copy Constructor
Character::Character(const Character& _other)
{
	Turret = nullptr;
	LocalData = _other.LocalData;
	TextureIndex = _other.TextureIndex;
	Origin = _other.Origin;
	Hitbox = _other.Hitbox;
	MovementVector = _other.MovementVector;
	Speed = _other.Speed;
	BulletSpeed = _other.BulletSpeed;
	BulletLifetime = _other.BulletLifetime;
	bLastHit = _other.bLastHit;
	bFlipFlop = _other.bFlipFlop;
	SwitchingColorTime = _other.SwitchingColorTime;
}

//Copy Assignment
Character Character::operator=(const Character& _other)
{
	Turret = nullptr;
	LocalData = _other.LocalData;
	TextureIndex = _other.TextureIndex;
	Origin = _other.Origin;
	Hitbox = _other.Hitbox;
	MovementVector = _other.MovementVector;
	Speed = _other.Speed;
	BulletSpeed = _other.BulletSpeed;
	BulletLifetime = _other.BulletLifetime;
	bLastHit = _other.bLastHit;
	bFlipFlop = _other.bFlipFlop;
	SwitchingColorTime = _other.SwitchingColorTime;
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
	Turret = new Gunner(LocalData2D({0, 0}, 0, {1.0f, 1.0f}), 8, {0.5f, 1.f}, HitboxData(), 60, 3);
	Turret->SetTextureManagerRef(GetTextureManagerRef());
	Turret->SetParent(this);
	SetLocalRotation(0);
	SetHealth(5);

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
	if (bIsAlive)
	{
		if (bLastHit)
		{
			SwitchingColorTime += GetFrameTime();
			if (SwitchingColorTime > 0.25f)
			{
				SwitchingColorTime = 0;
				bFlipFlop = !bFlipFlop;

				if (bFlipFlop)
				{
					DrawColor = Driscoll::RED;
					Turret->SetDrawColor(DrawColor);
				}
				else
				{
					DrawColor = Driscoll::WHITE;
					Turret->SetDrawColor(DrawColor);
				}
			}
		}

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

		if (MovementVector != 0)
		{
			SetLocalRotation(Driscoll::AngleFrom2D(MovementVector.x, MovementVector.y));
		}

		//Update Turret Vars
		//Turret Look in RADIANS
		Driscoll::Vector2D mousePosition = GetMousePosition();
		mousePosition -= GetWorldPosition();
		Turret->SetLocalRotation(Driscoll::AngleFrom2D(mousePosition.x, mousePosition.y) + -GetWorldRotation());


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

		//Call Parent Update to Update Matricies and Hitbox Position.
		Player::Update();

		Turret->Update();
	}
}

//Draw: Called Every Tick in the Draw Section && MUST BE USER CALLED
void Character::Draw()
{
	if (bIsAlive)
	{
		Player::Draw();
		Turret->Draw();
	}
}

void Character::GotHit()
{
	SetHealth(GetHealth() - 1);

	switch ((int)GetHealth())
	{
	case 0:
		//bool for last hit to flash colors
		bLastHit = true;
		DrawColor = Driscoll::RED;
		Turret->SetDrawColor(DrawColor);
		break;
	case 1:
		//Full Turret
		Turret->SetTextureIndex(12);
		break;
	case 2:
		//1/4 Turret Left
		Turret->SetTextureIndex(11);
		break;
	case 3:
		//1/2 Turret Left
		Turret->SetTextureIndex(10);
		break;
	case 4:
		//3/4 Turret Left
		Turret->SetTextureIndex(9);
		break;
	}

	if (GetHealth() < 0)
	{
		SetIsAlive(false);
	}
}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* Character SPECIFIC GET FUNCTIONS */

Gunner* Character::GetTurretRef()
{
	return Turret;
}

float Character::GetHealth()
{
	return Health;
}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* Character SPECIFIC SET FUNCTIONS */
void Character::SetHealth(float _maxHealth)
{
	Health = _maxHealth;
}