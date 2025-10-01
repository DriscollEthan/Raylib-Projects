#pragma once
#include "GameManager.h"
#include "Character.h" //For Player -- Player Manages it's Turret and Bullets
#include "Enemy.h"     //For Enemy -- Enemy Manages it's Turret and Bullet\

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
};

