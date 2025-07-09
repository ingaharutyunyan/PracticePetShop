#pragma once

#include "AnimalShelter.h"
#include "PlayerInput.h"
#include "DataPersistenceManager.h"

class GameManager
{
  private:
      PlayerInput playerInput;
      AnimalShelter animalShelter;
        DataPersistenceManager dataPersistenceManager;

  public:
      void StartGame();
};