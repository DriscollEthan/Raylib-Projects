#pragma once
#include "Object.h"
#include "Character.h" //For Player -- Player Manages it's Turret and Bullets
#include "Enemy.h"     //For Enemy -- Enemy Manages it's Turret and Bullets




class GameManager : public Object
{
public:
  GameManager();

  ~GameManager();

  virtual void BeginPlay() override; 

  virtual void Update() override;
  
  virtual void Draw() override;
  
protected:
  Character* PlayerRef;

  Enemy* EnemyRef;
};

