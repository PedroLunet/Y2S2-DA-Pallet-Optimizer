#include "PalletPackingOptimizer.h"
#include <iostream>
#include <algorithm>
#include <bitset>

Solution PalletPackingOptimizer::solveBruteForce()
{
    Solution solution;
    solution.algorithmName = "Brute Force - O(2^n)";

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
    return solution;
}

Solution PalletPackingOptimizer::solveBacktracking()
{
    Solution solution;
    solution.algorithmName = "Backtracking - O(2^n)";

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
    solution.algorithmName = "Dynamic Programming - O(n*W)";

    const std::vector<Pallet> &pallets = getPallets();
    int capacity = getTruckCapacity();
    int n = pallets.size();

    auto startTime = std::chrono::high_resolution_clock::now();

    std::vector<std::vector<std::pair<int, int>>> dp(n, std::vector<std::pair<int, int>>(capacity + 1, {0, 0}));

    for (int w = 0; w <= capacity; w++)
    {
        if (w >= pallets[0].weight)
        {
            dp[0][w] = {pallets[0].profit, 1};
        }
        else
        {
            dp[0][w] = {0, 0};
        }
    }

    for (int i = 1; i < n; i++)
    {
        for (int w = 0; w <= capacity; w++)
        {
            if (pallets[i].weight > w)
            {
                dp[i][w] = dp[i - 1][w];
            }
            else
            {
                int newProfit = dp[i - 1][w - pallets[i].weight].first + pallets[i].profit;
                int newCount = dp[i - 1][w - pallets[i].weight].second + 1;

                int prevProfit = dp[i - 1][w].first;
                int prevCount = dp[i - 1][w].second;

                if (newProfit > prevProfit ||
                    (newProfit == prevProfit && newCount < prevCount))
                {
                    dp[i][w] = {newProfit, newCount};
                }
                else
                {
                    dp[i][w] = {prevProfit, prevCount};
                }
            }
        }
    }

    std::vector<bool> usedPallets(n, false);
    int remainingCapacity = capacity;

    int i = n - 1;
    int totalProfit = dp[i][remainingCapacity].first;
    int palletCount = dp[i][remainingCapacity].second;

    while (i >= 0 && remainingCapacity > 0)
    {
        if (i == 0)
        {
            if (remainingCapacity >= pallets[0].weight && dp[0][remainingCapacity].first > 0)
            {
                usedPallets[0] = true;
            }
            break;
        }

        if (dp[i][remainingCapacity].first != dp[i - 1][remainingCapacity].first ||
            (dp[i][remainingCapacity].first == dp[i - 1][remainingCapacity].first &&
             dp[i][remainingCapacity].second < dp[i - 1][remainingCapacity].second))
        {
            usedPallets[i] = true;
            remainingCapacity -= pallets[i].weight;
        }

        i--;
    }

    std::vector<int> selectedPalletIds;
    int totalWeight = 0;
    int actualPalletCount = 0;

    for (int i = 0; i < n; i++)
    {
        if (usedPallets[i])
        {
            selectedPalletIds.push_back(pallets[i].id);
            totalWeight += pallets[i].weight;
            actualPalletCount++;
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    solution.totalProfit = totalProfit;
    solution.totalWeight = totalWeight;
    solution.selectedPallets = selectedPalletIds;
    solution.executionTime = duration.count();

    return solution;
}

Solution PalletPackingOptimizer::solveGreedyA()
{
    Solution solution;
    solution.algorithmName = "Greedy-A (By Profit/Weight Ratio) - O(n log n)";

    const std::vector<Pallet> &pallets = getPallets();
    int capacity = getTruckCapacity();
    int n = pallets.size();

    auto startTime = std::chrono::high_resolution_clock::now();

    std::vector<std::pair<int, Pallet>> indexedPallets;
    for (int i = 0; i < n; i++)
    {
        indexedPallets.push_back({i, pallets[i]});
    }

    std::sort(indexedPallets.begin(), indexedPallets.end(),
              [](const std::pair<int, Pallet> &a, const std::pair<int, Pallet> &b)
              {
                  double ratioA = static_cast<double>(a.second.profit) / a.second.weight;
                  double ratioB = static_cast<double>(b.second.profit) / b.second.weight;
                  return ratioA > ratioB;
              });

    int totalWeight = 0;
    int totalProfit = 0;
    std::vector<int> selectedPalletIds;

    for (const auto &indexedPallet : indexedPallets)
    {
        const Pallet &pallet = indexedPallet.second;

        if (totalWeight + pallet.weight <= capacity)
        {
            totalWeight += pallet.weight;
            totalProfit += pallet.profit;
            selectedPalletIds.push_back(pallet.id);
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    solution.totalProfit = totalProfit;
    solution.totalWeight = totalWeight;
    solution.selectedPallets = selectedPalletIds;
    solution.executionTime = duration.count();

    return solution;
}

Solution PalletPackingOptimizer::solveGreedyB()
{
    Solution solution;
    solution.algorithmName = "Greedy-B (By Profit) - O(n log n)";

    const std::vector<Pallet> &pallets = getPallets();
    int capacity = getTruckCapacity();
    int n = pallets.size();

    auto startTime = std::chrono::high_resolution_clock::now();

    std::vector<std::pair<int, Pallet>> indexedPallets;
    for (int i = 0; i < n; i++)
    {
        indexedPallets.push_back({i, pallets[i]});
    }

    std::sort(indexedPallets.begin(), indexedPallets.end(),
              [](const std::pair<int, Pallet> &a, const std::pair<int, Pallet> &b)
              {
                  return a.second.profit > b.second.profit;
              });

    int totalWeight = 0;
    int totalProfit = 0;
    std::vector<int> selectedPalletIds;

    for (const auto &indexedPallet : indexedPallets)
    {
        const Pallet &pallet = indexedPallet.second;

        if (totalWeight + pallet.weight <= capacity)
        {
            totalWeight += pallet.weight;
            totalProfit += pallet.profit;
            selectedPalletIds.push_back(pallet.id);
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    solution.totalProfit = totalProfit;
    solution.totalWeight = totalWeight;
    solution.selectedPallets = selectedPalletIds;
    solution.executionTime = duration.count();

    return solution;
}

Solution PalletPackingOptimizer::solveApproximation()
{
    Solution solution;
    solution.algorithmName = "Approximation (Max of Greedy-A and Greedy-B)";

    auto startTime = std::chrono::high_resolution_clock::now();

    Solution greedyA = solveGreedyA();
    Solution greedyB = solveGreedyB();

    Solution &bestSolution = (greedyA.totalProfit >= greedyB.totalProfit) ? greedyA : greedyB;

    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    solution.totalProfit = bestSolution.totalProfit;
    solution.totalWeight = bestSolution.totalWeight;
    solution.selectedPallets = bestSolution.selectedPallets;
    solution.executionTime = duration.count();
    solution.algorithmName = "Approximation (Max of " +
                             std::string((bestSolution.totalProfit == greedyA.totalProfit) ? "Greedy-A" : "Greedy-B") +
                             ") - O(n log n)";

    return solution;
}

std::string PalletPackingOptimizer::compareWithOptimal(const Solution &approximationSolution, const Solution &optimalSolution)
{
    std::stringstream comparison;

    double profitAccuracy = (static_cast<double>(approximationSolution.totalProfit) / optimalSolution.totalProfit) * 100.0;
    double speedup = (static_cast<double>(optimalSolution.executionTime) / approximationSolution.executionTime);

    comparison << "Comparison with " << optimalSolution.algorithmName << ":\n";
    comparison << "Optimal profit: " << optimalSolution.totalProfit << "\n";
    comparison << "Approximation profit: " << approximationSolution.totalProfit << "\n";
    comparison << "Accuracy: " << profitAccuracy << "%\n";
    comparison << "Optimal execution time: " << optimalSolution.executionTime << " ms\n";
    comparison << "Approximation execution time: " << approximationSolution.executionTime << " ms\n";
    comparison << "Speedup: " << speedup << "x\n";

    std::set<int> optimalPallets(optimalSolution.selectedPallets.begin(), optimalSolution.selectedPallets.end());
    std::set<int> approxPallets(approximationSolution.selectedPallets.begin(), approximationSolution.selectedPallets.end());

    int commonPallets = 0;
    for (int id : approxPallets)
    {
        if (optimalPallets.count(id) > 0)
        {
            commonPallets++;
        }
    }

    double palletMatchPercentage = (static_cast<double>(commonPallets) / optimalPallets.size()) * 100.0;
    comparison << "Pallet selection match: " << palletMatchPercentage << "%\n";
    comparison << "Common pallets: " << commonPallets << " out of " << optimalPallets.size() << "\n";

    return comparison.str();
}
