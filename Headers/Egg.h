#pragma once
#include "Animal.h"
#include <string>

class Egg {
private:
    Animal* baby;
    int rot = 0;
    int incubate = 0;
    bool incubating = false;

public:
    Egg(std::string name, Type type, Gender gender);
    ~Egg(); 

    void Incubate();
    Animal Hatch();

    // Animal property accessors
    std::string GetName() const { return baby->GetName(); }
    Type GetType() const { return baby->GetType(); }
    Gender GetGender() const { return baby->GetGender(); }

    // Egg property accessors
    int GetRotTime() const { return rot; }
    int GetIncubateTime() const { return incubate; }
    bool IsIncubating() const { return incubating; }

    void SetRotTime(int r) { rot = r; }
    void SetIncubateTime(int i) { incubate = i; }
    void SetIncubating(bool i) { incubating = i; }
};