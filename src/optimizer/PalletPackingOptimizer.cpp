#include "PalletPackingOptimizer.h"
#include <iostream>
#include <algorithm>
#include <bitset>

Solution PalletPackingOptimizer::solveBruteForce()
{
    Solution solution;
    solution.algorithmName = "Brute Force (Exhaustive Search)";

    const std::vector<Pallet> &pallets = getPallets();
    int capacity = getTruckCapacity();

    auto startTime = std::chrono::high_resolution_clock::now();

    int n = pallets.size();
    int bestProfit = 0;
    int bestWeight = 0;
    std::vector<int> bestSelection;

    long long totalCombinations = 1LL << n;

    for (long long mask = 0; mask < totalCombinations; mask++)
    {
        int currentWeight = 0;
        int currentProfit = 0;
        std::vector<int> currentSelection;

        for (int i = 0; i < n; i++)
        {
            if (mask & (1LL << i))
            {
                currentWeight += pallets[i].weight;
                currentProfit += pallets[i].profit;
                currentSelection.push_back(pallets[i].id);
            }
        }

        if (currentWeight <= capacity && currentProfit > bestProfit)
        {
            bestProfit = currentProfit;
            bestWeight = currentWeight;
            bestSelection = currentSelection;
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    solution.totalProfit = bestProfit;
    solution.totalWeight = bestWeight;
    solution.selectedPallets = bestSelection;
    solution.executionTime = duration.count();

    std::cout << "Brute Force Analysis:" << std::endl;
    std::cout << "Total combinations explored: " << totalCombinations << std::endl;
    std::cout << "Time complexity: O(2^n) where n = " << n << std::endl;
    std::cout << "For larger datasets, this algorithm becomes impractical." << std::endl;

    return solution;
}

Solution PalletPackingOptimizer::solveBacktracking()
{
    Solution solution;
    solution.algorithmName = "Backtracking";

    const std::vector<Pallet> &pallets = getPallets();
    int capacity = getTruckCapacity();

    auto startTime = std::chrono::high_resolution_clock::now();

    int bestProfit = 0;
    std::vector<int> bestSelection;
    std::vector<int> currentSelection;

    backtrack(pallets, capacity, 0, 0, 0, currentSelection, bestProfit, bestSelection);

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    int bestWeight = 0;
    for (int id : bestSelection)
    {
        for (const auto &pallet : pallets)
        {
            if (pallet.id == id)
            {
                bestWeight += pallet.weight;
                break;
            }
        }
    }

    solution.totalProfit = bestProfit;
    solution.totalWeight = bestWeight;
    solution.selectedPallets = bestSelection;
    solution.executionTime = duration.count();

    return solution;
}

void PalletPackingOptimizer::backtrack(
    const std::vector<Pallet> &pallets, int capacity,
    int index, int currentWeight, int currentProfit,
    std::vector<int> &currentSelection,
    int &bestProfit, std::vector<int> &bestSelection)
{

    int n = pallets.size();

    if (index == n)
    {
        if (currentProfit > bestProfit)
        {
            bestProfit = currentProfit;
            bestSelection = currentSelection;
        }
        return;
    }

    backtrack(pallets, capacity, index + 1, currentWeight, currentProfit,
              currentSelection, bestProfit, bestSelection);

    if (currentWeight + pallets[index].weight <= capacity)
    {
        currentSelection.push_back(pallets[index].id);

        backtrack(pallets, capacity, index + 1,
                  currentWeight + pallets[index].weight,
                  currentProfit + pallets[index].profit,
                  currentSelection, bestProfit, bestSelection);

        currentSelection.pop_back();
    }
}
