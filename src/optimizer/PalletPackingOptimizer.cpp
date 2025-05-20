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
    int n = pallets.size();

    auto startTime = std::chrono::high_resolution_clock::now();

    int bestProfit = 0;
    std::vector<bool> usedPallets(n, false);
    std::vector<bool> currentPallets(n, false);

    backtrack(pallets, n, 0, capacity, 0, currentPallets, bestProfit, usedPallets);

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    std::vector<int> bestSelection;
    int bestWeight = 0;
    int palletCount = 0;
    for (int i = 0; i < n; i++)
    {
        if (usedPallets[i])
        {
            bestSelection.push_back(pallets[i].id);
            bestWeight += pallets[i].weight;
            palletCount++;
        }
    }

    std::cout << "Backtracking found optimal solution with " << palletCount << " pallets for maximum profit of " << bestProfit << std::endl;

    solution.totalProfit = bestProfit;
    solution.totalWeight = bestWeight;
    solution.selectedPallets = bestSelection;
    solution.executionTime = duration.count();

    return solution;
}

void PalletPackingOptimizer::backtrack(
    const std::vector<Pallet> &pallets, int n,
    int curIndex, int maxWeight, int curProfit,
    std::vector<bool> &curPallets,
    int &maxProfit, std::vector<bool> &usedPallets)
{
    if (curIndex == n)
    {
        int currentPalletCount = 0;
        for (int i = 0; i < n; i++)
        {
            if (curPallets[i])
                currentPalletCount++;
        }

        int usedPalletCount = 0;
        for (int i = 0; i < n; i++)
        {
            if (usedPallets[i])
                usedPalletCount++;
        }

        if (curProfit > maxProfit || (curProfit == maxProfit && currentPalletCount < usedPalletCount))
        {
            maxProfit = curProfit;
            for (int i = 0; i < n; i++)
            {
                usedPallets[i] = curPallets[i];
            }
        }
        return;
    }

    if (maxWeight >= pallets[curIndex].weight)
    {
        curPallets[curIndex] = true;
        backtrack(pallets, n, curIndex + 1,
                  maxWeight - pallets[curIndex].weight,
                  curProfit + pallets[curIndex].profit,
                  curPallets, maxProfit, usedPallets);
        curPallets[curIndex] = false;
    }

    backtrack(pallets, n, curIndex + 1, maxWeight, curProfit,
              curPallets, maxProfit, usedPallets);
}
