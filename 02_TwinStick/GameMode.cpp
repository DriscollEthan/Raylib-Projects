#include "GameMode.h"


GameMode::GameMode()
{
  PlayerRef = nullptr;
  EnemyRefs = nullptr;
}

GameMode::~GameMode()
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

void GameMode::BeginPlay()
{
  //CREATE TEXTURE MANAGER
  TextureManagerRef = new TextureManager(4);

  //SET TEXTURES
  {
    raylib::Image ImageLoader; 
    
    ImageLoader.Load("Resources/Default.png");
    TextureManagerRef->SetTexture(ImageLoader, 0);

    ImageLoader.Load("Resources/Turret.png");
    TextureManagerRef->SetTexture(ImageLoader, 1);

    ImageLoader.Load("Resources/Dollar-Gold-Coin-PNG.png");
    TextureManagerRef->SetTexture(ImageLoader, 2);

    ImageLoader.Load("Resources/target_round_b.png");
    TextureManagerRef->SetTexture(ImageLoader, 3);
  }

  //CREATE PLAYER
  PlayerRef = new Character(LocalData2D((GlobalVariables.ScreenSize / 2), 2, { 1, 1 }), 2, Driscoll::Vector2D(0.5f, 0.5f), HitboxData(), 5.0f, 10.0f, 4.5f);
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

void GameMode::Update()
{
  //CHECK COLLISIONS
  for (int i = 0; i < 10; ++i)
  {
    if (EnemyRefs[i].GetIsAlive())
    {
      PlayerRef->GetTurretRef()->BulletCollisionCheck(EnemyRefs[i]);
      EnemyRefs[i].GetTurretRef()->BulletCollisionCheck((*PlayerRef));
    }
  }

  //UPDATE PLAYER
  PlayerRef->Update();

  //UPDATE ENEMIES
  for (int i = 0; i < 10; ++i)
  {
    EnemyRefs[i].Update();
  }
}

void GameMode::Draw()
{
  //DRAW PLAYER
  PlayerRef->Draw();

  //DRAW ENEMIES
  for (int i = 0; i < 10; ++i)
  {
    EnemyRefs[i].Draw();
  }
}
