#include "Headers/GameManager.h"
#include <iostream>
#include <fstream>

void GameManager::StartGame() {
    json gameData = dataPersistenceManager.LoadData();
    
    if (gameData.is_null() || gameData.empty()) {
        std::cout << "No saved data found, starting fresh..." << std::endl;
        gameData = dataPersistenceManager.NewGameData();
    }
    
    animalShelter.Init(gameData);
    playerInput.Init(animalShelter);  // Now matches the signature
}

// method that updates the view of the animal shelter every second
// method that direct player input to the correct method in the animal shelter
// method that saves the game data every second
/* 
void GameManager::UpdateView()
{
    
}

 */