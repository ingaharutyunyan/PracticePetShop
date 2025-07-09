#include "Headers/AnimalShelter.h"
#include "Headers/AnimalHolder.h"
#include "Headers/EggHolder.h"
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <atomic>
#include <stdexcept>

bool AnimalShelter::Init(nlohmann::json gameData) {
    if (gameData.is_null() || gameData.empty()) {
        std::cerr << "Error: Invalid game data provided to Init()\n";
        return false;
    }

    try {
        // Initialize animals from JSON
        if (gameData.contains("animals") && gameData["animals"].is_array()) {
            for (const auto& animalData : gameData["animals"]) {
                if (animalData.is_object()) {
                    std::string name = animalData.value("name", "Unknown");
                    Type type = static_cast<Type>(animalData.value("type", 0));
                    Gender gender = static_cast<Gender>(animalData.value("gender", 0));

                    Animal animal(name, type, gender);

                    // Set additional properties if they exist
                    if (animalData.contains("health")) {
                        animal.SetHealth(animalData["health"]);
                    }
                    if (animalData.contains("cleanliness")) {
                        animal.SetCleanliness(animalData["cleanliness"]);
                    }
                    if (animalData.contains("hunger")) {
                        animal.SetHunger(animalData["hunger"]);
                    }

                    animalHolder.AddAnimal(animal);
                }
            }
        }

        // Initialize eggs - now properly creating Egg objects that wrap Animals
        if (gameData.contains("eggs") && gameData["eggs"].is_array()) {
            for (const auto& eggData : gameData["eggs"]) {
                if (eggData.is_object()) {
                    std::string name = eggData.value("name", "Unknown Egg");
                    Type type = static_cast<Type>(eggData.value("type", 0));
                    Gender gender = static_cast<Gender>(eggData.value("gender", 0));

                    // Create the egg with the animal inside
                    Egg egg(name, type, gender);

                    // Set egg-specific properties
                    if (eggData.contains("rotTime")) {
                        egg.SetRotTime(eggData["rotTime"]);
                    }
                    if (eggData.contains("incubateTime")) {
                        egg.SetIncubateTime(eggData["incubateTime"]);
                    }

                    eggHolder.AddEgg(egg);
                }
            }
        }

        eggHolder = EggHolder();
        animalHolder = AnimalHolder();
        // Initialize supplies
        const auto& supplies = gameData["supplies"];
        medicine = supplies.value("medicine", 10);
        food = supplies.value("food", 10);
        soap = supplies.value("soap", 10);
        money = supplies.value("money", 100);

        std::cout << "Animal Shelter initialized with " 
                 << animalHolder.GetAnimalCount() << " animals and "
                 << eggHolder.GetEggCount() << " eggs\n";
        return true;

    } catch (const nlohmann::json::exception& e) {
        std::cerr << "JSON error in Init(): " << e.what() << '\n';
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Error in Init(): " << e.what() << '\n';
        return false;
    }
    MachineCountdown();
}


nlohmann::json AnimalShelter::GetSuppliesData() {
    return {
        {"medicine", medicine},
        {"food", food},
        {"soap", soap},
        {"money", money}
    };
}

void AnimalShelter::ShowSupplies()
{
    std::cout << "Medicine: " << medicine << std::endl;
    std::cout << "Food: " << food << std::endl;
    std::cout << "Soap: " << soap << std::endl;
    std::cout << "Money: " << money << std::endl;
}

void AnimalShelter::SaveData() {
    nlohmann::json data;
    data["animals"] = GetAnimalsData();
    data["eggs"] = GetEggsData();
    data["supplies"] = GetSuppliesData();

    // Write data to file
    // std::ofstream(filePath) << data.dump(4);
}

nlohmann::json AnimalShelter::LoadData() {
    try {
        // std::ifstream file(filePath);
        // nlohmann::json data;
        // file >> data;
        // return data;
        return nlohmann::json(); // Placeholder
    } catch (const std::exception& e) {
        std::cerr << "Load error: " << e.what() << '\n';
        return nlohmann::json();
    }
}

void AnimalShelter::ShowListOfAnimals()
{
    animalHolder.ShowListOfAnimals();
}

void AnimalShelter::ShowListOfEggs()
{
    eggHolder.ShowListOfEggs();
}

void AnimalShelter::FeedAnimal(int index)
{
    if (food < 5) throw std::runtime_error("Not enough food");
    animalHolder.GetAnimal(index).SetHunger(animalHolder.GetAnimal(index).GetHunger() + 10);
    food -= 5;
}

void AnimalShelter::CleanAnimal(int index)
{ 
    if (soap < 5) throw std::runtime_error("Not enough soap");
    animalHolder.GetAnimal(index).SetCleanliness(animalHolder.GetAnimal(index).GetCleanliness() + 10);
    soap -= 5;
}

void AnimalShelter::HealAnimal(int index)
{
    if (medicine < 5) throw std::runtime_error("Not enough medicine");
    animalHolder.GetAnimal(index).SetHealth(animalHolder.GetAnimal(index).GetHealth() + 10);
    medicine -= 5;
}

void AnimalShelter::SellAnimal(int index)
{
    try
        {
            animalHolder.DeleteAnimal(index);
            money += 500; // change this to calculate higher for higher health and cleanliness
            std::cout << "Animal sold for " << money << " money!" << std::endl;
        }
    catch (const std::exception& e)
        {
            std::cerr << "Error selling animal: " << e.what() << '\n';
        }
}

void AnimalShelter::SellEgg(int index)
{
    eggHolder.DeleteEgg(index);
    money += 20;
}

void AnimalShelter::IncubateEgg(int index)
{
    eggHolder.GetEgg(index).Incubate();
}

