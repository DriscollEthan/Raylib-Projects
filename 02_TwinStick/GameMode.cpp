#include "GameMode.h"

#include <string.h>


GameMode::GameMode()
{
  PlayerRef = nullptr;
  EnemyRefs = nullptr;
  MenuObjectRefs = nullptr;
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
  if (MenuObjectRefs)
  {
    delete[] MenuObjectRefs;
  }
}

void GameMode::BeginPlay()
{
  //CREATE TEXTURE MANAGER
  TextureManagerRef = new TextureManager(26);

  /* Texture List: (TOTAL = 26)
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
   * 13 = Button Image Background
   * 14 = Player Smoke 0
   * 15 = Player Smoke 1
   * 16 = Player Smoke 2
   * 17 = Player Smoke 3
   * 18 = Player Smoke 4
   * 19 = Player Smoke 5
   * 20 = Enemy Smoke 0
   * 21 = Enemy Smoke 1
   * 22 = Enemy Smoke 2
   * 23 = Enemy Smoke 3
   * 24 = Enemy Smoke 4
   * 25 = Enemy Smoke 5
   */

  //SET TEXTURES
  {
    CurrentState = MainMenu;

    raylib::Image ImageLoader; 
    
    //Default
    ImageLoader.Load("Resources/Default.png");
    TextureManagerRef->SetTexture(ImageLoader, 0);

    //Player Tank
    ImageLoader.Load("Resources/Tanks/tankBlue_outline.png");
    TextureManagerRef->SetTexture(ImageLoader, 1);

    //Enemy Tank
    ImageLoader.Load("Resources/Tanks/tankRed_outline.png");
    TextureManagerRef->SetTexture(ImageLoader, 2);

    //Player Bullet
    ImageLoader.Load("Resources/Bullets/bulletBlueSilver_outline.png");
    TextureManagerRef->SetTexture(ImageLoader, 3);

    //Enemy Bullet
    ImageLoader.Load("Resources/Bullets/bulletRedSilver_outline.png");
    TextureManagerRef->SetTexture(ImageLoader, 4);

    //Mouse Cursor
    ImageLoader.Load("Resources/target_round_b.png");
    TextureManagerRef->SetTexture(ImageLoader, 5);

    //Background
    ImageLoader.Load("Resources/Environment/dirt.png");
    TextureManagerRef->SetTexture(ImageLoader, 6);

    //Tire Tracks
    ImageLoader.Load("Resources/Tanks/tracksLarge.png");
    TextureManagerRef->SetTexture(ImageLoader, 7);

    //Max Health Turret
    ImageLoader.Load("Resources/Tanks/barrelWhite_outline-0Hit.png");
    TextureManagerRef->SetTexture(ImageLoader, 8);

    //3/4 Health Turret
    ImageLoader.Load("Resources/Tanks/barrelWhite_outline-1Hit.png");
    TextureManagerRef->SetTexture(ImageLoader, 9);

    //1/2 Health Turret
    ImageLoader.Load("Resources/Tanks/barrelWhite_outline-2Hit.png");
    TextureManagerRef->SetTexture(ImageLoader, 10);

    //1/4 Health Turret
    ImageLoader.Load("Resources/Tanks/barrelWhite_outline-3Hit.png");
    TextureManagerRef->SetTexture(ImageLoader, 11);

    //0 Health Turret
    ImageLoader.Load("Resources/Tanks/barrelWhite_outline-4Hit.png");
    TextureManagerRef->SetTexture(ImageLoader, 12);

    //Button Image Background
    ImageLoader.Load("Resources/ButtonImage.png");
    TextureManagerRef->SetTexture(ImageLoader, 13);

    //Player Smoke 0
    ImageLoader.Load("Resources/Smoke/smokeGrey0.png");
    TextureManagerRef->SetTexture(ImageLoader, 14);

    //Player Smoke 1
    ImageLoader.Load("Resources/Smoke/smokeGrey1.png");
    TextureManagerRef->SetTexture(ImageLoader, 15);

    //Player Smoke 2
    ImageLoader.Load("Resources/Smoke/smokeGrey2.png");
    TextureManagerRef->SetTexture(ImageLoader, 16);

    //Player Smoke 3
    ImageLoader.Load("Resources/Smoke/smokeGrey3.png");
    TextureManagerRef->SetTexture(ImageLoader, 17);

    //Player Smoke 4
    ImageLoader.Load("Resources/Smoke/smokeGrey4.png");
    TextureManagerRef->SetTexture(ImageLoader, 18);

    //Player Smoke 5
    ImageLoader.Load("Resources/Smoke/smokeGrey5.png");
    TextureManagerRef->SetTexture(ImageLoader, 19);

    //Enemy Smoke 0
    ImageLoader.Load("Resources/Smoke/smokeOrange0.png");
    TextureManagerRef->SetTexture(ImageLoader, 20);

    //Enemy Smoke 1
    ImageLoader.Load("Resources/Smoke/smokeOrange1.png");
    TextureManagerRef->SetTexture(ImageLoader, 21);

    //Enemy Smoke 2
    ImageLoader.Load("Resources/Smoke/smokeOrange2.png");
    TextureManagerRef->SetTexture(ImageLoader, 22);

    //Enemy Smoke 3
    ImageLoader.Load("Resources/Smoke/smokeOrange3.png");
    TextureManagerRef->SetTexture(ImageLoader, 23);

    //Enemy Smoke 4
    ImageLoader.Load("Resources/Smoke/smokeOrange4.png");
    TextureManagerRef->SetTexture(ImageLoader, 24);

    //Enemy Smoke 5
    ImageLoader.Load("Resources/Smoke/smokeOrange5.png");
    TextureManagerRef->SetTexture(ImageLoader, 25);
  }

  /* Menu Object List:
   *  0. Start Game Button
   *  1. Quit Game Button
   *  2. Restart Game Button
   *  3. Title Text
   *  4. Win/Lose Text
   *  5. Tutorial Text
   *  6. Credits Text
   */

  MenuObjectRefs = new MenuObject[7];
  //Setup for MainMenu State;
  {
    raylib::Text setupText = raylib::Text();
    std::string setupString = std::string("Start Game");
    setupText.SetText(setupString);
    setupText.SetFontSize(50);
    setupText.SetSpacing(5.0f);

    MenuObjectRefs[0] = MenuObject({GlobalVariables.ScreenX / 2.f, 400}, {400, 200}, Driscoll::BLACK, Driscoll::TEAL, Driscoll::CYAN, Driscoll::ORANGE, setupText);
    MenuObjectRefs[0].SetTextureManagerRef(TextureManagerRef);
    MenuObjectRefs[0].SetTextureIndex(13);
    MenuObjectRefs[0].BeginPlay();

    setupString = std::string("Quit Game");
    setupText.SetText(setupString);
    MenuObjectRefs[1] = MenuObject({ GlobalVariables.ScreenX / 2.f, 800 }, { 400, 200 }, Driscoll::BLACK, Driscoll::TEAL, Driscoll::CYAN, Driscoll::ORANGE, setupText);
    MenuObjectRefs[1].SetTextureManagerRef(TextureManagerRef);
    MenuObjectRefs[1].SetTextureIndex(13);
    MenuObjectRefs[1].BeginPlay();

    setupString = std::string("Tanky Game");
    setupText.SetFontSize(75);
    setupText.SetText(setupString);
    MenuObjectRefs[3] = MenuObject({ GlobalVariables.ScreenX / 2.f, 40 }, { 450, 80 }, Driscoll::TEAL, Driscoll::TEAL, Driscoll::WHITE, Driscoll::WHITE, setupText);
    MenuObjectRefs[3].SetTextureManagerRef(TextureManagerRef);
    MenuObjectRefs[3].SetTextureIndex(13);
    MenuObjectRefs[3].BeginPlay();

    setupString = std::string("Controls: \n\nMovement: \n W: Move Up\n Up: Move Up\n\n A: Move Left\n Left: Move Left\n\n S: Move Down\n Down: Move Down\n\n D: Move Right\n Right: Move Right\n\n\nShooting:\n Left Click: Shoot\n\n Space Bar: Shoot\n\nAiming: \n The Turret Looks\n Towards the Mouse");
    setupText.SetFontSize(30);
    setupText.SetText(setupString);
    MenuObjectRefs[5] = MenuObject({ 330, 600 }, { 375, 825 }, Driscoll::Color(37, 150, 190, 255), Driscoll::Color(232, 106, 23, 255), Driscoll::BLACK, Driscoll::BLACK, setupText);
    MenuObjectRefs[5].SetTextureManagerRef(TextureManagerRef);
    MenuObjectRefs[5].SetTextureIndex(13);
    MenuObjectRefs[5].SetTextOrigin({ 0.55f, 0.53f });
    MenuObjectRefs[5].BeginPlay();
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
      EnemyRefs[i].SetTimer(3.0f, 1.0f);
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

    MenuObjectRefs[2] = MenuObject({ GlobalVariables.ScreenX / 2.f, 400 }, { 400, 200 }, Driscoll::BLACK, Driscoll::TEAL, Driscoll::CYAN, Driscoll::ORANGE, setupText);
    MenuObjectRefs[2].SetTextureManagerRef(TextureManagerRef);
    MenuObjectRefs[2].SetTextureIndex(13);
    MenuObjectRefs[2].BeginPlay();

    setupString = std::string("You Win!");
    setupText.SetText(setupString);
    setupText.SetFontSize(50);
    MenuObjectRefs[4] = MenuObject({ GlobalVariables.ScreenX / 2.f, 160 }, { 300, 80 }, Driscoll::GREEN, Driscoll::CLEAR, Driscoll::BLUE, Driscoll::CLEAR, setupText);
    MenuObjectRefs[4].SetTextureManagerRef(TextureManagerRef);
    MenuObjectRefs[4].SetTextureIndex(13);
    MenuObjectRefs[4].BeginPlay();
  }
}

