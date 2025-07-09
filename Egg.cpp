#include "Headers/Egg.h"
#include <chrono>
#include <thread>
#include <iostream>

Egg::Egg(std::string name, Type type, Gender gender) 
    : baby(new Animal(name, type, gender)) {}

Egg::~Egg() {
    delete baby;  // Clean up the Animal
}

Animal Egg::Hatch() {
    Animal hatched = *baby;  // Make a copy
    delete baby;             // Clean up the original
    baby = nullptr;          // Set to null
    return hatched;
}

void Egg::Incubate()
{
  SetIncubating(true);
}