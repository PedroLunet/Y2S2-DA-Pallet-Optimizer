#ifndef PALLETPACKINGOPTIMIZER_H
#define PALLETPACKINGOPTIMIZER_H

#include "../data/DataManager.h"
#include <string>
#include <vector>

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

    // Algorithm implementations will be added in future tasks

    // T2.1: Exhaustive (Brute-Force) Approach
    // T2.2: Dynamic Programming Approach
    // T2.3: Approximation Algorithms (Greedy Approach)
    // T2.4: Integer Linear Programming Algorithm
};

#endif // PALLETPACKINGOPTIMIZER_H
