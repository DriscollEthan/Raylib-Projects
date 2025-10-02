#include "Gunner.h"
#include "Utils.h"

/* CONSTRUCTORS & DESTRUCTORS */

//DEFAULT CONSTRUCTOR
Gunner::Gunner(LocalData2D _localData, size_t _textureLocation, Driscoll::Vector2D _origin, HitboxData _hitbox, size_t _maxBulletsInPool, size_t _bulletTextureIndex) : Entity(_localData, _textureLocation, _origin, _hitbox)
{
	WhichBulletToUse = 0;
	BulletsInPool = nullptr;
	MAX_BULLETS_IN_POOL = _maxBulletsInPool;
	BulletTextureIndex = _bulletTextureIndex;
}

//Copy Constructor
Gunner::Gunner(const Gunner& _other)
{
	BulletsInPool = nullptr;
	LocalData = _other.LocalData;
	TextureIndex = _other.TextureIndex;
	Origin = _other.Origin;
	Hitbox = _other.Hitbox;
	MovementVector = _other.MovementVector;
	Speed = _other.Speed;
	WhichBulletToUse = _other.WhichBulletToUse;
	MAX_BULLETS_IN_POOL = _other.MAX_BULLETS_IN_POOL;
	TextureManagerRef = _other.TextureManagerRef;
	BulletTextureIndex = _other.BulletTextureIndex;
}

//Copy Assignment
Gunner Gunner::operator=(const Gunner& _other)
{
	BulletsInPool = nullptr;
	LocalData = _other.LocalData;
	TextureIndex = _other.TextureIndex;
	Origin = _other.Origin;
	Hitbox = _other.Hitbox;
	MovementVector = _other.MovementVector;
	Speed = _other.Speed;
	WhichBulletToUse = _other.WhichBulletToUse;
	MAX_BULLETS_IN_POOL = _other.MAX_BULLETS_IN_POOL;
	TextureManagerRef = _other.TextureManagerRef;
	BulletTextureIndex = _other.BulletTextureIndex;
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
	Entity::BeginPlay();

	//Init Vars
	BulletsInPool = new Bullet[MAX_BULLETS_IN_POOL];

	for (int i = 0; i < MAX_BULLETS_IN_POOL; ++i)
	{
		BulletsInPool[i].SetTextureIndex(BulletTextureIndex);
		BulletsInPool[i].SetTextureManagerRef(GetTextureManagerRef());
		BulletsInPool[i].BeginPlay();
	}

}

//Update: Called Every Tick in the Update Section && MUST BE USER CALLED
void Gunner::Update()
{
	//Call Parent Update
	Entity::Update();

	for (int i = 0; i < MAX_BULLETS_IN_POOL; ++i)
	{
		BulletsInPool[i].Update();
	}
}

//Draw: Called Every Tick in the Draw Section && MUST BE USER CALLED
void Gunner::Draw()
{
	Entity::Draw();

	for (int i = 0; i < MAX_BULLETS_IN_POOL; ++i)
	{
		BulletsInPool[i].Draw();
	}
}

void Gunner::BulletCollisionCheck(Entity& _enemy)
{
	for (int i = 0; i < MAX_BULLETS_IN_POOL; ++i)
	{
		if (BulletsInPool[i].GetCurrentState() == Active && BulletsInPool[i].GetHitbox().CheckCollision(_enemy.GetHitbox()))
		{
			BulletsInPool[i].SetCurrentState(Inactive);
			_enemy.GotHit();
		}
	}
}

void Gunner::Shoot(float _speed, float _lifetime)
{
	//Shoot Function
	raylib::Texture& texture = GetTextureManagerRef()->GetTexture(TextureIndex);

	Driscoll::Vector2D unitVectorBasedOnCurrentRotation = { Driscoll::CosDeg<float>(GetWorldRotation() * Driscoll::Rad2Deg), Driscoll::SinDeg<float>(GetWorldRotation() * Driscoll::Rad2Deg) };
	Driscoll::Vector2D spawnPositionBasedOnEndOfTurret = { ((texture.GetWidth() * unitVectorBasedOnCurrentRotation.x) + GetWorldPosition().x),
		((texture.GetHeight() * unitVectorBasedOnCurrentRotation.y) + GetWorldPosition().y)};
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