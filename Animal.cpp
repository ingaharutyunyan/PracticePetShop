#include "Headers/Animal.h"
#include "Headers/Gender.h"
#include "Headers/Type.h"
#include <iostream>

// Minimal constructor (delegates to full constructor)
Animal::Animal(std::string n, Type t, Gender g) 
    : Animal(n, t, 50, 50, 50, g) {}  // Calls full constructor with defaults

// Full constructor (matches header AND respects member order)
Animal::Animal(std::string n, Type t, int h, int c, int hun, Gender g) 
    : name(n), type(t), health(h), gender(g), cleanliness(c), hunger(hun) {}  

// Rest of the methods...
void Animal::Speak() {
    std::cout << "I am a " << name
              << ", type: " << (type == Type::Mammal ? "Mammal" : "Reptile")
              << ", gender: " << (gender == Gender::Male ? "Male" : "Female")
              << ", health: " << health << std::endl;
}

int Animal::GetHealth() { return health; }
int Animal::GetCleanliness() { return cleanliness; }
int Animal::GetHunger() { return hunger; }

void Animal::SetCleanliness(int c) { cleanliness = c; }
void Animal::SetHunger(int hun) { hunger = hun; }
void Animal::SetHealth(int h) { health = h; }