void GameMode::Update()
{
  bool bIsStartHovered = false;
  bool bIsQuitHovered = false;
  bool bIsRestartHovered = false;
  bool bIsTitleHovered = false;

  bool bEnemiesDead = true;


  switch (CurrentState)
  {
  case MainMenu:
    //CHECK COLLISIONS
    MenuObjectRefs[5].CheckCollision(GetMousePosition(), TextureManagerRef->GetTexture(5).GetWidth());
    bIsStartHovered = MenuObjectRefs[0].CheckCollision(GetMousePosition(), TextureManagerRef->GetTexture(5).GetWidth() / 2.0f);
    if (bIsStartHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      CurrentState = PlayingGame;
      break;
    }

    bIsQuitHovered = MenuObjectRefs[1].CheckCollision(GetMousePosition(), TextureManagerRef->GetTexture(5).GetWidth() / 2.0f);
    if (bIsQuitHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      bShouldShutdown = true;
      break;
    }
    bIsTitleHovered = MenuObjectRefs[3].CheckCollision(GetMousePosition(), TextureManagerRef->GetTexture(5).GetWidth() / 2.0f);
    if (bIsTitleHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      raylib::Image newTankImage;
      switch (++CyclePlayerTank)
      {
      case 0:
      newTankImage.Load("Resources/Tanks/tankBlue_outline.png");
      TextureManagerRef->SetTexture(newTankImage, 1);
      newTankImage.Load("Resources/Bullets/bulletBlueSilver_outline.png");
      TextureManagerRef->SetTexture(newTankImage, 3);
      break;
      case 1:
        newTankImage.Load("Resources/Tanks/tankGreen_outline.png");
        TextureManagerRef->SetTexture(newTankImage, 1);
        newTankImage.Load("Resources/Bullets/bulletGreenSilver_outline.png");
        TextureManagerRef->SetTexture(newTankImage, 3);
        break;
      case 2:
        newTankImage.Load("Resources/Tanks/tankRed_outline.png");
        TextureManagerRef->SetTexture(newTankImage, 1);
        newTankImage.Load("Resources/Bullets/bulletRedSilver_outline.png");
        TextureManagerRef->SetTexture(newTankImage, 3);
        break;
      case 3:
        newTankImage.Load("Resources/Tanks/tankBlack_outline.png");
        TextureManagerRef->SetTexture(newTankImage, 1);
        newTankImage.Load("Resources/Bullets/bulletSilverSilver_outline.png");
        TextureManagerRef->SetTexture(newTankImage, 3);
        break;
      case 4:
        newTankImage.Load("Resources/Tanks/tankBeige_outline.png");
        TextureManagerRef->SetTexture(newTankImage, 1);
        newTankImage.Load("Resources/Bullets/bulletBeigeSilver_outline.png");
        TextureManagerRef->SetTexture(newTankImage, 3);
        CyclePlayerTank = -1;
        break;
      }
    }

    MenuObjectRefs[0].Update();
    MenuObjectRefs[1].Update();
    MenuObjectRefs[3].Update();
    MenuObjectRefs[5].Update();
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
      MenuObjectRefs[4].SetText(setupText);
      MenuObjectRefs[4].SetNormalColor(Driscoll::DARKRED);
      MenuObjectRefs[4].SetTextNormalColor(Driscoll::PINK);
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
    bIsRestartHovered = MenuObjectRefs[2].CheckCollision(GetMousePosition(), TextureManagerRef->GetTexture(5).GetWidth() / 2.0f);
    if (bIsRestartHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      bShouldRestart = true;
      bShouldShutdown = true;
      break;
    }

    bIsQuitHovered = MenuObjectRefs[1].CheckCollision(GetMousePosition(), TextureManagerRef->GetTexture(5).GetWidth() / 2.0f);
    if (bIsQuitHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      bShouldShutdown = true;
      break;
    }

    MenuObjectRefs[2].Update();
    MenuObjectRefs[1].Update();
    MenuObjectRefs[3].Update();
    MenuObjectRefs[4].Update();
    break;
  }
}

void GameMode::Draw()
{
  switch (CurrentState)
  {
  case MainMenu:
    MenuObjectRefs[0].Draw();
    MenuObjectRefs[1].Draw();
    MenuObjectRefs[3].Draw();
    MenuObjectRefs[5].Draw();

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
    MenuObjectRefs[2].Draw();
    MenuObjectRefs[1].Draw();
    MenuObjectRefs[3].Draw();
    MenuObjectRefs[4].Draw();
    break;
  }

  //DRAW MOUSE
  raylib::Texture& MouseTexture = TextureManagerRef->GetTexture(5);
  MouseTexture.Draw(GetMousePosition().x - (MouseTexture.GetWidth() / 2), GetMousePosition().y - (MouseTexture.GetHeight() / 2));
}
