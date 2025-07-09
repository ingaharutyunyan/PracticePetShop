#include "Headers/DataPersistenceManager.h"
#include <fstream>
#include <stdexcept>
#include <filesystem> 
#include "Headers/IDataPersistence.h"

// Constructor
DataPersistenceManager::DataPersistenceManager() {
}

// Override IDataPersistence functions
void DataPersistenceManager::SaveData(AnimalShelter animalShelter) {
    try {
        json saveData;
       /*  saveData["animals"] = animalShelter.GetAnimalsData();
        saveData["eggs"] = animalShelter.GetEggsData();
        saveData["supplies"] = animalShelter.GetSuppliesData(); */

        std::ofstream outputFile(SAVE_PATH);
        if (!outputFile.is_open()) {
            throw std::runtime_error("Could not open save file.");
        }
        outputFile << saveData.dump(4);
    } catch (const std::exception& e) {
        throw std::runtime_error("Save failed: " + std::string(e.what()));
    }
}

json DataPersistenceManager::LoadData() {
    try {
        std::ifstream inputFile(SAVE_PATH);
        if (!inputFile.is_open()) {
            return NewGameData(); // Fallback to new data if file doesn't exist
        }
        json loadedData;
        inputFile >> loadedData;
        return loadedData;
    } catch (const std::exception& e) {
        throw std::runtime_error("Load failed: " + std::string(e.what()));
    }
}

json DataPersistenceManager::NewGameData() {
    return {
        {"animals", json::array()},
        {"supplies", {
            {"medicine", 30},
            {"food", 30},
            {"soap", 30},
            {"money", 100}
        }}
    };
}

void DataPersistenceManager::DeleteData() {
    if (std::remove(SAVE_PATH.c_str()) != 0) {
        throw std::runtime_error("Could not delete save file.");
    }
}