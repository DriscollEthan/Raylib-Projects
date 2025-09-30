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
  if (TextureManagerRef)
  {
    delete TextureManagerRef;
  }
}

void GameManager::BeginPlay()
{
  //CREATE TEXTURE MANAGER
  TextureManagerRef = new TextureManager(3);

  //SET TEXTURES
  {
    raylib::Image DefaultImage; DefaultImage.Load("Resources/Default.png");
    TextureManagerRef->SetTexture(DefaultImage, 0);
    raylib::Image PlayerImage; PlayerImage.Load("Resources/Dollar-Gold-Coin-PNG.png");
    TextureManagerRef->SetTexture(PlayerImage, 2);
    raylib::Image TurretImage; TurretImage.Load("Resources/Turret.png");
    TextureManagerRef->SetTexture(TurretImage, 1);
  }

  //CREATE PLAYER
  PlayerRef = new Character(Driscoll::Vector2D(500, 300), 2, Driscoll::Vector2D(0.5f, 0.5f), Driscoll::Vector2D(1, 1), 20.0f, 0.0f, 3.5f);
  PlayerRef->SetTextureManagerRef(TextureManagerRef);
  PlayerRef->BeginPlay();

  //CREATE ENEMIES
  EnemyRefs = new Enemy[10];
  for (int i = 0; i < 10; ++i)
  { 
    EnemyRefs[i] = { Driscoll::Vector2D(500, 300), 0, Driscoll::Vector2D(0.5f, 0.5f), Driscoll::Vector2D(1, 1), 20.0f, 0.0f, 2.5f };
    EnemyRefs[i].SetPlayerRef(PlayerRef);
    EnemyRefs[i].SetTimer(Timer(4.0f, 1.0f));
    EnemyRefs[i].SetTextureManagerRef(TextureManagerRef);
    EnemyRefs[i].BeginPlay();
  }
}

void GameManager::Update()
{
  //CHECK COLLISIONS
  for (int i = 0; i < 10; ++i)
  {
    PlayerRef->GetTurretRef()->BulletCollisionCheck(&EnemyRefs[i]);
    
    EnemyRefs[i].GetTurretRef()->BulletCollisionCheck(PlayerRef);
  }

  //UPDATE PLAYER
  PlayerRef->Update();

  //UPDATE ENEMIES
  for (int i = 0; i < 10; ++i)
  {
    EnemyRefs[i].Update();
  }
}

void GameManager::Draw()
{
  //DRAW PLAYER
  PlayerRef->Draw();

  //DRAW ENEMIES
  for (int i = 0; i < 10; ++i)
  {
    EnemyRefs[i].Draw();
  }
}
