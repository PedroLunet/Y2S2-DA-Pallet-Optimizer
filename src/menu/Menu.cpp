#include "Menu.h"

#include <iostream>
#include <limits>
#include <thread>

Menu::Menu() = default;

void Menu::credits()
{
    std::cout << "" << std::endl;
    std::cout << "Design of Algorithms Project 2 - Spring 2025" << std::endl;
    std::cout << "Developed by Group 2 - Class 15" << std::endl;
}

void Menu::mainMenu()
{
    system("clear");

    std::cout << "\n0. Load Dataset" << std::endl;
    std::cout << "1. Display Dataset Information" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "2. Solve using Brute Force (Exhaustive Search)" << std::endl;
    std::cout << "3. Solve using Backtracking" << std::endl;
    std::cout << "4. Solve using Dynamic Programming" << std::endl;
    std::cout << "5. Solve using Greedy Approximation" << std::endl;
    std::cout << "6. Solve using Integer Linear Programming" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "7. Compare All Algorithms" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "8. Exit" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Please select an option: ";

    std::cout.flush();

    optionPicker();
}

void Menu::optionPicker()
{
    int option;
    std::cin >> option;

    switch (option)
    {
    case 0:
    {
        std::string input;
        std::cout << "Enter dataset number (e.g., 01, 02): ";
        std::cin >> input;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        datasetNumber = input;

        bool success = optimizer.loadDataset(datasetNumber);

        if (success)
        {
            std::cout << "\nDataset " << datasetNumber << " loaded successfully." << std::endl;
        }
    }
    break;

    case 1:
        if (optimizer.getCurrentDataset().empty())
        {
            std::cerr << "\nPlease load a dataset first." << std::endl;
            std::cout.flush();
            break;
        }
        optimizer.displayDatasetInfo();
        break;

    case 2:
    {
        if (optimizer.getCurrentDataset().empty())
        {
            std::cerr << "\nPlease load a dataset first." << std::endl;
            std::cout.flush();
            break;
        }
        std::cout << "\nSolving using Brute Force...\n" << std::endl;
        Solution solution = optimizer.solveBruteForce();
        displaySolution(solution);
    }
    break;

    case 3:
    {
        if (optimizer.getCurrentDataset().empty())
        {
            std::cerr << "\nPlease load a dataset first." << std::endl;
            break;
        }
        std::cout << "\nSolving using Backtracking...\n"
                  << std::endl;
        Solution solution = optimizer.solveBacktracking();
        displaySolution(solution);
    }
    break;

    case 4:
        std::cout << "Dynamic Programming algorithm not implemented yet." << std::endl;
        break;

    case 5:
        std::cout << "Greedy Approximation algorithm not implemented yet." << std::endl;
        break;

    case 6:
        std::cout << "Integer Linear Programming algorithm not implemented yet." << std::endl;
        break;

    case 7:
        std::cout << "Algorithm comparison not implemented yet." << std::endl;
        break;

    case 8:
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

    std::cout.flush();

    const std::chrono::seconds dura( 1);

    std::this_thread::sleep_for(dura);

    mainMenu();
}

void Menu::displaySolution(const Solution &solution)
{
    std::cout << "==============================" << std::endl;
    std::cout << "Algorithm: " << solution.algorithmName << std::endl;
    std::cout << "Execution Time: " << solution.executionTime << " ms" << std::endl;
    std::cout << "Total Profit: " << solution.totalProfit << std::endl;
    std::cout << "Total Weight: " << solution.totalWeight << std::endl;

    std::cout << "Selected Pallets: ";
    for (size_t i = 0; i < solution.selectedPallets.size(); ++i)
    {
        std::cout << solution.selectedPallets[i];
        if (i < solution.selectedPallets.size() - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    std::cout << "==============================" << std::endl;
}
