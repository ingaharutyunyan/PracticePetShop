#pragma once
#include <string>
#include "AnimalHolder.h"
#include "IDataPersistence.h"
#include "EggHolder.h"
#include <vector>

class AnimalShelter : public IDataPersistence {
public:
    void ShowListOfAnimals();
    void ShowListOfEggs();
    void FeedAnimal(int index);
    void CleanAnimal(int index);
    void HealAnimal(int index);
    void SellAnimal(int index);
    void CreateEgg();
    void SellEgg(int index);
    void IncubateEgg(int index);
    void HatchEgg(int index);
    Egg RandomEggGenerator();
    void AddAnimal(Animal);
    void CleanRottedEggs();
    bool Init(nlohmann::json);
    virtual void SaveData();
    virtual nlohmann::json  LoadData();
    nlohmann::json GetAnimalsData();
    nlohmann::json GetEggsData();
    nlohmann::json GetSuppliesData();
    void MachineCountdown();
    void ShowSupplies();
private:
    AnimalHolder animalHolder;
    EggHolder eggHolder;
    int medicine;
    int food;
    int soap;
    int money; 
};