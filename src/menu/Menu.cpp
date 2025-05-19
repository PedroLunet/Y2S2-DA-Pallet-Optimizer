#include "Menu.h"

#include <iostream>

Menu::Menu() = default;

void Menu::credits()
{
    std::cout << "" << std::endl;
    std::cout << "Design of Algorithms Project 2 - Spring 2025" << std::endl;
    std::cout << "Developed by Group 2 - Class 15" << std::endl;
}

void Menu::mainMenu()
{
    std::cout << "" << std::endl;
    std::cout << "0. Load Dataset" << std::endl;
    std::cout << "1. Display Dataset Information" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "2. Solve using Brute Force (Exhaustive Search)" << std::endl;
    std::cout << "3. Solve using Dynamic Programming" << std::endl;
    std::cout << "4. Solve using Greedy Approximation" << std::endl;
    std::cout << "5. Solve using Integer Linear Programming" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "6. Compare All Algorithms" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "7. Exit" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Please select an option: ";

    optionPicker();
}

void Menu::optionPicker()
{
    int option;
    std::cin >> option;

    switch (option)
    {
    case 0:
        std::cout << "Enter dataset number (e.g., 01, 02): ";
        std::cin >> datasetNumber;
        if (optimizer.loadDataset(datasetNumber))
        {
            std::cout << "Dataset " << datasetNumber << " loaded successfully." << std::endl;
        }
        else
        {
            std::cout << "Failed to load dataset " << datasetNumber << "." << std::endl;
        }
        break;

    case 1:
        optimizer.displayDatasetInfo();
        break;

    case 2:
        std::cout << "Brute Force algorithm not implemented yet." << std::endl;
        break;

    case 3:
        std::cout << "Dynamic Programming algorithm not implemented yet." << std::endl;
        break;

    case 4:
        std::cout << "Greedy Approximation algorithm not implemented yet." << std::endl;
        break;

    case 5:
        std::cout << "Integer Linear Programming algorithm not implemented yet." << std::endl;
        break;

    case 6:
        std::cout << "Algorithm comparison not implemented yet." << std::endl;
        break;

    case 7:
        std::cout << "Exiting the program. Goodbye!" << std::endl;
        exit(0);
        break;

    default:
        std::cout << "Invalid choice. Please try again." << std::endl;
        std::cout << "" << std::endl;
        std::cout << "Please select an option: ";
        optionPicker();
        return;
    }

    std::cout << std::endl;
    mainMenu();
}
