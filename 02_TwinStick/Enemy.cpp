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
  E_TextureLocation = _other.E_TextureLocation;
  E_Origin = _other.E_Origin;
  E_Scale = _other.E_Scale;
  E_Radius = _other.E_Radius;
  E_MovementVector = _other.E_MovementVector;
  E_Speed = _other.E_Speed;
  E_Rotation = _other.E_Rotation;
  Turret = nullptr;
  PlayerRef = nullptr;
  ShootingTimer = _other.ShootingTimer;
  E_TextureManagerRef = _other.E_TextureManagerRef;
}

Enemy& Enemy::operator=(const Enemy& _other)
{
  E_Position = _other.E_Position;
  E_TextureLocation = _other.E_TextureLocation;
  E_Origin = _other.E_Origin;
  E_Scale = _other.E_Scale;
  E_Radius = _other.E_Radius;
  E_MovementVector = _other.E_MovementVector;
  E_Speed = _other.E_Speed;
  E_Rotation = _other.E_Rotation;
  Turret = nullptr;
  PlayerRef = nullptr;
  ShootingTimer = _other.ShootingTimer;
  E_TextureManagerRef = _other.E_TextureManagerRef;
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
  Turret = new Gunner(E_Position, 1, { 0.5f, 1 }, { (E_Scale.x / 2.0f), E_Scale.y }, 0, E_Rotation, 0, 3, 2);
  Turret->SetTextureManagerRef(GetTextureManagerRef());

  Turret->BeginPlay();
}

void Enemy::Update()
{
  Entity::Update();

  if (PlayerRef)
  {
    Turret->Rotate(PlayerRef->GetPosition().AngleBetween(E_Position) * Driscoll::Deg2Rad + 90.0f);
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
  Turret->SetPosition(E_Position);
  Turret->SetScale(E_Scale);

  Turret->Update();
}

void Enemy::Draw()
{
  Entity::Draw();
  Turret->Draw();
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

  E_MovementVector = { Driscoll::SinDeg<float>(RandomMoveToLocation.AngleBetween(E_Position) * Driscoll::Deg2Rad + 90.0f), -Driscoll::CosDeg<float>(RandomMoveToLocation.AngleBetween(E_Position) * Driscoll::Deg2Rad + 90.0f) };

  Move();
}
