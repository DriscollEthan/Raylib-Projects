#include "Enemy.h"

Enemy::Enemy(LocalData2D _localData, size_t _textureLocation, Driscoll::Vector2D _origin, HitboxData _hitbox, float _speed, float _bulletLifetime, float _bulletSpeed) : Entity(_localData, _textureLocation, _origin, _hitbox, _speed)
{
  Turret = nullptr;
  PlayerRef = nullptr;
  ShootingTimer = {};
  RandomMoveToLocation = {};
  BulletSpeed = _bulletSpeed;
  BulletLifetime = _bulletLifetime;
  bLastHit = false;
  bFlipFlop = true;
  SwitchingColorTime = 0.f;
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
  bLastHit = _other.bLastHit;
  bFlipFlop = _other.bFlipFlop;
  SwitchingColorTime = _other.SwitchingColorTime;
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
  bLastHit = _other.bLastHit;
  bFlipFlop = _other.bFlipFlop;
  SwitchingColorTime = _other.SwitchingColorTime;
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
  Turret = new Gunner(LocalData2D({ 0, 0 }, 5, { 1.0f, 1.0f }), 8, { 0.5f, 1.f }, HitboxData(), 5, 4);
  Turret->SetTextureManagerRef(GetTextureManagerRef());
  Turret->SetParent(this);
  SetLocalRotation(0);
  SetHealth(3);
  SetRandomLocation();

  Turret->BeginPlay();
}

void Enemy::Update()
{
  if (bIsAlive)
  {
    Entity::Update();

    if (bLastHit)
    {
      SwitchingColorTime += GetFrameTime();
      if (SwitchingColorTime > 0.25f)
      {
        SwitchingColorTime = 0;
        bFlipFlop = !bFlipFlop;
        if (bFlipFlop)
        {
          DrawColor = Driscoll::DARKRED;
          Turret->SetDrawColor(DrawColor);
        }
        else
        {
          DrawColor = Driscoll::WHITE;
          Turret->SetDrawColor(DrawColor);
        }
      }
    }

    if (PlayerRef)
    {
      Turret->SetLocalRotation(PlayerRef->GetWorldPosition().AngleBetween(GetWorldPosition()) - GetWorldRotation());
    }


    ShootingTimer.TimerUpdate();

    if (ShootingTimer.TimerOver())
    {
      Turret->Shoot(3.0f, 3.5f);
      ShootingTimer.ResetTimer();
    }


    //Movement for Enemy using a Random Position On Screen
    MoveToRandomLocation();

    //Call Entity Update to update Matricies and Hitbox Position.
    Entity::Update();

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
  SetHealth(GetHealth() - 1);

  switch ((int)GetHealth())
  {
  case 0:
    //bool for last hit to flash colors
    bLastHit = true;
    DrawColor = Driscoll::DARKRED;
    Turret->SetDrawColor(DrawColor);
    break;
  case 1:
    //Full Turret
    Turret->SetTextureIndex(12);
    break;
  case 2:
    //1/2 Turret Left
    Turret->SetTextureIndex(10);
    break;
  }

  if (GetHealth() < 0)
  {
    SetIsAlive(false);
  }
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

  MovementVector = { Driscoll::SinDeg<float>(RandomMoveToLocation.AngleBetween(GetWorldPosition()) * Driscoll::Rad2Deg + 90.0f), -Driscoll::CosDeg<float>(RandomMoveToLocation.AngleBetween(GetWorldPosition()) * Driscoll::Rad2Deg + 90.0f) };

  SetLocalRotation(Driscoll::AngleFrom2D(MovementVector.x, MovementVector.y));

  Move();
}

Gunner* Enemy::GetTurretRef()
{
  return Turret;
}

float Enemy::GetHealth()
{
  return Health;
}

void Enemy::SetHealth(float _maxHealth)
{
  Health = _maxHealth;
}
