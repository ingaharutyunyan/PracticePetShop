#pragma once
#include "IDataPersistence.h"  // This already includes json.hpp and the using declaration
#include "AnimalShelter.h"
#include <string>
#include <filesystem>

class DataPersistenceManager {
public:
    DataPersistenceManager();
    virtual ~DataPersistenceManager() = default;

    void SaveData(AnimalShelter animalShelter);
    nlohmann::json LoadData();  // Fully qualify the return type
    nlohmann::json NewGameData();
    void DeleteData();

private:
    const std::string SAVE_PATH = "Data/data.json";
};