#pragma once
#include "GameManager.h"
#include "Character.h"      //For Player -- Player Manages it's Turret and Bullets
#include "Enemy.h"          //For Enemy -- Enemy Manages it's Turret and Bullet
#include "MenuObject.h"     //For Buttons -- GameMode Manages Calling Colliisons and Clicks

enum GameState
{
  MainMenu,
  PlayingGame,
  InbetweenRounds,
  EndMenu
};

class GameMode : public GameManager
{
public:
  GameMode();

  ~GameMode();

  virtual void BeginPlay() override;

  virtual void Update() override;

  virtual void Draw() override;

protected:
  Character* PlayerRef;

  Enemy* EnemyRefs;

  int TOTAL_ENEMY_COUNT;

  MenuObject* MenuObjectRefs;

  GameState CurrentState;

  Timer EndConditionWaitingTimer;

  Timer HitStopTimer;

  Timer StartingCountdownTimer;

  Timer PlayerLastHitFlashTimer;

  bool bShowPlayerLastHit;

  Timer PlayingTime;

  int Rounds;

  int RoundHighScore;

  int CurrentAmountOfEnemies;

  ///Funny
  int CyclePlayerTank;
};

