#include "GameMode.h"

#include <string.h>


GameMode::GameMode()
{
  PlayerRef = nullptr;
  EnemyRefs = nullptr;
  StartButtonRef = nullptr;
  QuitButtonRef = nullptr;
  RestartButtonRef = nullptr;
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
  if (StartButtonRef)
  {
    delete StartButtonRef;
  }
  if (QuitButtonRef)
  {
    delete QuitButtonRef;
  }
  if (RestartButtonRef)
  {
    delete RestartButtonRef;
  }
}

void GameMode::BeginPlay()
{
  //CREATE TEXTURE MANAGER
  TextureManagerRef = new TextureManager(14);

  /* Texture List: (TOTAL = 14)
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
   * 13 = ButtonImageBackground
   */

  //SET TEXTURES
  {
    CurrentState = MainMenu;

    raylib::Image ImageLoader; 
    
    ImageLoader.Load("Resources/Default.png");
    TextureManagerRef->SetTexture(ImageLoader, 0);

    ImageLoader.Load("Resources/Tanks/tankBlue_outline.png");
    TextureManagerRef->SetTexture(ImageLoader, 1);

    ImageLoader.Load("Resources/Tanks/tankRed_outline.png");
    TextureManagerRef->SetTexture(ImageLoader, 2);

    ImageLoader.Load("Resources/Bullets/bulletBlueSilver_outline.png");
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

    ImageLoader.Load("Resources/ButtonImage.png");
    TextureManagerRef->SetTexture(ImageLoader, 13);
  }

  //Setup for MainMenu State;
  {
    raylib::Text setupText = raylib::Text();
    std::string setupString = std::string("Start Game");
    setupText.SetText(setupString);
    setupText.SetFontSize(50);
    setupText.SetSpacing(5.0f);

    StartButtonRef = new MenuObject({ GlobalVariables.ScreenX / 2.f, 400 }, { 400, 200 }, Driscoll::BLACK, Driscoll::TEAL, Driscoll::CYAN, Driscoll::ORANGE, setupText);
    StartButtonRef->SetTextureManagerRef(TextureManagerRef);
    StartButtonRef->SetTextureIndex(13);
    StartButtonRef->BeginPlay();

    setupString = std::string("Quit Game");
    setupText.SetText(setupString);
    QuitButtonRef = new MenuObject({ GlobalVariables.ScreenX / 2.f, 800 }, { 400, 200 }, Driscoll::BLACK, Driscoll::TEAL, Driscoll::CYAN, Driscoll::ORANGE, setupText);
    QuitButtonRef->SetTextureManagerRef(TextureManagerRef);
    QuitButtonRef->SetTextureIndex(13);
    QuitButtonRef->BeginPlay();

    setupString = std::string("Tanky Game");
    setupText.SetFontSize(75);
    setupText.SetText(setupString);
    TitleRef = new MenuObject({ GlobalVariables.ScreenX / 2.f, 40 }, { 450, 80 }, Driscoll::TEAL, Driscoll::CLEAR, Driscoll::WHITE, Driscoll::CLEAR, setupText);
    TitleRef->SetTextureManagerRef(TextureManagerRef);
    TitleRef->SetTextureIndex(13);
    TitleRef->BeginPlay();
  }

  //Setup for PlayingGame State;
  {
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

  //Setup for EndMenu State;
  {
    raylib::Text setupText = raylib::Text();
    std::string setupString = std::string("Restart Game");
    setupText.SetText(setupString);
    setupText.SetFontSize(50);
    setupText.SetSpacing(5.0f);

    RestartButtonRef = new MenuObject({ GlobalVariables.ScreenX / 2.f, 400 }, { 400, 200 }, Driscoll::BLACK, Driscoll::TEAL, Driscoll::CYAN, Driscoll::ORANGE, setupText);
    RestartButtonRef->SetTextureManagerRef(TextureManagerRef);
    RestartButtonRef->SetTextureIndex(13);
    RestartButtonRef->BeginPlay();

    setupString = std::string("You Win!");
    setupText.SetText(setupString);
    setupText.SetFontSize(50);
    WinTextRef = new MenuObject({ GlobalVariables.ScreenX / 2.f, 160 }, { 300, 80 }, Driscoll::GREEN, Driscoll::CLEAR, Driscoll::BLUE, Driscoll::CLEAR, setupText);
    WinTextRef->SetTextureManagerRef(TextureManagerRef);
    WinTextRef->SetTextureIndex(13);
    WinTextRef->BeginPlay();
  }
}

void GameMode::Update()
{
  bool bIsStartHovered = false;
  bool bIsQuitHovered = false;
  bool bIsRestartHovered = false;

  bool bEnemiesDead = true;


  switch (CurrentState)
  {
  case MainMenu:
    //CHECK COLLISIONS
    bIsStartHovered = StartButtonRef->CheckCollision(GetMousePosition(), TextureManagerRef->GetTexture(5).GetWidth());
    if (bIsStartHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      CurrentState = PlayingGame;
      break;
    }

    bIsQuitHovered = QuitButtonRef->CheckCollision(GetMousePosition(), TextureManagerRef->GetTexture(5).GetWidth());
    if (bIsQuitHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      bShouldShutdown = true;
      break;
    }

    StartButtonRef->Update();
    QuitButtonRef->Update();
    TitleRef->Update();
    break;

  case PlayingGame:
    //CHECK COLLISIONS
    for (int i = 0; i < 10; ++i)
    {
      if (EnemyRefs[i].GetIsAlive())
      {
        bEnemiesDead = false;
        PlayerRef->GetTurretRef()->BulletCollisionCheck(EnemyRefs[i]);
        EnemyRefs[i].GetTurretRef()->BulletCollisionCheck((*PlayerRef));
      }
    }

    if (bEnemiesDead)
    {
      CurrentState = EndMenu;
      break;
    }
    else if (!PlayerRef->GetIsAlive())
    {
      std::string setupText = std::string("You Lost!");
      WinTextRef->SetText(setupText);
      WinTextRef->SetNormalColor(Driscoll::DARKRED);
      WinTextRef->SetTextNormalColor(Driscoll::PINK);
      CurrentState = EndMenu;
    }

    //UPDATE PLAYER
    PlayerRef->Update();

    //UPDATE ENEMIES
    for (int i = 0; i < 10; ++i)
    {
      EnemyRefs[i].Update();
    }
    break;

  case EndMenu:
    //CHECK COLLISIONS
    bIsRestartHovered = RestartButtonRef->CheckCollision(GetMousePosition(), TextureManagerRef->GetTexture(5).GetWidth());
    if (bIsRestartHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      bShouldRestart = true;
      bShouldShutdown = true;
      break;
    }

    bIsQuitHovered = QuitButtonRef->CheckCollision(GetMousePosition(), TextureManagerRef->GetTexture(5).GetWidth());
    if (bIsQuitHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      bShouldShutdown = true;
      break;
    }

    RestartButtonRef->Update();
    QuitButtonRef->Update();
    TitleRef->Update();
    WinTextRef->Update();
    break;
  }
}

void GameMode::Draw()
{
  switch (CurrentState)
  {
  case MainMenu:
    StartButtonRef->Draw();
    QuitButtonRef->Draw();
    TitleRef->Draw();

    break;

  case PlayingGame:
    { //When Should Be Running Game

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
    }
    break;

  case EndMenu:
    RestartButtonRef->Draw();
    QuitButtonRef->Draw();
    TitleRef->Draw();
    WinTextRef->Draw();
    break;
  }

  //DRAW MOUSE
  raylib::Texture& MouseTexture = TextureManagerRef->GetTexture(5);
  MouseTexture.Draw(GetMousePosition().x - (MouseTexture.GetWidth() / 2), GetMousePosition().y - (MouseTexture.GetHeight() / 2));
}
