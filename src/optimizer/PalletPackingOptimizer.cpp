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

    const int MAX_PALLETS = 30;
    if (n > MAX_PALLETS)
    {
        std::cout << "Warning: Dataset contains " << n << " pallets, which exceeds the maximum for brute force algorithm." << std::endl;
        std::cout << "This is not recommended and another algorithm is advised." << std::endl;
    }

    std::vector<bool> curCandidate(n, false);

    bool foundSolution = false;
    int bestProfit = 0;
    int bestWeight = 0;
    std::vector<bool> bestPalletSelection(n, false);
    long long totalCombinations = 0;

    while (true)
    {
        totalCombinations++;

        int currentWeight = 0;
        int currentProfit = 0;

        for (int i = 0; i < n; i++)
        {
            if (curCandidate[i])
            {
                currentWeight += pallets[i].weight;
                currentProfit += pallets[i].profit;
            }
        }

        if (currentWeight <= capacity)
        {
            if (!foundSolution || currentProfit > bestProfit)
            {
                foundSolution = true;
                bestProfit = currentProfit;
                bestWeight = currentWeight;
                bestPalletSelection = curCandidate;
            }
        }

        int curIndex = 0;
        while (curIndex < n && curCandidate[curIndex])
        {
            curIndex++;
        }

        if (curIndex == n)
            break;

        for (int i = 0; i < curIndex; i++)
        {
            curCandidate[i] = false;
        }
        curCandidate[curIndex] = true;
    }

    std::vector<int> selectedPalletIds;
    for (int i = 0; i < n; i++)
    {
        if (bestPalletSelection[i])
        {
            selectedPalletIds.push_back(pallets[i].id);
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    solution.totalProfit = bestProfit;
    solution.totalWeight = bestWeight;
    solution.selectedPallets = selectedPalletIds;
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

Solution PalletPackingOptimizer::solveDynamicProgramming()
{
    Solution solution;
    solution.algorithmName = "Dynamic Programming";

    const std::vector<Pallet> &pallets = getPallets();
    int capacity = getTruckCapacity();
    int n = pallets.size();

    auto startTime = std::chrono::high_resolution_clock::now();

    std::vector<std::vector<int>> maxValue(n, std::vector<int>(capacity + 1, 0));

    for (int w = 0; w <= capacity; w++)
    {
        if (w >= pallets[0].weight)
        {
            maxValue[0][w] = pallets[0].profit;
        }
        else
        {
            maxValue[0][w] = 0;
        }
    }

    for (int i = 1; i < n; i++)
    {
        for (int w = 0; w <= capacity; w++)
        {
            if (pallets[i].weight > w)
            {
                maxValue[i][w] = maxValue[i - 1][w];
            }
            else
            {
                int valueWithCurrentPallet = maxValue[i - 1][w - pallets[i].weight] + pallets[i].profit;
                int valueWithoutCurrentPallet = maxValue[i - 1][w];
                maxValue[i][w] = std::max(valueWithCurrentPallet, valueWithoutCurrentPallet);
            }
        }
    }

    std::vector<bool> usedPallets(n, false);
    int remainingCapacity = capacity;

    for (int i = n - 1; i > 0; i--)
    {
        if (maxValue[i][remainingCapacity] != maxValue[i - 1][remainingCapacity])
        {
            usedPallets[i] = true;
            remainingCapacity -= pallets[i].weight;
        }
    }

    if (remainingCapacity >= pallets[0].weight && maxValue[0][remainingCapacity] == pallets[0].profit)
    {
        usedPallets[0] = true;
    }

    std::vector<int> selectedPalletIds;
    int totalWeight = 0;
    int totalProfit = 0;

    for (int i = 0; i < n; i++)
    {
        if (usedPallets[i])
        {
            selectedPalletIds.push_back(pallets[i].id);
            totalWeight += pallets[i].weight;
            totalProfit += pallets[i].profit;
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    solution.totalProfit = totalProfit;
    solution.totalWeight = totalWeight;
    solution.selectedPallets = selectedPalletIds;
    solution.executionTime = duration.count();

    std::cout << "Dynamic Programming Analysis:" << std::endl;
    std::cout << "Time complexity: O(n*W) where n = " << n << " and W = " << capacity << std::endl;
    std::cout << "Space complexity: O(n*W) = " << n << "*" << capacity << " = " << n * capacity << std::endl;
    std::cout << "Optimal profit: " << totalProfit << " with " << selectedPalletIds.size() << " pallets" << std::endl;

    return solution;
}
