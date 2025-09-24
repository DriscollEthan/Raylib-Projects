#include "GameManager.h"

GameManager::GameManager()
{
  PlayerRef = nullptr;
  EnemyRefs = nullptr;
}

GameManager::~GameManager()
{
  if (PlayerRef)
  {
    delete PlayerRef;
  }
  if (EnemyRefs)
  {
    delete[] EnemyRefs;
  }
}

void GameManager::BeginPlay()
{
  raylib::Image PlayerImage; PlayerImage.Load("Resources/Dollar-Gold-Coin-PNG.png");
  PlayerRef = new Character(Driscoll::Vector2D(500, 300), PlayerImage, Driscoll::Vector2D(0.5f, 0.5f), Driscoll::Vector2D(1, 1), 20.0f, 0.0f, 2.5f);
  PlayerRef->BeginPlay();
  EnemyRefs = new Enemy[10];
  for (int i = 0; i < 10; ++i)
  {
    raylib::Image test;
    EnemyRefs[i] = { Driscoll::Vector2D(500, 300), PlayerImage, Driscoll::Vector2D(0.5f, 0.5f), Driscoll::Vector2D(1, 1), 20.0f, 0.0f, 2.5f };
    EnemyRefs[i].SetPlayerRef(PlayerRef);
    EnemyRefs[i].SetTimer(Timer(5.0f, 1.0f));
    EnemyRefs[i].BeginPlay();
  }
}

void GameManager::Update()
{
  PlayerRef->Update();
  for (int i = 0; i < 10; ++i)
  {
    EnemyRefs[i].Update();
  }
}

void GameManager::Draw()
{
  PlayerRef->Draw();
  for (int i = 0; i < 10; ++i)
  {
    EnemyRefs[i].Draw();
  }
}