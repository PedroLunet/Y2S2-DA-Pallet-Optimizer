#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

#include "menu/Menu.h"
#include "data/DataManager.h"

/**
 * @brief Structure to represent a solution to the knapsack problem
 */
struct Solution
{
    std::vector<int> selectedPallets; ///< IDs of selected pallets
    int totalWeight;                  ///< Total weight of selected pallets
    int totalProfit;                  ///< Total profit of selected pallets
    double executionTime;             ///< Execution time in milliseconds
    std::string algorithmName;        ///< Name of the algorithm used
};

/**
 * @brief Displays the solution to the knapsack problem
 * @param solution The solution to display
 */
void displaySolution(const Solution &solution)
{
    std::cout << "\nAlgorithm: " << solution.algorithmName << std::endl;
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
}

/**
 * @brief Main function to run the Pallet Packing Optimization Tool
 * @return 0 on successful execution
 */
int main()
{
    Menu menu;
    menu.credits();
    menu.mainMenu();

    // Clean up the DataManager singleton before exiting
    DataManager::destroyInstance();

    return 0;
}