void AnimalShelter::AddAnimal(Animal an)
{
   if (animalHolder.GetAnimalCount() >= 10) return;
    animalHolder.AddAnimal(an);
}

Egg AnimalShelter::RandomEggGenerator() {
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> gender_dist(0, 1);
    std::uniform_int_distribution<> type_dist(0, 9);
    std::uniform_int_distribution<> name_dist(0, 34); // For name selection

    // Properly initialize vector of names
    std::vector<std::string> names = {
        "Katy", "John", "Mike", "Sarah", "Lisa", 
        "Jake", "Jordan", "Moggle", "Bogdan", "Pukkle",
        "Anna", "Bob", "Charlie", "Dave", "Eve",
        "Frank", "Grace", "Hank", "Ivy", "Jack",
        "Kate", "Larry", "Mary", "Nancy", "Oscar",
        "Pete", "Quinn", "Ray", "Sally", "Tom",
        "Uma", "Victor", "Wendy", "Xavier", "Yoko"
    };

    std::string name = names[name_dist(gen)];
    Gender gender = (gender_dist(gen) == 0) ? Gender::Male : Gender::Female;
    Type type = (type_dist(gen) < 7) ? Type::Mammal : Type::Reptile;

    Egg newEgg(name, type, gender);
    return newEgg;
}
void AnimalShelter::MachineCountdown()
{
    std::atomic<bool> running(true);

    std::thread countdownThread([this, &running]() {
        auto lastHungerTime = std::chrono::steady_clock::now();
        auto lastHealthTime = std::chrono::steady_clock::now();
        auto lastCleanTime = std::chrono::steady_clock::now();
        auto lastEggRotTime = std::chrono::steady_clock::now();
        auto lastEggGenTime = std::chrono::steady_clock::now();

        while (running) {
            auto now = std::chrono::steady_clock::now();

            // Animal hunger
            if (now - lastHungerTime >= std::chrono::seconds(1)) {
                for (int i = 0; i < animalHolder.GetAnimalCount(); i++) {
                    animalHolder.GetAnimal(i).SetHunger(
                        animalHolder.GetAnimal(i).GetHunger() - 1);
                }
                lastHungerTime = now;
            }

            // Animal health
            if (now - lastHealthTime >= std::chrono::seconds(2)) {
                for (int i = 0; i < animalHolder.GetAnimalCount(); i++) {
                    Animal animal = animalHolder.GetAnimal(i);
                    if (animal.GetHunger() < 10 || animal.GetCleanliness() < 10) {
                        animal.SetHealth(animal.GetHealth() - 1);
                    }
                }
                lastHealthTime = now;
            }

            // Animal cleanliness
            if (now - lastCleanTime >= std::chrono::seconds(3)) {
                for (int i = 0; i < animalHolder.GetAnimalCount(); i++) {
                    animalHolder.GetAnimal(i).SetCleanliness(
                        animalHolder.GetAnimal(i).GetCleanliness() - 1);
                }
                lastCleanTime = now;
            }

            // Egg rotting
            if (now - lastEggRotTime >= std::chrono::seconds(1)) {
                for (int i = 0; i < eggHolder.GetEggCount(); i++) {
                    Egg egg = eggHolder.GetEgg(i);
                    if (!egg.IsIncubating()) {
                        egg.SetRotTime(egg.GetRotTime() + 1);
                    }
                }
                CleanRottedEggs();
                lastEggRotTime = now;
            }

            // Egg generation
            if (now - lastEggGenTime >= std::chrono::seconds(10)) {
                RandomEggGenerator();
                lastEggGenTime = now;
            }

            // Egg hatching
            for (int i = 0; i < eggHolder.GetEggCount(); i++) {
                Egg egg = eggHolder.GetEgg(i);
                if (egg.IsIncubating() && egg.GetIncubateTime() >= 15) {
                    Animal newAnimal(egg.GetName(), egg.GetType(), egg.GetGender());
                    animalHolder.AddAnimal(newAnimal);
                    eggHolder.DeleteEgg(i);
                    i--;
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });
    countdownThread.detach();
}

// Single implementation of CleanRottedEggs
void AnimalShelter::CleanRottedEggs()
{
    for (int i = 0; i < eggHolder.GetEggCount(); i++) {
        if (eggHolder.GetEgg(i).GetRotTime() >= 10) {
            eggHolder.DeleteEgg(i);
            i--;
        }
    }
}

nlohmann::json AnimalShelter::GetAnimalsData() {
    nlohmann::json animals;
    for (int i = 0; i < animalHolder.GetAnimalCount(); i++) {
        Animal animal = animalHolder.GetAnimal(i);
        animals.push_back({
            {"name", animal.name},
            {"type", static_cast<int>(animal.type)},
            {"health", animal.GetHealth()},
            {"gender", static_cast<int>(animal.gender)},
            {"cleanliness", animal.GetCleanliness()},
            {"hunger", animal.GetHunger()}
        });
    }
    return animals;
}

nlohmann::json AnimalShelter::GetEggsData() {
    nlohmann::json eggs;
    for (int i = 0; i < eggHolder.GetEggCount(); i++) {
        Egg egg = eggHolder.GetEgg(i);
        eggs.push_back({
            {"name", egg.GetName()},
            {"type", static_cast<int>(egg.GetType())},
            {"gender", static_cast<int>(egg.GetGender())},
            {"rotTime", egg.GetRotTime()},
            {"incubateTime", egg.GetIncubateTime()},
            {"isIncubating", egg.IsIncubating()}
        });
    }
    return eggs;
}

void AnimalShelter::CreateEgg()
{
  if (eggHolder.GetEggCount() >= 10) return;
    eggHolder.AddEgg(RandomEggGenerator());
}

void AnimalShelter::SayHi()
{
    std::cout << "Hi!" << std::endl;
}