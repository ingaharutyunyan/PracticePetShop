#pragma once
#include <string>
#include <vector>
#include "Egg.h"

class EggHolder {
public:
    EggHolder();
    EggHolder(std::vector<Egg>);
    void ShowListOfEggs();
    void AddEgg(Egg);
    int GetEggCount();
    Egg GetEgg(int);
    void DeleteEgg(int);
private:
    std::vector<Egg> eggs;
};