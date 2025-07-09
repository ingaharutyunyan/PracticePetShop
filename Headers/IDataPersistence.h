// IDataPersistence.h
#pragma once

#include "../Data/json.hpp"

// Forward declaration instead of full include
class AnimalShelter;

using json = nlohmann::json;

class IDataPersistence {
public:
    virtual ~IDataPersistence() = default;
    virtual void SaveData() = 0;
    virtual json LoadData() = 0;
};