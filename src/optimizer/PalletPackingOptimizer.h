#ifndef PALLETPACKINGOPTIMIZER_H
#define PALLETPACKINGOPTIMIZER_H

#include "../data/DataManager.h"
#include <string>
#include <vector>
#include <chrono>

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
 * @brief Class to handle the Pallet Packing Optimization Problem algorithms
 */
class PalletPackingOptimizer
{

public:
    PalletPackingOptimizer() {}

    /**
     * @brief Loads a dataset from the specified files
     * @param datasetNumber The dataset number to load (e.g., 01, 02)
     * @return True if the dataset was loaded successfully, false otherwise
     */
    bool loadDataset(const std::string &datasetNumber)
    {
        return DataManager::getInstance()->loadDataset(datasetNumber);
    }

    /**
     * @brief Gets the list of available pallets
     * @return The list of available pallets
     */
    const std::vector<Pallet> &getPallets() const
    {
        return DataManager::getInstance()->getPallets();
    }

    /**
     * @brief Gets the truck capacity
     * @return The truck capacity
     */
    int getTruckCapacity() const
    {
        return DataManager::getInstance()->getTruckCapacity();
    }

    /**
     * @brief Gets the name of the currently loaded dataset
     * @return The name of the currently loaded dataset
     */
    std::string getCurrentDataset() const
    {
        return DataManager::getInstance()->getCurrentDataset();
    }

    /**
     * @brief Displays information about the currently loaded dataset
     */
    void displayDatasetInfo() const
    {
        DataManager::getInstance()->displayDatasetInfo();
    }

    /**
     * @brief Solves the pallet packing problem using brute force (exhaustive search)
     * @return Solution structure containing the results
     * @time_complexity O(2^n) where n is the number of pallets
     * @space_complexity O(n) for storing the best solution
     */
    Solution solveBruteForce();

    /**
     * @brief Solves the pallet packing problem using backtracking to improve efficiency
     * @return Solution structure containing the results
     * @time_complexity O(2^n) in worst case, but typically better due to early pruning
     * @space_complexity O(n) for recursion stack and storing the best solution
     */
    Solution solveBacktracking();

private:
    /**
     * @brief Helper function for the backtracking algorithm
     * @param pallets The list of pallets
     * @param capacity The truck capacity
     * @param index The current pallet index being considered
     * @param currentWeight The current accumulated weight
     * @param currentProfit The current accumulated profit
     * @param currentSelection Current selected pallets
     * @param bestProfit Reference to track the best profit found so far
     * @param bestSelection Reference to store the best selection found so far
     */
    void backtrack(const std::vector<Pallet> &pallets, int capacity,
                   int index, int currentWeight, int currentProfit,
                   std::vector<int> &currentSelection,
                   int &bestProfit, std::vector<int> &bestSelection);
};

#endif // PALLETPACKINGOPTIMIZER_H
