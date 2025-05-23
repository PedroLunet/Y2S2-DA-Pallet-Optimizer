#ifndef PALLETPACKINGOPTIMIZER_H
#define PALLETPACKINGOPTIMIZER_H

#include "../data/DataManager.h"
#include <string>
#include <vector>
#include <chrono>
#include <set>
#include <sstream>

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

    /**
     * @brief Solves the pallet packing problem using dynamic programming approach
     * @return Solution structure containing the results
     * @time_complexity O(n*W) where n is the number of pallets and W is the weight capacity
     * @space_complexity O(n*W) for the DP table
     */
    Solution solveDynamicProgramming();

    /**
     * @brief Solves the pallet packing problem using a greedy approach based on profit-to-weight ratio
     * @return Solution structure containing the results
     * @time_complexity O(n log n) due to sorting
     * @space_complexity O(n) for storing the solution
     */
    Solution solveGreedyA();

    /**
     * @brief Solves the pallet packing problem using a greedy approach based on profit value
     * @return Solution structure containing the results
     * @time_complexity O(n log n) due to sorting
     * @space_complexity O(n) for storing the solution
     */
    Solution solveGreedyB();

    /**
     * @brief Solves the pallet packing problem using an approximation algorithm
     * that returns the maximum result of both greedy approaches
     * @return Solution structure containing the results
     * @time_complexity O(n log n) due to sorting
     * @space_complexity O(n) for storing the solution
     */
    Solution solveApproximation();

    /**
     * @brief Solves the pallet packing problem using Integer Linear Programming (ILP) with recursive approach
     * @return Solution structure containing the results
     * @time_complexity O(2^n) where n is the number of pallets
     * @space_complexity O(n) for recursion stack and storing the best solution
     */
    Solution solveILP();

    /**
     * @brief Solves the pallet packing problem using Integer Linear Programming (ILP) with Python PuLP
     * @return Solution structure containing the results
     * @time_complexity Depends on the ILP solver (typically exponential in worst case)
     * @space_complexity Depends on the ILP solver
     */
    Solution solveILPPython();

    /**
     * @brief Compares the approximation algorithm with optimal solutions
     * @param approximationSolution The solution from the approximation algorithm
     * @param optimalSolution The optimal solution (from DP or Brute Force)
     * @return A string with comparison metrics (accuracy, performance)
     */
    std::string compareWithOptimal(const Solution &approximationSolution, const Solution &optimalSolution);

    /**
     * @brief Exports performance data from multiple algorithm solutions to JSON format
     * @param solutions Vector of solutions from different algorithms
     * @param datasetName Name of the current dataset
     * @param filename Output filename for the JSON data
     * @return True if export was successful, false otherwise
     */
    bool exportPerformanceData(const std::vector<Solution> &solutions, const std::string &datasetName, const std::string &filename);

    /**
     * @brief Generates performance visualization graphs using Python script
     * @param datasetName Name of the dataset used for labeling
     * @return True if visualization generation was successful, false otherwise
     */
    bool generatePerformanceVisualization(const std::string &datasetName);

    /**
     * @brief Runs all algorithms and generates comprehensive performance analysis with visualizations
     * @return Vector of solutions from all algorithms
     */
    std::vector<Solution> runFullPerformanceAnalysis();

private:
    /**
     * @brief Helper function for the backtracking algorithm
     * @param pallets The list of pallets
     * @param n The number of pallets
     * @param curIndex The current pallet index being considered
     * @param maxWeight The remaining weight capacity
     * @param curProfit The current accumulated profit
     * @param curPallets Current selected pallets (boolean array)
     * @param maxProfit Reference to track the best profit found so far
     * @param usedPallets Reference to store the best selection found so far (boolean array)
     */
    void backtrack(const std::vector<Pallet> &pallets, int n,
                   int curIndex, int maxWeight, int curProfit,
                   std::vector<bool> &curPallets,
                   int &maxProfit, std::vector<bool> &usedPallets);
};

#endif // PALLETPACKINGOPTIMIZER_H
