#include "Bullet.h"

/* CONSTRUCTORS & DESTRUCTORS */

//DEFAULT CONSTRUCTOR
Bullet::Bullet(LocalData2D _localData, size_t _textureLocation, Driscoll::Vector2D _origin, HitboxData _hitbox, float _speed) : Entity(_localData, _textureLocation, _origin, _hitbox, _speed)
{
	CurrentState = None;
}

//Copy Constructor
Bullet::Bullet(const Bullet& _other)
{
	LocalData = _other.LocalData;
	Origin = _other.Origin;
	Hitbox = _other.Hitbox;
	MovementVector = _other.MovementVector;
	Speed = _other.Speed;
	CurrentState = _other.CurrentState;
	TextureManagerRef = _other.TextureManagerRef;
}

//Copy Assignment
Bullet Bullet::operator=(const Bullet& _other)
{
	LocalData = _other.LocalData;
	Origin = _other.Origin;
	Hitbox = _other.Hitbox;
	MovementVector = _other.MovementVector;
	Speed = _other.Speed;
	CurrentState = _other.CurrentState;
	TextureManagerRef = _other.TextureManagerRef;
	return *this;
}

//Destructor
Bullet::~Bullet()
{

}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* FUNCTIONS */

/* OBJECT VIRTUAL FUNCTION OVERRIDES */
//Begin Play: Called Before Start of Main Game Loop && MUST BE USER CALLED
void Bullet::BeginPlay()
{
	Entity::BeginPlay();

	//Init Vars
	SetCurrentState(None);
	Origin = { 0.5f, 0.5f };
	Hitbox.SetHitbox(GetWorldPosition(), (GetTextureManagerRef()->GetTexture(TextureIndex).GetWidth() * LocalData.LocalScale.x) - 2.5f);
	LivingTimer.SetTimerInSeconds(0.0f, 0.0f);
	ExplosionTimer.SetTimerInSeconds(0.0f, 0.1);
	ExplosionIterations = 0;
}

//Update: Called Every Tick in the Update Section && MUST BE USER CALLED
void Bullet::Update()
{
	//Reset Vars

	//Call Parent Update
	switch (CurrentState)
	{
	case None:
		break;
	case Active:
		Entity::Update();
		Move();
		SetLocalRotation(Driscoll::AngleFrom2D(MovementVector.x, MovementVector.y));
		//Check if still Alive
		if (LivingTimer.RunTimer(GetFrameTime()))
		{
			CurrentState = Explosion;
			ExplosionIterations = 0;
			TextureIndex = 14;
			SetHitboxRadius((TextureManagerRef->GetTexture(TextureIndex).GetWidth() * GetWorldScale().x) - 20.0f);
		}

		break;
	case Inactive:
		break;
	case Explosion:
	{
		Entity::Update();
		if (ExplosionTimer.RunTimer(GetFrameTime()) && TextureIndex != 0)
		{
			DrawColor = Driscoll::Color(255, 63, 63, 255);
			switch (ExplosionIterations++)
			{
			case 0:
				TextureIndex = 14;
				break;
			case 1:
				TextureIndex = 15;
				break;
			case 2:
				TextureIndex = 16;
				break;
			case 3:
				TextureIndex = 17;
				break;
			case 4:
				TextureIndex = 18;
				break;
			case 5:
				TextureIndex = 19;
				break;
			case 6:
				TextureIndex = 0;
				CurrentState = Inactive;
				break;
			}
			ExplosionTimer.ResetTimer();
		}
	}
		break;
	case NonDeadlyExplosion:
	{
		Entity::Update();
		if (ExplosionTimer.RunTimer(GetFrameTime()) && TextureIndex != 0)
		{
			DrawColor = Driscoll::PINK;
			switch (ExplosionIterations++)
			{
			case 0:
				TextureIndex = 14;
				break;
			case 1:
				TextureIndex = 15;
				break;
			case 2:
				TextureIndex = 16;
				break;
			case 3:
				TextureIndex = 17;
				break;
			case 4:
				TextureIndex = 18;
				break;
			case 5:
				TextureIndex = 19;
				break;
			case 6:
				TextureIndex = 0;
				CurrentState = Inactive;
				break;
			}
			ExplosionTimer.ResetTimer();
		}
	}
	break;
	}
}

//Draw: Called Every Tick in the Draw Section && MUST BE USER CALLED
void Bullet::Draw()
{
	switch (CurrentState)
	{
	case None:
		break;
	case Active:
		Entity::Draw();
		break;
	case Inactive:
		break;
	case Explosion:
		if (ExplosionIterations < 6)
		{
			Entity::Draw();
		}
		else
		{
			CurrentState == Inactive;
		}
		break;
	case NonDeadlyExplosion:
		if (ExplosionIterations < 6)
		{
			Entity::Draw();
		}
		else
		{
			CurrentState == Inactive;
		}
		break;
	}
}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* Bullet SPECIFIC GET FUNCTIONS */
//Get Current State
EState Bullet::GetCurrentState()
{
	return CurrentState;
}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* Bullet SPECIFIC SET FUNCTIONS */
//Set Current State
void Bullet::SetCurrentState(EState _newState)
{
	if (_newState == Explosion || _newState == NonDeadlyExplosion)
	{
		ExplosionIterations = 0;
	}
	CurrentState = _newState;
}

//Set Time To Live
void Bullet::SetTimeToLive(float _newTimeToLive)
{
	LivingTimer.SetTimerInSeconds(0.0f, _newTimeToLive);
}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* BULLET ONLY FUNCTIONS */
//Spawn Bullet
void Bullet::SpawnBullet(Driscoll::Vector2D _spawnPosition, Driscoll::Vector2D _movementVector, float _speed, float _timeToLive)
{
	LocalData.LocalPosition = _spawnPosition;
	MovementVector = _movementVector;
	Speed = _speed;
	SetCurrentState(Active);
	LivingTimer.SetTimerInSeconds(0.0f, _timeToLive);
	DrawColor = Driscoll::WHITE;
}

void Bullet::IncreaseDifficulty(int _round)
{
}