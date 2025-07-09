#pragma once
#include <string>
#include "Gender.h"
#include "Type.h"

class Animal {
public:
    std::string name;
    Type type;   // Mammal or Reptile
    int health;         // Max health = 50
    Gender gender;
    int cleanliness;    // Max cleanliness = 50
    int hunger;

    Animal(std::string n, Type t, Gender g); // Minimal constructor
    Animal(std::string n, Type t, int h = 50, int c = 50, int hun = 50, Gender g = Gender::Female); // Full

    int GetHealth();
    int GetCleanliness();
    int GetHunger();

    void SetCleanliness(int c);
    void SetHunger(int hun);
    void SetHealth(int h);

    // Method declaration
    void Speak();
    std::string GetName() { return name; }
    Gender GetGender() { return gender; }
    Type GetType() { return type; }
};