#include "GameManager.h"

GameManager::GameManager()
{
  PlayerRef = nullptr;
  EnemyRef = nullptr;
}

GameManager::~GameManager()
{
  if (PlayerRef)
  {
    delete PlayerRef;
  }
  if (EnemyRef)
  {
    delete EnemyRef;
  }
}

void GameManager::BeginPlay()
{
  raylib::Image PlayerImage; PlayerImage.Load("Resources/Dollar-Gold-Coin-PNG.png");
  PlayerRef = new Character(Driscoll::Vector2D(500, 300), PlayerImage, Driscoll::Vector2D(0.5f, 0.5f), Driscoll::Vector2D(1, 1), 20.0f, 0.0f, 2.5f);
  PlayerRef->BeginPlay();
  EnemyRef = new Enemy(Driscoll::Vector2D(500, 300), PlayerImage, Driscoll::Vector2D(0.5f, 0.5f), Driscoll::Vector2D(1, 1), 20.0f, 0.0f, 2.5f);
  EnemyRef->SetPlayerRef(PlayerRef);
  EnemyRef->BeginPlay();
}

void GameManager::Update()
{
  PlayerRef->Update();
  EnemyRef->Update();
  //Check Collision with bullets for enemies

}

void GameManager::Draw()
{
  PlayerRef->Draw();
  EnemyRef->Draw();
}