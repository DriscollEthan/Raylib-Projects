#include "GameManager.h"

GameManager::GameManager()
{
  bShouldShutdown = false;
  bShouldRestart = false;
}

GameManager::~GameManager()
{

}

void GameManager::BeginPlay()
{
  //CREATE TEXTURE MANAGER

  //SET TEXTURES

  //CREATE PLAYER

  //CREATE ENEMIES

}

void GameManager::Update()
{
  //CHECK COLLISIONS

  //UPDATE PLAYER

  //UPDATE ENEMIES

}

void GameManager::Draw()
{

}

bool GameManager::ShouldShutdown()
{
    return bShouldShutdown;
}

bool GameManager::ShouldRestart()
{
    return bShouldRestart;
}
