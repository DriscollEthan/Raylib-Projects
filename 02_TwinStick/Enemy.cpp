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
  SwitchingColorTimer = _other.SwitchingColorTimer;
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
  SwitchingColorTimer = _other.SwitchingColorTimer;
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
  SetRandomLocation();
  SetLocalPosition(RandomMoveToLocation);

  //Init Vars
  Turret = new Gunner(LocalData2D({ 0, 0 }, 5, { 1.0f, 1.0f }), 8, { 0.5f, 1.f }, HitboxData(), 5, 4);
  Turret->SetTextureManagerRef(GetTextureManagerRef());
  Turret->SetParent(this);

  SetLocalRotation(0);

  SetHealth(3);
  SwitchingColorTimer.SetTimerInSeconds(0.0f, 0.25f);
  bShowHit = false;
  HitColorShowingTimer.SetTimerInSeconds(0.0f, 0.6f);
  SwitchHitColorTimer.SetTimerInSeconds(0.0f, 0.15f);

  SetRandomLocation();

  ExplosionIterationCount = 0;
  DeadExplosionCountingTimer.SetTimerInSeconds(0.0f, 0.15f);

  Turret->BeginPlay();
}

void Enemy::Update()
{
  if (bIsAlive)
  {
    Entity::Update();

    if (bLastHit && SwitchingColorTimer.RunTimer(GetFrameTime()))
    {
      SwitchingColorTimer.ResetTimer();
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
    

    if (bShowHit)
    {
      if (!HitColorShowingTimer.RunTimer(GetFrameTime()))
      {
        if (SwitchHitColorTimer.RunTimer(GetFrameTime()))
        {
          if (DrawColor == Driscoll::PURPLE)
          {
            DrawColor = Driscoll::WHITE;
            SwitchHitColorTimer.ResetTimer();
          }
          else
          {
            DrawColor = Driscoll::PURPLE;
            SwitchHitColorTimer.ResetTimer();
          }
        }
      }
      else
      {
        bShowHit = false;
        HitColorShowingTimer.ResetTimer();
        DrawColor = Driscoll::WHITE;
        SwitchHitColorTimer.ResetTimer();
      }
    }

    if (PlayerRef)
    {
      Turret->SetLocalRotation(PlayerRef->GetWorldPosition().AngleBetween(GetWorldPosition()) - GetWorldRotation());
    }

    if (ShootingTimer.TimerUpdate(GetFrameTime()))
    {
      Turret->Shoot(3.0f, 3.5f);
      ShootingTimer.CustomSetTimer(2.0f, 1.0f);
    }


    //Movement for Enemy using a Random Position On Screen
    MoveToRandomLocation();

    //Call Entity Update to update Matricies and Hitbox Position.
    Entity::Update();
  }
  else
  {
    DrawColor = Driscoll::WHITE;
    //Run Timer for DeadSprite Drawing
    if (DeadExplosionCountingTimer.RunTimer(GetFrameTime()) && TextureIndex != 0)
    {
      switch (ExplosionIterationCount++)
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
        break;
      }
      DeadExplosionCountingTimer.ResetTimer();
    }
  }

  Turret->Update();
}

void Enemy::Draw()
{
  if (bIsAlive)
  {
    Entity::Draw();
  }
  //Draw Explosion Sprites
  else
  {
    if (TextureIndex != 0)
    {
      Entity::Draw();
    }
  }

  Turret->Draw();
}

void Enemy::GotHit()
{
  if (!bShowHit)
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
      bShowHit = true;
      break;
    case 2:
      //1/2 Turret Left
      Turret->SetTextureIndex(10);
      bShowHit = true;
      break;
    }

    if (GetHealth() < 0)
    {
      SetIsAlive(false);
    }
  }
}

void Enemy::SetPlayerRef(Entity* _playerRef)
{
  PlayerRef = _playerRef;
}

void Enemy::SetTimer(float _length, float _deviation)
{
  ShootingTimer.CustomSetTimer(_length, _deviation);
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
