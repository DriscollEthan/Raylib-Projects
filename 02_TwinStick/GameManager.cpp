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
  TextureManagerRef = new TextureManager(3);
  //Set Textures
  {
    raylib::Image PlayerImage; PlayerImage.Load("Resources/Dollar-Gold-Coin-PNG.png");
    TextureManagerRef->SetTexture(PlayerImage, 0);
    raylib::Image TurretImage; TurretImage.Load("Resources/Turret.png");
    TextureManagerRef->SetTexture(TurretImage, 1);
    raylib::Image DefaultImage; DefaultImage.Load("Resources/Default.png");
    TextureManagerRef->SetTexture(DefaultImage, 2);
  }

  PlayerRef = new Character(Driscoll::Vector2D(500, 300), 0, Driscoll::Vector2D(0.5f, 0.5f), Driscoll::Vector2D(1, 1), 20.0f, 0.0f, 2.5f);
  PlayerRef->SetTextureManagerRef(TextureManagerRef);
  PlayerRef->BeginPlay();
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
