#include "Headers/AnimalHolder.h"
#include "Headers/Animal.h"
#include <vector>
#include <iostream>

AnimalHolder::AnimalHolder()
{
    animals = std::vector<Animal>();
}

void AnimalHolder::ShowListOfAnimals()
{
    for (int i = 0; i < animals.size(); i++)
    {
        animals[i].Speak();
        std::cout << "Health: " << animals[i].GetHealth() << std::endl;
        std::cout << "Cleanliness: " << animals[i].GetCleanliness() << std::endl;
        std::cout << "Hunger: " << animals[i].GetHunger() << std::endl;
    }
}

int AnimalHolder::GetAnimalCount()
{
    return animals.size();
}

Animal AnimalHolder::GetAnimal(int index)
{
    return animals[index];
}

void AnimalHolder::AddAnimal(Animal animal)
{
    animals.push_back(Animal(animal));
}

void AnimalHolder::DeleteAnimal(int index)
{
    animals.erase(animals.begin() + index);
}
