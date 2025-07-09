#include "Headers/EggHolder.h"
#include "Headers/Egg.h"
#include <vector>
#include <iostream>

EggHolder::EggHolder()
{
    eggs = std::vector<Egg>();
}

Egg EggHolder::GetEgg(int index)
{
    return eggs[index];
}

void EggHolder::ShowListOfEggs()
{
    for (int i = 0; i < eggs.size(); i++)
        {
            std::cout << "Time until rotting: " << eggs[i].GetRotTime() << std::endl;
            std::cout << "Time until hatching: " << eggs[i].GetIncubateTime() << std::endl;
        }
}

void EggHolder::AddEgg(Egg e)
{
    eggs.push_back(e);
}

int EggHolder::GetEggCount()
{
    return eggs.size();
}

void EggHolder::DeleteEgg(int index)
{
    eggs.erase(eggs.begin() + index);
}