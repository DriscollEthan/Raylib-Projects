#include "Enemy.h"

Enemy::Enemy(LocalData2D _localData, size_t _textureLocation, Driscoll::Vector2D _origin, HitboxData _hitbox, float _speed, float _bulletLifetime, float _bulletSpeed) : Entity(_localData, _textureLocation, _origin, _hitbox, _speed)
{
  Turret = nullptr;
  PlayerRef = nullptr;
  ShootingTimer = {};
  RandomMoveToLocation = {};
  BulletSpeed = _bulletSpeed;
  BulletLifetime = _bulletLifetime;
}

Enemy::Enemy(const Enemy& _other)
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
  PlayerRef = nullptr;
  ShootingTimer = _other.ShootingTimer;
  TextureManagerRef = _other.TextureManagerRef;
}

Enemy& Enemy::operator=(const Enemy& _other)
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
  PlayerRef = nullptr;
  ShootingTimer = _other.ShootingTimer;
  TextureManagerRef = _other.TextureManagerRef;
  return *this;
}

Enemy::~Enemy()
{
  if (Turret)
  {
    delete Turret;
  }
}

void Enemy::BeginPlay()
{
  Entity::BeginPlay();
  //Init Vars
  Turret = new Gunner(LocalData2D({ 0, 0 }, 0, { 0.5f, 1.0f }), 1, { 0.5f, 1.f }, HitboxData(), 3, 0);
  Turret->SetTextureManagerRef(GetTextureManagerRef());
  Turret->SetParent(this);

  Turret->BeginPlay();
}

void Enemy::Update()
{
  if (bIsAlive)
  {
    Entity::Update();

    if (PlayerRef)
    {
      Turret->SetLocalRotation(GetWorldPosition().AngleBetween(PlayerRef->GetWorldPosition()) - 1.45f);
    }


    ShootingTimer.TimerUpdate();

    if (ShootingTimer.TimerOver())
    {
      Turret->Shoot(3.0f, 3.5f);
      ShootingTimer.ResetTimer();
    }


    //Movement for Enemy using a Random Position On Screen
    //MoveToRandomLocation();

    Turret->Update();
  }
}

void Enemy::Draw()
{
  if (bIsAlive)
  {
    Entity::Draw();
    Turret->Draw();
  }
}

void Enemy::GotHit()
{
  std::cout << "Hit \n";
  SetIsAlive(false);
}

void Enemy::SetPlayerRef(Entity* _playerRef)
{
  PlayerRef = _playerRef;
}

void Enemy::SetTimer(Timer _newTimer)
{
  ShootingTimer = _newTimer;
}

void Enemy::SetRandomLocation()
{
  RandomMoveToLocation = { GetRandomValue(0, GlobalVariables.ScreenX), GetRandomValue(0, GlobalVariables.ScreenY) };
}

void Enemy::MoveToRandomLocation()
{
  //Early Exit to grab new location if already at RandomLocation.
  if (GetWorldPosition().NearlyEquals(RandomMoveToLocation, 5))
  {
    SetRandomLocation();
  }

  MovementVector = { Driscoll::SinDeg<float>(RandomMoveToLocation.AngleBetween(GetWorldPosition()) * Driscoll::Deg2Rad + 90.0f), -Driscoll::CosDeg<float>(RandomMoveToLocation.AngleBetween(GetWorldPosition()) * Driscoll::Deg2Rad + 90.0f) };

  Move();
}

Gunner* Enemy::GetTurretRef()
{
  return Turret;
}
