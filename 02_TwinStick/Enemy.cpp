#include "Enemy.h"

Enemy::Enemy(Driscoll::Vector2D _position, raylib::Image _texture, Driscoll::Vector2D _origin, Driscoll::Vector2D _scale, float _radius, float _rotation, float _speed) : Entity(_position, _texture, _origin, _scale, _radius, _rotation, _speed)
{
  Turret = nullptr;
  PlayerRef = nullptr;
  ShootingTimer = {};
  RandomMoveToLocation = {};
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
  raylib::Image turretImage;
  turretImage.Load("Resources/Turret.png");
  raylib::Image bulletImage;
  //bulletImage.Load("Resources/Dollar-Gold-Coin-PNG.png");
  Turret = new Gunner(E_Position, turretImage, { 0.5f, 1 }, { (E_Scale.x / 2.0f), E_Scale.y }, 0, E_Rotation, 0, 3, bulletImage);

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
