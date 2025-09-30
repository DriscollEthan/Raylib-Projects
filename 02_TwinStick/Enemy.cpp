#include "Enemy.h"

Enemy::Enemy(Driscoll::Vector2D _position, size_t _textureLocation, Driscoll::Vector2D _origin, Driscoll::Vector2D _scale, float _radius, float _rotation, float _speed) : Entity(_position, _textureLocation, _origin, _scale, _radius, _rotation, _speed)
{
  Turret = nullptr;
  PlayerRef = nullptr;
  ShootingTimer = {};
  RandomMoveToLocation = {};
}

Enemy::Enemy(const Enemy& _other)
{
  E_Position = _other.E_Position;
  TextureIndex = _other.TextureIndex;
  Origin = _other.Origin;
  E_Scale = _other.E_Scale;
  E_Radius = _other.E_Radius;
  MovementVector = _other.MovementVector;
  Speed = _other.Speed;
  E_Rotation = _other.E_Rotation;
  Turret = nullptr;
  PlayerRef = nullptr;
  ShootingTimer = _other.ShootingTimer;
  TextureManagerRef = _other.TextureManagerRef;
}

Enemy& Enemy::operator=(const Enemy& _other)
{
  E_Position = _other.E_Position;
  TextureIndex = _other.TextureIndex;
  Origin = _other.Origin;
  E_Scale = _other.E_Scale;
  E_Radius = _other.E_Radius;
  MovementVector = _other.MovementVector;
  Speed = _other.Speed;
  E_Rotation = _other.E_Rotation;
  Turret = nullptr;
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
  Turret = new Gunner(E_Position, 1, { 0.5f, 1 }, { (E_Scale.x / 2.0f), E_Scale.y }, 0, E_Rotation, 0, 3, 0);
  Turret->SetTextureManagerRef(GetTextureManagerRef());

  Turret->BeginPlay();
}

void Enemy::Update()
{
  if (bIsAlive)
  {
    Entity::Update();

    if (PlayerRef)
    {
      Turret->SetLocalRotation(PlayerRef->GetPosition().AngleBetween(E_Position) * Driscoll::Deg2Rad + 90.0f);
    }


    ShootingTimer.TimerUpdate();

    if (ShootingTimer.TimerOver())
    {
      Turret->Shoot(3.0f, 3.5f);
      ShootingTimer.ResetTimer();
    }


    //Movement for Enemy using a Random Position On Screen
    MoveToRandomLocation();

    //Turret Position and Scale
    Turret->SetLocalPosition(E_Position);
    Turret->SetScale(E_Scale);

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
  RandomMoveToLocation = { GetRandomValue(0, GVO.GetScreenSizeIntX()), GetRandomValue(0, GVO.GetScreenSizeIntY()) };
}

void Enemy::MoveToRandomLocation()
{
  //Early Exit to grab new location if already at RandomLocation.
  if (E_Position.NearlyEquals(RandomMoveToLocation, 5))
  {
    SetRandomLocation();
  }

  MovementVector = { Driscoll::SinDeg<float>(RandomMoveToLocation.AngleBetween(E_Position) * Driscoll::Deg2Rad + 90.0f), -Driscoll::CosDeg<float>(RandomMoveToLocation.AngleBetween(E_Position) * Driscoll::Deg2Rad + 90.0f) };

  Move();
}

Gunner* Enemy::GetTurretRef()
{
  return Turret;
}
