#pragma once
#include "AnimalShelter.h"

class PlayerInput {
private:
    AnimalShelter* animalShelter;  // Use pointer to avoid copying
    
public:
    bool Init(AnimalShelter shelter);  // Single Init with reference
    int GetChoice();
    void StartDialogue(int);
    int StartDialogueAndGetChoice(int);  // Default argument
    void MainDialogue();
    void FirstDialogue();
    void SecondDialogue();
    void ThirdDialogue();
    void FourthDialogue();
    void EndGame();
    std::pair<int, int> StartDialogueAndGetMultiChoice(const std::string& prompt);
    std::string GetMultiChoice();
};