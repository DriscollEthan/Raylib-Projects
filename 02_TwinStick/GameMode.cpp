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
  TextureManagerRef = new TextureManager(21);

  /* Texture List: (TOTAL = 21)
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
   * 14 = Death Smoke 0
   * 15 = Death Smoke 1
   * 16 = Death Smoke 2
   * 17 = Death Smoke 3
   * 18 = Death Smoke 4
   * 19 = Death Smoke 5
   * 20 = Background Wrapper Indicationish
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

    //White Smoke 0
    ImageLoader.Load("Resources/Smoke/smokeWhite0.png");
    TextureManagerRef->SetTexture(ImageLoader, 14);

    //White Smoke 1
    ImageLoader.Load("Resources/Smoke/smokeWhite1.png");
    TextureManagerRef->SetTexture(ImageLoader, 15);

    //White Smoke 2
    ImageLoader.Load("Resources/Smoke/smokeWhite2.png");
    TextureManagerRef->SetTexture(ImageLoader, 16);

    //White Smoke 3
    ImageLoader.Load("Resources/Smoke/smokeWhite3.png");
    TextureManagerRef->SetTexture(ImageLoader, 17);

    //White Smoke 4
    ImageLoader.Load("Resources/Smoke/smokeWhite4.png");
    TextureManagerRef->SetTexture(ImageLoader, 18);

    //White Smoke 5
    ImageLoader.Load("Resources/Smoke/smokeWhite5.png");
    TextureManagerRef->SetTexture(ImageLoader, 19);

    //Laser
    ImageLoader.Load("Resources/Environment/Grass.png");
    TextureManagerRef->SetTexture(ImageLoader, 20);
  }

  /* Menu Object List:
   *  0. Start Game Button
   *  1. Quit Game Button
   *  2. Restart Game Button
   *  3. Title Text
   *  4. Win/Lose Text
   *  5. Tutorial Text
   *  6. Credits Text
   *  7. Pause Menu Background
   *  8. Pause Menu Resume Button
   *  9. Pause Menu Quit Button
   */

  MenuObjectRefs = new MenuObject[10];
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

    setupString = std::string("Controls: \n\nMovement: \n W: Move Up\n Up: Move Up\n\n A: Move Left\n Left: Move Left\n\n S: Move Down\n Down: Move Down\n\n D: Move Right\n Right: Move Right\n\n\nShooting:\n Left Click: Shoot\n Space Bar: Shoot\n\nAiming: \n The Turret Looks\n Towards the Mouse");
    setupText.SetFontSize(30);
    setupText.SetText(setupString);
    MenuObjectRefs[5] = MenuObject({ 330, 600 }, { 375, 775 }, Driscoll::Color(37, 150, 190, 255), Driscoll::Color(232, 106, 23, 255), Driscoll::BLACK, Driscoll::BLACK, setupText);
    MenuObjectRefs[5].SetTextureManagerRef(TextureManagerRef);
    MenuObjectRefs[5].SetTextureIndex(13);
    MenuObjectRefs[5].SetTextOrigin({ 0.55f, 0.53f });
    MenuObjectRefs[5].BeginPlay();
  }

  //Setup for PlayingGame State;
  {
    //SETUP TIMERS
    EndConditionWaitingTimer.SetTimerInSeconds(0.0f, 1.25f);
    HitStopTimer.SetTimerInSeconds(0.0f, 0.008f);
    StartingCountdownTimer.SetTimerInSeconds(0.0f, 4.0f);
    
    //SETUP PAUSE MENU
    std::string setupString = std::string("Paused");
    raylib::Text setupText; 
    setupText.SetFontSize(60);
    setupText.SetText(setupString);
    MenuObjectRefs[7] = MenuObject({ GlobalVariables.ScreenSize / 2.f }, { 350, 500 }, Driscoll::BLACK, Driscoll::BLACK, Driscoll::WHITE, Driscoll::YELLOW, setupText);
    MenuObjectRefs[7].SetTextureManagerRef(TextureManagerRef);
    MenuObjectRefs[7].SetTextureIndex(13);
    MenuObjectRefs[7].SetTextOrigin({ 0.5f, 3.75f });
    MenuObjectRefs[7].BeginPlay();
    MenuObjectRefs[7].SetTextSpacing(10.0f);

    setupString = std::string("Resume");
    setupText.SetFontSize(50);
    setupText.SetText(setupString);
    MenuObjectRefs[8] = MenuObject({ GlobalVariables.ScreenX / 2.f, (GlobalVariables.ScreenY / 2.f) - 75.f}, { 300, 150 }, Driscoll::WHITE, Driscoll::TEAL, Driscoll::BLACK, Driscoll::ORANGE, setupText);
    MenuObjectRefs[8].SetTextureManagerRef(TextureManagerRef);
    MenuObjectRefs[8].SetTextureIndex(13);
    MenuObjectRefs[8].SetTextOrigin({ 0.6f, 0.5f });
    MenuObjectRefs[8].BeginPlay();
    MenuObjectRefs[8].SetTextSpacing(10.0f);

    setupString = std::string("Quit");
    setupText.SetFontSize(50);
    setupText.SetText(setupString);
    MenuObjectRefs[9] = MenuObject({ GlobalVariables.ScreenX / 2.f, (GlobalVariables.ScreenY / 2.f) + 125.f }, { 300, 150 }, Driscoll::WHITE, Driscoll::TEAL, Driscoll::BLACK, Driscoll::ORANGE, setupText);
    MenuObjectRefs[9].SetTextureManagerRef(TextureManagerRef);
    MenuObjectRefs[9].SetTextureIndex(13);
    MenuObjectRefs[9].SetTextOrigin({ 0.6f, 0.5f });
    MenuObjectRefs[9].BeginPlay();
    MenuObjectRefs[9].SetTextSpacing(10.0f);

    //CREATE PLAYER
    PlayerRef = new Character(LocalData2D((GlobalVariables.ScreenSize / 2), 0, { 1, 1 }), 1, Driscoll::Vector2D(0.5f, 0.5f), HitboxData(50.0F), 5.0f, 2.F, 5.f);
    PlayerRef->SetTextureManagerRef(TextureManagerRef);
    PlayerRef->SetLocalPosition(GlobalVariables.ScreenSize - 100);
    PlayerRef->BeginPlay();

    //CREATE ENEMIES
    EnemyRefs = new Enemy[10];
    for (int i = 0; i < 10; ++i)
    {
      EnemyRefs[i] = { LocalData2D((GlobalVariables.ScreenSize / 2), 4, {1, 1}), 2, Driscoll::Vector2D(0.5f, 0.5f), HitboxData(60.0f), 3.5f, 3.5f, 3.0f };
      EnemyRefs[i].SetPlayerRef(PlayerRef);
      EnemyRefs[i].SetLocalPosition(Driscoll::Vector2D(0.f, 0.f) + 100);
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
  bool bIsPauseResumeHovered = false;
  bool bIsPauseQuitHovered = false;

  switch (CurrentState)
  {
  case MainMenu:
    //CHECK COLLISIONS
    MenuObjectRefs[5].CheckCollision(GetMousePosition(), TextureManagerRef->GetTexture(5).GetWidth() / 2.0f);
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
    if (!StartingCountdownTimer.RunTimer(GetFrameTime()))
    {
      break;
    }

    if (PlayerRef->GetShouldPause())
    {
      PlayerRef->CheckPauseInput();

      MenuObjectRefs[7].CheckCollision(GetMousePosition(), TextureManagerRef->GetTexture(5).GetWidth() / 2.0f);
      bIsPauseResumeHovered = MenuObjectRefs[8].CheckCollision(GetMousePosition(), TextureManagerRef->GetTexture(5).GetWidth() / 2.0f);
      if (bIsPauseResumeHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      {
        PlayerRef->SetShouldBePaused(false);
        break;
      }

      bIsPauseQuitHovered = MenuObjectRefs[9].CheckCollision(GetMousePosition(), TextureManagerRef->GetTexture(5).GetWidth() / 2.0f);
      if (bIsPauseQuitHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      {
        bShouldShutdown = true;
        break;
      }

      MenuObjectRefs[7].Update();
      MenuObjectRefs[8].Update();
      MenuObjectRefs[9].Update();

      break;
    }

    if (PlayerRef->bIsHit() && !HitStopTimer.RunTimer(GetFrameTime()))
    {
      break;
    }
    else
    {
      HitStopTimer.ResetTimer();

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
        if (EndConditionWaitingTimer.RunTimer(GetFrameTime()))
        {
          CurrentState = EndMenu;
          break;
        }
      }
      else if (!PlayerRef->GetIsAlive())
      {
        if (EndConditionWaitingTimer.RunTimer(GetFrameTime()))
        {
          std::string setupText = std::string("You Lost!");
          MenuObjectRefs[4].SetText(setupText);
          MenuObjectRefs[4].SetNormalColor(Driscoll::DARKRED);
          MenuObjectRefs[4].SetTextNormalColor(Driscoll::PINK);
          CurrentState = EndMenu;
        }
      }

      //UPDATE PLAYER
      PlayerRef->Update();

      //UPDATE ENEMIES
      for (int i = 0; i < 10; ++i)
      {
        EnemyRefs[i].Update();
      }
      break;
    }

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
      int NextEnvironmentPosiiton = GlobalVariables.ScreenX / 128.f;
      int HowManyImagesPerColumn = GlobalVariables.ScreenY / 128.f;
      raylib::Texture& backgroundTexture = TextureManagerRef->GetTexture(6);
      Driscoll::Color DrawColor;

      int i = 0;

      for (int j = 0; j < NextEnvironmentPosiiton; ++j)
      {
        for (int k = 0; k < HowManyImagesPerColumn; ++k)
        {
          if (PlayerRef->bIsHit() && !HitStopTimer.RunTimer(0))
          {
            DrawColor = (j == 0 || j == NextEnvironmentPosiiton - 1 || k == 0 || k == HowManyImagesPerColumn - 1)
              ? Driscoll::BLACK : DrawColor = Driscoll::DARKGREY;
          }
          else
          {
            DrawColor = (j == 0 || j == NextEnvironmentPosiiton - 1 || k == 0 || k == HowManyImagesPerColumn - 1)
              ? Driscoll::Color(185, 133, 85, 255) : DrawColor = Driscoll::Color(233, 160, 99, 255);
          }

          //Color Options
          // 1: 185, 133, 85
          // 2: 233, 160, 99
          backgroundTexture.Draw(j * 128, k * 128, DrawColor);
        }
      }

      //DRAW ENEMIES
      for (int i = 0; i < 10; ++i)
      {
        EnemyRefs[i].Draw();
      }

      //DRAW PLAYER
      PlayerRef->Draw();

      //DRAW COUNTDOWN TILL SHOOTING
      if (!StartingCountdownTimer.RunTimer(0.0f))
      {
        int drawNumber = 4 - StartingCountdownTimer.GetCurrentTimeInSeconds();

        raylib::Text drawText = raylib::Text();
        std::string drawString;
        if (drawNumber < 1)
        {
          drawString = "GO!";
          drawText.SetText(drawString);
        }
        else
        {
          drawText.SetText(TextFormat("% 01i", drawNumber));
        }
        drawText.SetFontSize(300);
        drawText.SetSpacing(10.0f);
        drawText.SetColor(Driscoll::YELLOW);

        drawText.Draw((GlobalVariables.ScreenSize / 2) - Driscoll::Vector2D(drawText.Measure() * 0.5f, drawText.GetFontSize() * 0.5f));
      }

      //Paused??
      if (PlayerRef->GetShouldPause())
      {
        MenuObjectRefs[7].Draw();
        MenuObjectRefs[8].Draw();
        MenuObjectRefs[9].Draw();
      }
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
