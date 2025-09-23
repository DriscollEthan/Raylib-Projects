#include "Enemy.h"

Enemy::Enemy(Driscoll::Vector2D _position, raylib::Image _texture, Driscoll::Vector2D _origin, Driscoll::Vector2D _scale, float _radius, float _rotation, float _speed) : Entity(_position, _texture, _origin, _scale, _radius, _rotation, _speed)
{
  Turret = nullptr;
  PlayerRef = nullptr;
  ShootingTimer = {};
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
  bulletImage.Load("Resources/Dollar-Gold-Coin-PNG.png");
  Turret = new Gunner(E_Position, turretImage, { 0.5, 1 }, { (E_Scale.x / 2.0f), E_Scale.y }, 0, E_Rotation, 0, 25, bulletImage);

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
    Turret->Shoot(2.0f, 3.0f);
    ShootingTimer.ResetTimer();
  }

  //Movement for Enemy

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
