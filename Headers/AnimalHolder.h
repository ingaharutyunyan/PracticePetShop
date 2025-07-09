#pragma once
#include "Animal.h"
#include <string>
#include <vector>

class AnimalHolder {
public:
  AnimalHolder();
  AnimalHolder(std::vector<Animal>);
  void ShowListOfAnimals();
  Animal GetAnimal(int);
  void AddAnimal(Animal);
  int GetAnimalCount();
  void DeleteAnimal(int);

private:
  std::vector<Animal> animals;
};