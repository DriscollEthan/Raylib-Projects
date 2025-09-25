#include "Gunner.h"
#include "Utils.h"

/* CONSTRUCTORS & DESTRUCTORS */

//DEFAULT CONSTRUCTOR
Gunner::Gunner(Driscoll::Vector2D _position, size_t _texturePosition, Driscoll::Vector2D _origin, Driscoll::Vector2D _scale, float _radius, float _rotation, float _speed, int _maxBulletsInPool, size_t _bulletTexturePosition) : Player(_position, _texturePosition, _origin, _scale, _radius, _rotation, _speed)
{
	WhichBulletToUse = 0;
	ScaleMult = _scale;
	BulletsInPool = nullptr;
	MAX_BULLETS_IN_POOL = _maxBulletsInPool;
	BulletTexturePosition = _bulletTexturePosition;
}

//Copy Constructor
Gunner::Gunner(const Gunner& _other)
{
	BulletsInPool = nullptr;
	E_Position = _other.E_Position;
	E_TextureLocation = _other.E_TextureLocation;
	E_Origin = _other.E_Origin;
	E_Scale = _other.E_Scale;
	E_Radius = _other.E_Radius;
	E_MovementVector = _other.E_MovementVector;
	E_Speed = _other.E_Speed;
	E_Rotation = _other.E_Rotation;
	WhichBulletToUse = _other.WhichBulletToUse;
	ScaleMult = _other.E_Scale;
	MAX_BULLETS_IN_POOL = _other.MAX_BULLETS_IN_POOL;
	E_TextureManagerRef = _other.E_TextureManagerRef;
	BulletTexturePosition = _other.BulletTexturePosition;
}

//Copy Assignment
Gunner Gunner::operator=(const Gunner& _other)
{
	BulletsInPool = nullptr;
	E_Position = _other.E_Position;
	E_TextureLocation = _other.E_TextureLocation;
	E_Origin = _other.E_Origin;
	E_Scale = _other.E_Scale;
	E_Radius = _other.E_Radius;
	E_MovementVector = _other.E_MovementVector;
	E_Speed = _other.E_Speed;
	E_Rotation = _other.E_Rotation;
	WhichBulletToUse = _other.WhichBulletToUse;
	ScaleMult = _other.E_Scale;
	MAX_BULLETS_IN_POOL = _other.MAX_BULLETS_IN_POOL;
	BulletTexturePosition = _other.BulletTexturePosition;
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
	BulletsInPool = new Bullet[MAX_BULLETS_IN_POOL];

	for (int i = 0; i < MAX_BULLETS_IN_POOL; ++i)
	{
		BulletsInPool[i].SetTexturePosition(BulletTexturePosition);
		BulletsInPool[i].SetTextureManagerRef(GetTextureManagerRef());
		BulletsInPool[i].BeginPlay();
	}

}

//Update: Called Every Tick in the Update Section && MUST BE USER CALLED
void Gunner::Update()
{
	//Call Parent Update
	Player::Update();

	for (int i = 0; i < MAX_BULLETS_IN_POOL; ++i)
	{
		BulletsInPool[i].Update();
	}
}

//Draw: Called Every Tick in the Draw Section && MUST BE USER CALLED
void Gunner::Draw()
{
	Player::Draw();

	for (int i = 0; i < MAX_BULLETS_IN_POOL; ++i)
	{
		BulletsInPool[i].Draw();
	}
}

bool Gunner::DidBulletHitEnemy(Entity& _enemy)
{
	for (int i = 0; i < MAX_BULLETS_IN_POOL; ++i)
	{
		if (BulletsInPool[i].CollisionCheck(_enemy))
		{
			return true;
		}
	}
	return false;
}

void Gunner::Shoot(float _speed, float _lifetime)
{
	//Shoot Function
	Driscoll::Vector2D unitVectorBasedOnCurrentRotation = { Driscoll::SinDeg<float>(E_Rotation), -Driscoll::CosDeg<float>(E_Rotation) };
	Driscoll::Vector2D spawnPositionBasedOnEndOfTurret = { ((GetTextureManagerRef()->GetTexture(E_TextureLocation).GetWidth() * unitVectorBasedOnCurrentRotation.x) + E_Position.x),
		((GetTextureManagerRef()->GetTexture(E_TextureLocation).GetHeight() * unitVectorBasedOnCurrentRotation.y) + E_Position.y) };
	BulletsInPool[WhichBulletToUse].SpawnBullet(spawnPositionBasedOnEndOfTurret, unitVectorBasedOnCurrentRotation, _speed, _lifetime);

	++WhichBulletToUse;

	if (WhichBulletToUse >= MAX_BULLETS_IN_POOL)
	{
		WhichBulletToUse = 0;
	}
}


/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* Gunner SPECIFIC GET FUNCTIONS */

/*** ------------------------------------------------------------------------------------------------------------------------------------ ***/

/* Gunner SPECIFIC SET FUNCTIONS */

void Gunner::SetScale(Driscoll::Vector2D _newScale)
{
	E_Scale = ScaleMult * _newScale;
}