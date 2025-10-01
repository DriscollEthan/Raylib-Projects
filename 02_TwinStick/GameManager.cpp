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
    raylib::Image TurretImage; TurretImage.Load("Resources/Turret.png");
    TextureManagerRef->SetTexture(TurretImage, 1);
    raylib::Image PlayerImage; PlayerImage.Load("Resources/Dollar-Gold-Coin-PNG.png");
    TextureManagerRef->SetTexture(PlayerImage, 2);
  }

  //CREATE PLAYER
  PlayerRef = new Character(LocalData2D((GlobalVariables.ScreenSize / 2), 2, {1, 1}), 2, Driscoll::Vector2D(0.5f, 0.5f), HitboxData(), 5.0f, 10.0f, 4.5f);
  PlayerRef->SetTextureManagerRef(TextureManagerRef);
  PlayerRef->SetHitboxRadius(20.0f);
  PlayerRef->BeginPlay();

  //CREATE ENEMIES
  EnemyRefs = new Enemy[10];
  for (int i = 0; i < 10; ++i)
  { 
    EnemyRefs[i] = { LocalData2D((GlobalVariables.ScreenSize / 2), 0, {1, 1}), 2, Driscoll::Vector2D(0.5f, 0.5f), HitboxData(), 3.5f, 3.0f, 2.5f };
    EnemyRefs[i].SetHitboxRadius(25.0f);
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
    PlayerRef->GetTurretRef()->BulletCollisionCheck(EnemyRefs[i]);
    
    EnemyRefs[i].GetTurretRef()->BulletCollisionCheck((*PlayerRef));
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
