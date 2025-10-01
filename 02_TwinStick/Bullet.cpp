#include "Bullet.h"

/* CONSTRUCTORS & DESTRUCTORS */

//DEFAULT CONSTRUCTOR
Bullet::Bullet(LocalData2D _localData, size_t _textureLocation, Driscoll::Vector2D _origin, HitboxData _hitbox, float _speed) : Entity(_localData, _textureLocation, _origin, _hitbox, _speed)
{
	CurrentState = None;
	TimeAlive = 0.0f;
	TimeToLive = 0.0f;
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
	TimeAlive = _other.TimeAlive;
	TimeToLive = _other.TimeToLive;
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
	TimeAlive = _other.TimeAlive;
	TimeToLive = _other.TimeToLive;
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
	Hitbox.SetHitbox(GetWorldPosition(), GetTextureManagerRef()->GetTexture(TextureIndex).GetWidth());
}

//Update: Called Every Tick in the Update Section && MUST BE USER CALLED
void Bullet::Update()
{
	//Reset Vars

	//Check if still Alive
	if (TimeAlive >= TimeToLive)
	{
		CurrentState = Inactive;
	}

	//Call Parent Update
	switch (CurrentState)
	{
	case None:
		break;
	case Active:
		Entity::Update();
		Move();
		TimeAlive += GetFrameTime();
		break;
	case Inactive:
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
	CurrentState = _newState;
}

//Set Time To Live
void Bullet::SetTimeToLive(float _newTimeToLive)
{
	TimeToLive = _newTimeToLive;
}

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* BULLET ONLY FUNCTIONS */
//Spawn Bullet
void Bullet::SpawnBullet(Driscoll::Vector2D _spawnPosition, Driscoll::Vector2D _movementVector, float _speed, float _timeToLive)
{
	LocalData.LocalPosition = _spawnPosition;
	MovementVector = _movementVector;
	Speed = _speed;
	SetTimeToLive(_timeToLive);
	SetCurrentState(Active);
	TimeAlive = 0.0f;
}