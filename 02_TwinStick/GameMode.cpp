#include "GameMode.h"

#include <string.h>   //Use of Creating Text for Menu Objects
#include <fstream>    //Use of tracking HighScore for Rounds

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
  TextureManagerRef = new TextureManager(20);

  std::fstream HighScoreFile;
  HighScoreFile.open("Resources/HighScores.txt", std::ios::in);
  if (HighScoreFile.is_open())
  {
    HighScoreFile >> RoundHighScore;
  }
  HighScoreFile.close();

  /* Texture List: (TOTAL = 20)
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
   */

  //SET TEXTURES
  {
    Rounds = 0;
    PlayingTime.SetTimerInSeconds(0.0f, 0.0f);
    CurrentAmountOfEnemies = 5;

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
   *  10. Lore Text
   *  11. Round Counter
   *  12. Next Round
   *  13. Round HighScore
   *  14. Quit
   *  15. In Game Round Counter
   */
  bShowPlayerLastHit = false;

  MenuObjectRefs = new MenuObject[16];
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

    setupString = std::string("You are the Blue Tank Warrior \nKill the Orange Tank Bad Guys\n Good luck my fellow Blue Tanker!");
    setupText.SetFontSize(30);
    setupText.SetText(setupString);
    MenuObjectRefs[10] = MenuObject({ 1590, 600 }, { 650, 300 }, Driscoll::Color(232, 106, 23, 255), Driscoll::Color(37, 150, 190, 255), Driscoll::BLACK, Driscoll::BLACK, setupText);
    MenuObjectRefs[10].SetTextureManagerRef(TextureManagerRef);
    MenuObjectRefs[10].SetTextureIndex(13);
    MenuObjectRefs[10].SetTextOrigin({ 0.55f, 0.53f });
    MenuObjectRefs[10].BeginPlay();

    //13 = High Score
    setupText.SetFontSize(30);
    setupText.SetText(TextFormat("Rounds HighScore \nCompleted: %03i", RoundHighScore));
    MenuObjectRefs[13] = MenuObject({ GlobalVariables.ScreenX - 225.f, 75 }, { 350, 150 }, Driscoll::BLUE, Driscoll::TEAL, Driscoll::WHITE, Driscoll::BLACK, setupText);
    MenuObjectRefs[13].SetTextureManagerRef(TextureManagerRef);
    MenuObjectRefs[13].SetTextureIndex(13);
    MenuObjectRefs[13].BeginPlay();
  }

  //Setup for PlayingGame State;
  {
    //SETUP TIMERS
    EndConditionWaitingTimer.SetTimerInSeconds(0.0f, 1.25f);
    HitStopTimer.SetTimerInSeconds(0.0f, 0.007f);
    StartingCountdownTimer.SetTimerInSeconds(0.0f, 4.0f);
    PlayerLastHitFlashTimer.SetTimerInSeconds(0.0f, 0.25f);
    
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

    //15 = In Game Round Counter
    setupText.SetText(TextFormat("Rounds Completed: %03i", Rounds));
    setupText.SetFontSize(30);
    setupText.SetSpacing(5.0f);
    MenuObjectRefs[15] = MenuObject({ GlobalVariables.ScreenX - 225.f, 50  }, { 200, 155 }, Driscoll::CLEAR, Driscoll::CLEAR, Driscoll::WHITE, Driscoll::WHITE, setupText);
    MenuObjectRefs[15].SetTextureManagerRef(TextureManagerRef);
    MenuObjectRefs[15].SetTextureIndex(13);
    MenuObjectRefs[15].BeginPlay();

    //CREATE PLAYER
    PlayerRef = new Character(LocalData2D({128, 128}, 45, {1, 1}), 1, Driscoll::Vector2D(0.5f, 0.5f), HitboxData(50.0F), 5.0f, 2.F, 5.f);
    PlayerRef->SetTextureManagerRef(TextureManagerRef);
    PlayerRef->BeginPlay();

    //CREATE ENEMIES
    TOTAL_ENEMY_COUNT = 15;
    EnemyRefs = new Enemy[TOTAL_ENEMY_COUNT];
    for (int i = 0; i < TOTAL_ENEMY_COUNT; ++i)
    {
      EnemyRefs[i] = { LocalData2D((GlobalVariables.ScreenSize - 128.0f), 180, {1, 1}), 2, Driscoll::Vector2D(0.5f, 0.5f), HitboxData(60.0f), 1.f, 3.5f, 1.f };
      EnemyRefs[i].SetPlayerRef(PlayerRef);
      EnemyRefs[i].SetTimer(3.0f, 1.0f);
      EnemyRefs[i].SetTextureManagerRef(TextureManagerRef);
      EnemyRefs[i].BeginPlay();
    }
  }

  //Setup for InBetweenRounds State; 
  {
     //11 = Round Counter
    raylib::Text setupText;
    std::string setupString;
    setupText.SetText(TextFormat("Rounds Completed: %03i", Rounds));
    setupText.SetFontSize(50);
    setupText.SetSpacing(5.0f);
    MenuObjectRefs[11] = MenuObject({ GlobalVariables.ScreenX / 2.f, 200 }, { 650, 155 }, Driscoll::DARKBLUE, Driscoll::GREEN, Driscoll::BLUE, Driscoll::BLUE, setupText);
    MenuObjectRefs[11].SetTextureManagerRef(TextureManagerRef);
    MenuObjectRefs[11].SetTextureIndex(13);
    MenuObjectRefs[11].SetTextNormalColor(Driscoll::BLUE);
    MenuObjectRefs[11].BeginPlay();

    //12 = Next Round
    setupString = std::string("Next Round");
    setupText.SetFontSize(50);
    setupText.SetText(setupString);
    MenuObjectRefs[12] = MenuObject({ GlobalVariables.ScreenX / 2.f, 500}, { 400, 150 }, Driscoll::BLACK, Driscoll::TEAL, Driscoll::CYAN, Driscoll::ORANGE, setupText);
    MenuObjectRefs[12].SetTextureManagerRef(TextureManagerRef);
    MenuObjectRefs[12].SetTextureIndex(13);
    MenuObjectRefs[12].BeginPlay();

    //14 = Quit
    setupString = std::string("Quit");
    setupText.SetFontSize(50);
    setupText.SetText(setupString);
    MenuObjectRefs[14] = MenuObject({ GlobalVariables.ScreenX / 2.f, 900 }, { 400, 150 }, Driscoll::BLACK, Driscoll::TEAL, Driscoll::CYAN, Driscoll::ORANGE, setupText);
    MenuObjectRefs[14].SetTextureManagerRef(TextureManagerRef);
    MenuObjectRefs[14].SetTextureIndex(13);
    MenuObjectRefs[14].BeginPlay();

  }

  //Setup for EndLevelMenu State;
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

    setupString = std::string("             Well done! \nThe Blue Tankers win the War!");
    setupText.SetText(setupString);
    setupText.SetFontSize(50);
    MenuObjectRefs[4] = MenuObject({ GlobalVariables.ScreenX / 2.f, 200 }, { 900, 155 }, Driscoll::GREEN, Driscoll::CLEAR, Driscoll::BLUE, Driscoll::CLEAR, setupText);
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
  bool bIsNextRoundHovered = false;

  bool bEnemiesDead = true;
  bool bIsPauseResumeHovered = false;
  bool bIsPauseQuitHovered = false;

  raylib::Text setupText;

  switch (CurrentState)
  {
  case MainMenu:
    //CHECK COLLISIONS
    MenuObjectRefs[13].CheckCollision(GetMousePosition(), TextureManagerRef->GetTexture(5).GetWidth() / 2.0f);
    MenuObjectRefs[5].CheckCollision(GetMousePosition(), TextureManagerRef->GetTexture(5).GetWidth() / 2.0f);
    MenuObjectRefs[10].CheckCollision(GetMousePosition(), TextureManagerRef->GetTexture(5).GetWidth() / 2.0f);
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
      std::string setupText;
      switch (++CyclePlayerTank)
      {
      case 0:
        newTankImage.Load("Resources/Tanks/tankBlue_outline.png");
        TextureManagerRef->SetTexture(newTankImage, 1);
        newTankImage.Load("Resources/Bullets/bulletBlueSilver_outline.png");
        TextureManagerRef->SetTexture(newTankImage, 3);
        setupText = std::string("You are the Blue Tank Warrier \nKill the Orange Tank Bad Guys\n Good luck my fellow Blue Tanker!");
        MenuObjectRefs[10].SetText(setupText);
        setupText = std::string("             Well done! \nThe Blue Tankers win the War!");
        MenuObjectRefs[4].SetText(setupText);
        break;
      case 1:
        newTankImage.Load("Resources/Tanks/tankGreen_outline.png");
        TextureManagerRef->SetTexture(newTankImage, 1);
        newTankImage.Load("Resources/Bullets/bulletGreenSilver_outline.png");
        TextureManagerRef->SetTexture(newTankImage, 3);
        setupText = std::string("You are the Green Tank Warrier \nKill the Orange Tank Bad Guys\n Good luck my fellow Green Tanker!");
        MenuObjectRefs[10].SetText(setupText);
        setupText = std::string("             Well done! \nThe Green Tankers win the War!");
        MenuObjectRefs[4].SetText(setupText);
        break;
      case 2:
        newTankImage.Load("Resources/Tanks/tankRed_outline.png");
        TextureManagerRef->SetTexture(newTankImage, 1);
        newTankImage.Load("Resources/Bullets/bulletRedSilver_outline.png");
        TextureManagerRef->SetTexture(newTankImage, 3);
        setupText = std::string("You are the Orange Tank Warrier \nKill the Orange Tank Bad Guys\n Good luck my fellow Orange Tanker!");
        MenuObjectRefs[10].SetText(setupText);
        setupText = std::string("             Well done! \nThe Orange Tankers win the War!");
        MenuObjectRefs[4].SetText(setupText);
        break;
      case 3:
        newTankImage.Load("Resources/Tanks/tankBlack_outline.png");
        TextureManagerRef->SetTexture(newTankImage, 1);
        newTankImage.Load("Resources/Bullets/bulletSilverSilver_outline.png");
        TextureManagerRef->SetTexture(newTankImage, 3);
        setupText = std::string("You are the Black Tank Warrier \nKill the Orange Tank Bad Guys\n Good luck my fellow Black Tanker!");
        MenuObjectRefs[10].SetText(setupText);
        setupText = std::string("             Well done! \nThe Black Tankers win the War!");
        MenuObjectRefs[4].SetText(setupText);
        break;
      case 4:
        newTankImage.Load("Resources/Tanks/tankBeige_outline.png");
        TextureManagerRef->SetTexture(newTankImage, 1);
        newTankImage.Load("Resources/Bullets/bulletBeigeSilver_outline.png");
        TextureManagerRef->SetTexture(newTankImage, 3);
        setupText = std::string("You are the Beige Tank Warrier \nKill the Orange Tank Bad Guys\n Good luck my fellow Beige Tanker!");
        MenuObjectRefs[10].SetText(setupText);
        setupText = std::string("             Well done! \nThe Beige Tankers win the War!");
        MenuObjectRefs[4].SetText(setupText);
        CyclePlayerTank = -1;
        break;
      }
    }

    MenuObjectRefs[0].Update();
    MenuObjectRefs[1].Update();
    MenuObjectRefs[3].Update();
    MenuObjectRefs[5].Update();
    MenuObjectRefs[10].Update();
    MenuObjectRefs[13].Update();
    break;

  case PlayingGame:
    if (!StartingCountdownTimer.RunTimer(GetFrameTime()))
    {
      break;
    }

    setupText.SetText(TextFormat("Rounds Completed: %03i", Rounds));
    MenuObjectRefs[15].SetText(setupText);
    MenuObjectRefs[15].Update();

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
        if (RoundHighScore < Rounds)
        {
          std::fstream HighScoreFile;
          HighScoreFile.open("Resources/HighScores.txt", std::ios::out);
          if (HighScoreFile.is_open())
          {
            RoundHighScore = Rounds;
            HighScoreFile << RoundHighScore;

            raylib::Text newHighscoreText;
            newHighscoreText.SetText(TextFormat("Rounds HighScore \nCompleted: %03i", RoundHighScore));
            MenuObjectRefs[13].SetText(newHighscoreText);
          }
          HighScoreFile.flush();
          HighScoreFile.close();
        }
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
      for (int i = 0; i < CurrentAmountOfEnemies; ++i)
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
          Rounds++;
          CurrentState = InbetweenRounds;
          break;
        }
      }
      else if (!PlayerRef->GetIsAlive())
      {
        if (EndConditionWaitingTimer.RunTimer(GetFrameTime()))
        {
          if (Rounds < 1)
          {
            std::string setupText = std::string("             How dare you! \nThe Orange Tankers Win the War!");
            MenuObjectRefs[4].SetText(setupText);
            MenuObjectRefs[4].SetNormalColor(Driscoll::DARKRED);
            MenuObjectRefs[4].SetTextNormalColor(Driscoll::PINK);
          }

          if (RoundHighScore < Rounds)
          {
            std::fstream HighScoreFile;
            HighScoreFile.open("Resources/HighScores.txt", std::ios::out);
            if (HighScoreFile.is_open())
            {
              RoundHighScore = Rounds;
              HighScoreFile << RoundHighScore;

              raylib::Text newHighscoreText;
              newHighscoreText.SetText(TextFormat("Rounds HighScore \nCompleted: %03i", RoundHighScore));
              MenuObjectRefs[13].SetText(newHighscoreText);
            }
            HighScoreFile.flush();
            HighScoreFile.close();
        }
          CurrentState = EndMenu;
        }
      }

      if (PlayerRef->GetLastHit() && PlayerLastHitFlashTimer.RunTimer(GetFrameTime()))
      {
        bShowPlayerLastHit = !bShowPlayerLastHit;
        PlayerLastHitFlashTimer.ResetTimer();
      }

      //UPDATE PLAYER
      PlayerRef->Update();

      //UPDATE ENEMIES
      for (int i = 0; i < CurrentAmountOfEnemies; ++i)
      {
        EnemyRefs[i].Update();
      }
      break;
    }

  case InbetweenRounds:
  {
    //CHECK COLLISIONS
    raylib::Text setupText; setupText.SetText(TextFormat("Rounds Completed: %03i", Rounds));

    MenuObjectRefs[11].SetText(setupText);
    MenuObjectRefs[13].CheckCollision(GetMousePosition(), TextureManagerRef->GetTexture(5).GetWidth() / 2.0f);
    bIsNextRoundHovered = MenuObjectRefs[12].CheckCollision(GetMousePosition(), TextureManagerRef->GetTexture(5).GetWidth() / 2.0f);
    bIsQuitHovered = MenuObjectRefs[14].CheckCollision(GetMousePosition(), TextureManagerRef->GetTexture(5).GetWidth() / 2.0f);
    MenuObjectRefs[5].CheckCollision(GetMousePosition(), TextureManagerRef->GetTexture(5).GetWidth() / 2.0f);
    MenuObjectRefs[10].CheckCollision(GetMousePosition(), TextureManagerRef->GetTexture(5).GetWidth() / 2.0f);
    if (bIsNextRoundHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      if (CurrentAmountOfEnemies < TOTAL_ENEMY_COUNT)
      {
        CurrentAmountOfEnemies += 2;
      }
      //SETUP TIMERS
      EndConditionWaitingTimer.SetTimerInSeconds(0.0f, 1.25f);
      HitStopTimer.SetTimerInSeconds(0.0f, 0.008f);
      StartingCountdownTimer.SetTimerInSeconds(0.0f, 4.0f);
      PlayerLastHitFlashTimer.SetTimerInSeconds(0.0f, 0.25f);

      PlayerRef->SetLocalPosition({ 128, 128 });
      PlayerRef->SetLocalRotation(45.0f);

      for (int i = 0; i < TOTAL_ENEMY_COUNT; ++i)
      {
        EnemyRefs[i].SetLocalPosition(GlobalVariables.ScreenSize - 128.0f);
        EnemyRefs[i].SetLocalRotation(180.0f);
        EnemyRefs[i].IncreaseDifficulty(Rounds);
        EnemyRefs[i].GetTurretRef()->DisableAllBullets();

        EnemyRefs[i].Update();
        EnemyRefs[i].GetTurretRef()->DisableAllBullets();
      }

      PlayerRef->IncreaseDifficulty(Rounds);
      PlayerRef->GetTurretRef()->DisableAllBullets();
      PlayerRef->Update();
      PlayerRef->GetTurretRef()->DisableAllBullets();

      bShowPlayerLastHit = false;

      CurrentState = PlayingGame;
      break;
    }
    if (bIsQuitHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      bShouldShutdown = true;
      break;
    }
    MenuObjectRefs[3].Update();
    MenuObjectRefs[5].Update();
    MenuObjectRefs[10].Update();
    MenuObjectRefs[12].Update();
    MenuObjectRefs[13].Update();
    MenuObjectRefs[14].Update();
    break;
  }
  case EndMenu:
    //CHECK COLLISIONS
    MenuObjectRefs[13].CheckCollision(GetMousePosition(), TextureManagerRef->GetTexture(5).GetWidth() / 2.0f);
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
    MenuObjectRefs[13].Update();
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
    MenuObjectRefs[10].Draw();
    MenuObjectRefs[13].Draw();

    break;

  case PlayingGame:
    { //When Should Be Running Game

      //Draw Background
      int NextEnvironmentPosiiton = GlobalVariables.ScreenX / 128.f;
      int HowManyImagesPerColumn = GlobalVariables.ScreenY / 128.f;
      raylib::Texture& backgroundTexture = TextureManagerRef->GetTexture(6);
      Driscoll::Color DrawColor;

      for (int j = 0; j < NextEnvironmentPosiiton; ++j)
      {
        for (int k = 0; k < HowManyImagesPerColumn; ++k)
        {
          if (PlayerRef->bIsHit() && !HitStopTimer.RunTimer(0))
          {
            DrawColor = (j == 0 || j == NextEnvironmentPosiiton - 1 || k == 0 || k == HowManyImagesPerColumn - 1)
              ? Driscoll::BLACK : Driscoll::DARKGREY;
          }
          else if (bShowPlayerLastHit == true)
          {
            DrawColor = Driscoll::BLACK;
            DrawColor = (j == 0 || j == NextEnvironmentPosiiton - 1 || k == 0 || k == HowManyImagesPerColumn - 1)
              ? Driscoll::Color(207, 7, 0, 255) : Driscoll::Color(233, 120, 99, 255);

            //Should Main Area be a Shade of Red at: 160, 71, 50, 255 || Normal Color at: 233, 160, 99, 255
          }
          else
          {
            DrawColor = (j == 0 || j == NextEnvironmentPosiiton - 1 || k == 0 || k == HowManyImagesPerColumn - 1)
              ? Driscoll::Color(185, 133, 85, 255) : Driscoll::Color(233, 160, 99, 255);
          }

          //Color Options
          // 1: 185, 133, 85
          // 2: 233, 160, 99
          backgroundTexture.Draw(j * 128, k * 128, DrawColor);
        }
      }

      //DRAW ENEMIES
      for (int i = 0; i < CurrentAmountOfEnemies; ++i)
      {
        EnemyRefs[i].Draw();
      }

      //Draw Laser Sight
      DrawLine(PlayerRef->GetWorldPosition().x, PlayerRef->GetWorldPosition().y, GetMousePosition().x, GetMousePosition().y, Driscoll::YELLOW);

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

      MenuObjectRefs[15].Draw();

      //Paused??
      if (PlayerRef->GetShouldPause())
      {
        MenuObjectRefs[7].Draw();
        MenuObjectRefs[8].Draw();
        MenuObjectRefs[9].Draw();
      }
      size_t textureIndex = 0;

      //Draw Mini Health Bar under Mouse Cursor
      switch ((int)PlayerRef->GetHealth())
      {
      default:
      case 1:
        //Full Turret
        textureIndex = 12;
        break;
      case 2:
        //1/4 Turret Left
        textureIndex = 11;
        break;
      case 3:
        //1/2 Turret Left
        textureIndex = 10;
        break;
      case 4:
        //3/4 Turret Left
        textureIndex = 9;
        break;
      case 5:
        // Full Health Turret
        textureIndex = 8;
        break;
      }
     raylib::Texture& texture = TextureManagerRef->GetTexture(textureIndex);
     raylib::Texture& mouseTexture = TextureManagerRef->GetTexture(5);

     //Actually Draw Mini Health Bar Texture:
     texture.Draw
     (
       raylib::Rectangle(0, 0, (float)texture.GetWidth(), (float)texture.GetHeight()),																																								              // SourceRec
       raylib::Rectangle(GetMousePosition().x, GetMousePosition().y + (mouseTexture.GetHeight() / 2) + 7.5f, (float)texture.GetWidth() * 0.5f, (float)texture.GetHeight() * 0.5f),	// DestRec
       raylib::Vector2((float)texture.GetWidth() * 0.5f * 0.5f, (float)texture.GetHeight() * 0.5f * 0.5f),											                                                    // Origin
       90.0f,	// Rotation
       Driscoll::WHITE // Tint
     );

     break;

    }
  case InbetweenRounds:
    MenuObjectRefs[3].Draw();
    MenuObjectRefs[5].Draw();
    MenuObjectRefs[10].Draw();
    MenuObjectRefs[11].Draw();
    MenuObjectRefs[12].Draw();
    MenuObjectRefs[13].Draw();
    MenuObjectRefs[14].Draw();
    break;

  case EndMenu:
    MenuObjectRefs[2].Draw();
    MenuObjectRefs[1].Draw();
    MenuObjectRefs[3].Draw();
    MenuObjectRefs[4].Draw();
    MenuObjectRefs[13].Draw();
    break;
  }

  //DRAW MOUSE
  raylib::Texture& MouseTexture = TextureManagerRef->GetTexture(5);
  MouseTexture.Draw(GetMousePosition().x - (MouseTexture.GetWidth() / 2), GetMousePosition().y - (MouseTexture.GetHeight() / 2));
}
