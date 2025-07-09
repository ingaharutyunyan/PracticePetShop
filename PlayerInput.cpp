#include "Headers/PlayerInput.h"
#include <iostream>

bool PlayerInput::Init(AnimalShelter shelter) {
    animalShelter = &shelter;  // Store reference as pointer
    MainDialogue();
    return true;
}

int PlayerInput::GetChoice() {
    std::string input;
    std::getline(std::cin, input);
    try {
        return std::stoi(input);
    } catch (...) {
        return -1;  // Handle non-numeric input
    }
}

void PlayerInput::StartDialogue(int menuType) {
    if (menuType == 0) {
        std::cout << "What would you like to do?\n"
                  << "1. Check egg list\n"
                  << "2. Check animal list\n"
                  << "3. Take care of animal\n"
                  << "4. Take care of egg\n"
                  << "5. Check supplies list\n"
                  << "6. Options\n"
                  << "7. Buy resources\n\n"
                  << "Enter your choice: ";
    } else if (menuType == 1) {
        std::cout << "Which animal would you like to take care of and how?:\n"
                  << "Please write in this format: [animal index 0-9] and [care index 1-5] for example 2 5\n"
                  << "1. Feed\n"
                  << "2. Give medicine\n"
                  << "3. Wash\n"
                  << "4. Sell\n"
                  << "5. Go back\n"
                  << "Enter your choice: ";
    }
    else if (menuType == 2) {
        std::cout << "Which egg would you like to take care of and how?:\n"
                  << "Please write in this format: [egg index 0-9] and [care index 1-3] for example 4 1\n"
                  << "1. Incubate\n"
                  << "2. Sell\n"
                  << "3. Get rid of all rotted eggs\n\n"
                  << "Enter your choice: ";
    }
    else if (menuType == 3)
    {
        std::cout << "What would you like to do?:\n"
              << "1. Save game\n"
              << "2. Exit game\n"
              << "3. Return to game\n\n"
              << "Enter your choice: ";
    }
    else {
        std::cout << "Invalid menu type!" << std::endl;
        StartDialogue(0);
    }
}

int PlayerInput::StartDialogueAndGetChoice(int menuType) {
    StartDialogue(menuType);
    return GetChoice();
}

std::pair<int, int> PlayerInput::StartDialogueAndGetMultiChoice(int menuType) {
    StartDialogue(menuType);
    std::string input = GetMultiChoice();

    // Parse two integers from the input string
    std::istringstream iss(input);
    std::vector<int> choices;
    int num;

    while (iss >> num) {
        choices.push_back(num);
        // Skip commas or other delimiters if needed
        if (iss.peek() == ',' || iss.peek() == ' ') {
            iss.ignore();
        }
    }

    // Ensure we have at least two numbers
    if (choices.size() < 2) {
        // Return invalid pair if not enough inputs
        return std::make_pair(-1, -1);
    }

    return std::make_pair(choices[0], choices[1]);
}

std::string PlayerInput::GetMultiChoiceInput() {
    std::string input;
    std::getline(std::cin, input);

    // Basic input validation - remove any non-digit characters except spaces and commas
    input.erase(std::remove_if(input.begin(), input.end(), 
        [](char c) { return !(std::isdigit(c) || c == ' ' || c == ','); }), 
        input.end());

    return input;
}

void PlayerInput::MainDialogue() {
    std::cout << "Welcome to the game!" << std::endl;
    FirstDialogue();
}

void PlayerInput::FirstDialogue() {
    int choice = StartDialogueAndGetChoice(0);
    switch (choice) {
        case 1:
            animalShelter->ShowListOfEggs();  // Use -> for pointer
            FirstDialogue();
            break;
        case 2:
            animalShelter->ShowListOfAnimals();  // Use -> for pointer
            FirstDialogue();
            break;
        case 3:
            SecondDialogue();
            break;
        case 4:
            //ThirdDialogue();
            break;
        case 5:
            animalShelter -> ShowSupplies();  // Use -> for pointer
            FirstDialogue();
            break;
        case 6:
            FourthDialogue();
            break;
        case 7:
            //FifthDialogue();
            break;
        default:
            std::cout << "Invalid choice! Please enter 1 or 2.\n";
    }
}

void PlayerInput::SecondDialogue() {
    auto [animalIndex, choice] = StartDialogueAndGetChoice(1);
    switch (choice) {
        case 1:
            std::cout << "Feeding animal #" << animalIndex << ".\n";
            animalShelter->FeedAnimal(animalIndex); 
            break;
        case 2:
            std::cout << "Curing animal #" << animalIndex << ".\n";
            animalShelter->HealAnimal(animalIndex);
            break;
        case 3:
            std::cout << "Cleaning animal #" << animalIndex << ".\n";
            animalShelter->CleanAnimal(animalIndex);
            break;
        case 4:
            std::cout << "Selling animal #" << animalIndex << ".\n";
            animalShelter->SellAnimal(animalIndex);
            break;
        case 5:
            FirstDialogue();
            break;
        default:
            std::cout << "Invalid choice! Please enter 1 or 2.\n";
    }
}

void PlayerInput::ThirdDialogue() {
    int choice = StartDialogueAndGetChoice(2);
    switch (choice) {
        case 1:
            
            break;
        case 2:
            
            break;
        case 3:
            
            break;
        case 4:
            
            break;
        case 5:
            
            break;
        case 6:
            
            break;
        default:
            std::cout << "Invalid choice! Please enter 1 or 2.\n";
    }
}

void PlayerInput::FourthDialogue() {
    int choice = StartDialogueAndGetChoice(0);
    switch (choice) {
        case 1:
            animalShelter -> SaveData();
            break;
        case 2:
            EndGame();
            break;
        case 3:
            FirstDialogue();
            break;
        default:
            std::cout << "Invalid choice! Please enter 1 or 2.\n";
    }
}

void PlayerInput::EndGame()
{
    std::cout << "Thanks for playing!" << std::endl;
}

// method that listens in on input constantly...?