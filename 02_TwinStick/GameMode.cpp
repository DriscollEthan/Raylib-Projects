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
  TextureManagerRef = new TextureManager(11);

  /* Texture List: (TOTAL = 11)
   * 0 = DEFAULT (ALWAYS DEFAULT)
   * 1 = Player Image
   * 2 = Player Turret Image
   * 3 = Player Bullet Image
   * 4 = Enemy Image
   * 5 = Enemy Turret Image
   * 6 = Enemy Bullet Image
   * 7 = Mouse Image
   * 8 = Dirt Background Image
   * 9 = Grass Background Image
   * 10 = Sand Background Image
   */

  //SET TEXTURES
  {
    raylib::Image ImageLoader; 
    
    ImageLoader.Load("Resources/Default.png");
    TextureManagerRef->SetTexture(ImageLoader, 0);

    ImageLoader.Load("Resources/Tanks/tankBlue_outline.png");
    TextureManagerRef->SetTexture(ImageLoader, 1);

    ImageLoader.Load("Resources/Tanks/barrelBlue_outline.png");
    TextureManagerRef->SetTexture(ImageLoader, 2);

    ImageLoader.Load("Resources/Bullets/bulletBlueSilver_outline.png");
    TextureManagerRef->SetTexture(ImageLoader, 3);

    ImageLoader.Load("Resources/Tanks/tankRed_outline.png");
    TextureManagerRef->SetTexture(ImageLoader, 4);

    ImageLoader.Load("Resources/Tanks/barrelRed_outline.png");
    TextureManagerRef->SetTexture(ImageLoader, 5);

    ImageLoader.Load("Resources/Bullets/bulletRedSilver_outline.png");
    TextureManagerRef->SetTexture(ImageLoader, 6);

    ImageLoader.Load("Resources/target_round_b.png");
    TextureManagerRef->SetTexture(ImageLoader, 7);

    ImageLoader.Load("Resources/Environment/dirt.png");
    TextureManagerRef->SetTexture(ImageLoader, 8);

    ImageLoader.Load("Resources/Environment/grass.png");
    TextureManagerRef->SetTexture(ImageLoader, 9);

    ImageLoader.Load("Resources/Environment/sand.png");
    TextureManagerRef->SetTexture(ImageLoader, 10);
  }

  //CREATE PLAYER
  PlayerRef = new Character(LocalData2D((GlobalVariables.ScreenSize / 2), 0, { 1, 1 }), 1, Driscoll::Vector2D(0.5f, 0.5f), HitboxData(50.0F), 5.0f, 10.0f, 4.5f);
  PlayerRef->SetTextureManagerRef(TextureManagerRef);
  PlayerRef->BeginPlay();

  //CREATE ENEMIES
  EnemyRefs = new Enemy[10];
  for (int i = 0; i < 10; ++i)
  {
    EnemyRefs[i] = { LocalData2D((GlobalVariables.ScreenSize / 2), 4, {1, 1}), 4, Driscoll::Vector2D(0.5f, 0.5f), HitboxData(60.0f), 3.5f, 3.0f, 2.5f };
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
  //Draw Background
  int EnvironmentCount = 3;
  int NextEnvironmentPosiiton = GlobalVariables.ScreenX / (3 * TextureManagerRef->GetTexture(8).GetWidth());
  int HowManyImagesPerColumn = GlobalVariables.ScreenY / TextureManagerRef->GetTexture(8).GetHeight();

  for (int i = 0; i < EnvironmentCount; ++i)
  {
    raylib::Texture& texture = TextureManagerRef->GetTexture(8);
    for (int j = 0; j < NextEnvironmentPosiiton; ++j)
    {
      for (int k = 0; k < HowManyImagesPerColumn; ++k)
      {
        texture.Draw(j * texture.GetWidth(), k * texture.GetHeight(), Driscoll::WHITE);
      }
    }

    texture = TextureManagerRef->GetTexture(9);
    for (int j = NextEnvironmentPosiiton; j < NextEnvironmentPosiiton * 2; ++j)
    {
      for (int k = 0; k < HowManyImagesPerColumn; ++k)
      {
        texture.Draw(j * texture.GetWidth(), k * texture.GetHeight(), Driscoll::WHITE);
      }
    }

    TextureManagerRef->GetTexture(10);
    for (int j = NextEnvironmentPosiiton * 2; j < NextEnvironmentPosiiton * 3; ++j)
    {
      for (int k = 0; k < HowManyImagesPerColumn; ++k)
      {
        texture.Draw(j * texture.GetWidth(), k * texture.GetHeight(), Driscoll::WHITE);
      }
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
  raylib::Texture& MouseTexture = TextureManagerRef->GetTexture(7);
  MouseTexture.Draw(GetMousePosition().x - (MouseTexture.GetWidth() / 2), GetMousePosition().y - (MouseTexture.GetHeight() / 2));
}
