#include "Bullet.h"

/* CONSTRUCTORS & DESTRUCTORS */

//DEFAULT CONSTRUCTOR
Bullet::Bullet(Driscoll::Vector2D _position, size_t _texturePosition, Driscoll::Vector2D _origin, Driscoll::Vector2D _scale, float _radius, float _rotation, float _speed) : Entity(_position, _texturePosition, _origin, _scale, _radius, _rotation, _speed)
{
	CurrentState = None;
	TimeAlive = 0.0f;
	TimeToLive = 0.0f;
}

//Copy Constructor
Bullet::Bullet(const Bullet& _other)
{
	E_Position = _other.E_Position;
	TextureIndex = _other.TextureIndex;
	E_Origin = _other.E_Origin;
	E_Scale = _other.E_Scale;
	E_Radius = _other.E_Radius;
	E_MovementVector = _other.E_MovementVector;
	E_Speed = _other.E_Speed;
	E_Rotation = _other.E_Rotation;
	CurrentState = _other.CurrentState;
	TimeAlive = _other.TimeAlive;
	TimeToLive = _other.TimeToLive;
	TextureManagerRef = _other.TextureManagerRef;
}

//Copy Assignment
Bullet Bullet::operator=(const Bullet& _other)
{
	E_Position = _other.E_Position;
	TextureIndex = _other.TextureIndex;
	E_Origin = _other.E_Origin;
	E_Scale = _other.E_Scale;
	E_Radius = _other.E_Radius;
	E_MovementVector = _other.E_MovementVector;
	E_Speed = _other.E_Speed;
	E_Rotation = _other.E_Rotation;
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
	E_Origin = { 0.5f, 0.5f };
	E_Radius = GetTextureManagerRef()->GetTexture(TextureIndex).GetWidth();
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

bool Bullet::CollisionCheck(Entity* _otherObject)
{
	switch (CurrentState)
	{
	case None:
		return false;
		break;
	case Active:
		if (_otherObject == nullptr)
		{
			std::cout << "NULLPTR DETECTED \n";
		}
		return CheckCollisionCircles(E_Position, E_Radius, _otherObject->GetPosition(), _otherObject->GetRadius());
		break;
	case Inactive:
		return false;
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
	E_Position = _spawnPosition;
	E_MovementVector = _movementVector;
	E_Speed = _speed;
	SetTimeToLive(_timeToLive);
	SetCurrentState(Active);
	TimeAlive = 0.0f;
}