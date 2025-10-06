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
  TextureManagerRef = new TextureManager(13);

  /* Texture List: (TOTAL = 13)
   * 0 = DEFAULT (ALWAYS DEFAULT)
   * 1 = Player Image
   * 2 = Enemy Image
   * 3 = Player Bullet Image
   * 4 = Enemy Bullet Image
   * 5 = Mouse Image
   * 6 = Dirt Background Image
   * 7 = Tire Tracks Large
   * 8 = Max Health Turret 
   * 9 = 3/4 Health Turret
   * 10 = 1/2 Health Turret
   * 11 = 1/4 Health Turret
   * 12 = 0 Health Turret
   */

  //SET TEXTURES
  {
    raylib::Image ImageLoader; 
    
    ImageLoader.Load("Resources/Default.png");
    TextureManagerRef->SetTexture(ImageLoader, 0);

    ImageLoader.Load("Resources/Tanks/tankBlue_outline.png");
    TextureManagerRef->SetTexture(ImageLoader, 1);

    ImageLoader.Load("Resources/Tanks/tankRed_outline.png");
    TextureManagerRef->SetTexture(ImageLoader, 2);

    ImageLoader.Load("Resources/Bullets/bulletGreenSilver_outline.png");
    TextureManagerRef->SetTexture(ImageLoader, 3);

    ImageLoader.Load("Resources/Bullets/bulletRedSilver_outline.png");
    TextureManagerRef->SetTexture(ImageLoader, 4);

    ImageLoader.Load("Resources/target_round_b.png");
    TextureManagerRef->SetTexture(ImageLoader, 5);

    ImageLoader.Load("Resources/Environment/dirt.png");
    TextureManagerRef->SetTexture(ImageLoader, 6);

    ImageLoader.Load("Resources/Tanks/tracksLarge.png");
    TextureManagerRef->SetTexture(ImageLoader, 7);

    ImageLoader.Load("Resources/Tanks/barrelWhite_outline-0Hit.png");
    TextureManagerRef->SetTexture(ImageLoader, 8);

    ImageLoader.Load("Resources/Tanks/barrelWhite_outline-1Hit.png");
    TextureManagerRef->SetTexture(ImageLoader, 9);

    ImageLoader.Load("Resources/Tanks/barrelWhite_outline-2Hit.png");
    TextureManagerRef->SetTexture(ImageLoader, 10);

    ImageLoader.Load("Resources/Tanks/barrelWhite_outline-3Hit.png");
    TextureManagerRef->SetTexture(ImageLoader, 11);

    ImageLoader.Load("Resources/Tanks/barrelWhite_outline-4Hit.png");
    TextureManagerRef->SetTexture(ImageLoader, 12);
  }

  //CREATE PLAYER
  PlayerRef = new Character(LocalData2D((GlobalVariables.ScreenSize / 2), 0, { 1, 1 }), 1, Driscoll::Vector2D(0.5f, 0.5f), HitboxData(50.0F), 5.0f, 5.0F, 3.5f);
  PlayerRef->SetTextureManagerRef(TextureManagerRef);
  PlayerRef->BeginPlay();

  //CREATE ENEMIES
  EnemyRefs = new Enemy[10];
  for (int i = 0; i < 10; ++i)
  {
    EnemyRefs[i] = { LocalData2D((GlobalVariables.ScreenSize / 2), 4, {1, 1}), 2, Driscoll::Vector2D(0.5f, 0.5f), HitboxData(60.0f), 3.5f, 3.5f, 3.0f };
    EnemyRefs[i].SetPlayerRef(PlayerRef);
    EnemyRefs[i].SetTimer(Timer(3.0f, 1.0f));
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
  //Draw Background
  int NextEnvironmentPosiiton = GlobalVariables.ScreenX / TextureManagerRef->GetTexture(8).GetWidth();
  int HowManyImagesPerColumn = GlobalVariables.ScreenY / TextureManagerRef->GetTexture(8).GetHeight();
  raylib::Texture& backgroundTexture = TextureManagerRef->GetTexture(6);


  for (int j = 0; j < NextEnvironmentPosiiton; ++j)
  {
    for (int k = 0; k < HowManyImagesPerColumn; ++k)
    {
      //Color Options
      // 1: 185, 133, 85
      // 2: 233, 160, 99
      backgroundTexture.Draw(j * backgroundTexture.GetWidth(), k * backgroundTexture.GetHeight(), Driscoll::Color(185, 133, 85, 255));
    }
  }

  //DRAW ENEMIES
  for (int i = 0; i < 10; ++i)
  {
    EnemyRefs[i].Draw();
  }

  //DRAW PLAYER
  PlayerRef->Draw();

  //DRAW MOUSE
  raylib::Texture& MouseTexture = TextureManagerRef->GetTexture(5);
  MouseTexture.Draw(GetMousePosition().x - (MouseTexture.GetWidth() / 2), GetMousePosition().y - (MouseTexture.GetHeight() / 2));
}
