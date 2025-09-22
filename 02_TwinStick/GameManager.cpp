#include "GameManager.h"

GameManager::GameManager()
{
  Player = nullptr;
}

GameManager::~GameManager()
{
  if (Player)
  {
    delete Player;
  }
}

void GameManager::BeginPlay()
{
  raylib::Image PlayerImage; PlayerImage.Load("Resources/Dollar-Gold-Coin-PNG.png");
  Player = new Character(Driscoll::Vector2D(500, 300), PlayerImage, Driscoll::Vector2D(0.5f, 0.5f), Driscoll::Vector2D(1, 1), 20.0f, 0.0f, 2.5f);
  Player->BeginPlay();
}

void GameManager::Update()
{
  Player->Update();

  //Check Collision with bullets for enemies

}

void GameManager::Draw()
{
  Player->Draw();
}