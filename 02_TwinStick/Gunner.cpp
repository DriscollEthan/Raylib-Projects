#include "Gunner.h"
#include "Utils.h"

/* CONSTRUCTORS & DESTRUCTORS */

//DEFAULT CONSTRUCTOR
Gunner::Gunner(Driscoll::Vector2D _position, raylib::Image _texture, Driscoll::Vector2D _origin, Driscoll::Vector2D _scale, float _radius, float _rotation, float _speed, int _maxBulletsInPool, raylib::Image _bulletImage) : Player(_position, _texture, _origin, _scale, _radius, _rotation, _speed)
{
	WhichBulletToUse = 0;
	ScaleMult = _scale;
	BulletsInPool = nullptr;
	MAX_BULLETS_IN_POOL = _maxBulletsInPool;
	if (_bulletImage.IsValid())
	{
		BulletImage = _bulletImage;
	}
	else
	{
		BulletImage.Load("Resources/DEFAULT.png"); 
			std::cout << "\033[1;31mWARNING: A GUNNER WAS CONSTRUCTED WITHOUT A VALID IMAGE FOR THE BULLET, USING DEFAULT IMAGE \033[0m\n";
	}
}

//Copy Constructor
Gunner::Gunner(const Gunner& _other)
{
	BulletsInPool = nullptr;
	E_Position = _other.E_Position;
	E_Texture = _other.E_Texture.GetData();
	E_Origin = _other.E_Origin;
	E_Scale = _other.E_Scale;
	E_Radius = _other.E_Radius;
	E_MovementVector = _other.E_MovementVector;
	E_Speed = _other.E_Speed;
	E_Rotation = _other.E_Rotation;
	WhichBulletToUse = _other.WhichBulletToUse;
	ScaleMult = _other.E_Scale;
	MAX_BULLETS_IN_POOL = _other.MAX_BULLETS_IN_POOL;
	BulletImage = _other.BulletImage;
}

//Copy Assignment
Gunner Gunner::operator=(const Gunner& _other)
{
	BulletsInPool = nullptr;
	E_Position = _other.E_Position;
	E_Texture = _other.E_Texture.GetData();
	E_Origin = _other.E_Origin;
	E_Scale = _other.E_Scale;
	E_Radius = _other.E_Radius;
	E_MovementVector = _other.E_MovementVector;
	E_Speed = _other.E_Speed;
	E_Rotation = _other.E_Rotation;
	WhichBulletToUse = _other.WhichBulletToUse;
	ScaleMult = _other.E_Scale;
	MAX_BULLETS_IN_POOL = _other.MAX_BULLETS_IN_POOL;
	BulletImage = _other.BulletImage;
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
		BulletsInPool[i].BeginPlay();
		BulletsInPool[i].SetTexture(BulletImage);
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
	Driscoll::Vector2D spawnPositionBasedOnEndOfTurret = { ((E_Texture.GetWidth() * unitVectorBasedOnCurrentRotation.x) + E_Position.x),
		((E_Texture.GetHeight() * unitVectorBasedOnCurrentRotation.y) + E_Position.y) };
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