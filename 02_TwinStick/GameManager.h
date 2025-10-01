#pragma once
#include "Object.h"

class GameManager : public Object
{
public:
  GameManager();

  ~GameManager();

  virtual void BeginPlay() override; 

  virtual void Update() override;
  
  virtual void Draw() override;
};

