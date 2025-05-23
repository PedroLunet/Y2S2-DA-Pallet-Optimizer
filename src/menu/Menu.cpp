#include "Menu.h"

#include <iostream>
#include <limits>
#include <thread>
#include <iomanip>

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
    std::cout << "8. Full Performance Analysis with Visualization" << std::endl;
    std::cout << "9. Generate Performance Graphs" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "10. Exit" << std::endl;
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
        std::cout << "\nSolving using Brute Force...\n"
                  << std::endl;
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
    {
        if (optimizer.getCurrentDataset().empty())
        {
            std::cerr << "\nPlease load a dataset first." << std::endl;
            break;
        }
        std::cout << "\nSolving using Dynamic Programming...\n"
                  << std::endl;
        Solution solution = optimizer.solveDynamicProgramming();
        displaySolution(solution);
    }
    break;

    case 5:
    {
        if (optimizer.getCurrentDataset().empty())
        {
            std::cerr << "\nPlease load a dataset first." << std::endl;
            break;
        }

        int subOption;
        std::cout << "\nSelect approximation algorithm:" << std::endl;
        std::cout << "1. Greedy-A (by Profit/Weight Ratio)" << std::endl;
        std::cout << "2. Greedy-B (by Profit Value)" << std::endl;
        std::cout << "3. Combined Approximation (Max of both)" << std::endl;
        std::cout << "4. Compare with Optimal Solution" << std::endl;
        std::cout << "Option: ";

        std::cin >> subOption;

        switch (subOption)
        {
        case 1:
            std::cout << "\nSolving using Greedy-A (Profit/Weight Ratio)...\n"
                      << std::endl;
            displaySolution(optimizer.solveGreedyA());
            break;

        case 2:
            std::cout << "\nSolving using Greedy-B (Profit Value)...\n"
                      << std::endl;
            displaySolution(optimizer.solveGreedyB());
            break;

        case 3:
            std::cout << "\nSolving using Combined Approximation...\n"
                      << std::endl;
            displaySolution(optimizer.solveApproximation());
            break;

        case 4:
        {
            std::cout << "\nComparing approximation with optimal solution...\n"
                      << std::endl;

            if (optimizer.getPallets().size() > 30)
            {
                std::cout << "Using Dynamic Programming for optimal solution...\n"
                          << std::endl;
                Solution optimalSolution = optimizer.solveDynamicProgramming();
                Solution approxSolution = optimizer.solveApproximation();

                displaySolution(optimalSolution);
                std::cout << "\n";
                displaySolution(approxSolution);

                std::cout << "\nComparison Results:\n"
                          << std::endl;
                std::cout << optimizer.compareWithOptimal(approxSolution, optimalSolution) << std::endl;
            }
            else
            {
                std::cout << "Using Exact algorithms for optimal solutions...\n"
                          << std::endl;

                Solution optimalSolution = optimizer.solveBacktracking();
                Solution approxSolution = optimizer.solveApproximation();
                Solution greedyASolution = optimizer.solveGreedyA();
                Solution greedyBSolution = optimizer.solveGreedyB();

                displaySolution(optimalSolution);
                std::cout << "\n";

                std::cout << "Comparison for Greedy-A:\n";
                std::cout << optimizer.compareWithOptimal(greedyASolution, optimalSolution) << std::endl;

                std::cout << "Comparison for Greedy-B:\n";
                std::cout << optimizer.compareWithOptimal(greedyBSolution, optimalSolution) << std::endl;

                std::cout << "Comparison for Combined Approximation:\n";
                std::cout << optimizer.compareWithOptimal(approxSolution, optimalSolution) << std::endl;
            }
            break;
        }

        default:
            std::cout << "Invalid option." << std::endl;
        }
    }
    break;

    case 6:
    {
        if (optimizer.getCurrentDataset().empty())
        {
            std::cerr << "\nPlease load a dataset first." << std::endl;
            break;
        }

        int subOption;
        std::cout << "\nSelect ILP method:" << std::endl;
        std::cout << "1. ILP (Recursive Implementation)" << std::endl;
        std::cout << "2. ILP (Python PuLP)" << std::endl;
        std::cout << "Option: ";

        std::cin >> subOption;

        switch (subOption)
        {
        case 1:
            std::cout << "\nSolving using Integer Linear Programming (Recursive)...\n" << std::endl;
            displaySolution(optimizer.solveILP());
            break;

        case 2:
            std::cout << "\nSolving using Integer Linear Programming (Python PuLP)...\n" << std::endl;
            displaySolution(optimizer.solveILPPython());
            break;

        default:
            std::cout << "Invalid option." << std::endl;
        }
    }
    break;

    case 7:
    {
        if (optimizer.getCurrentDataset().empty())
        {
            std::cerr << "\nPlease load a dataset first." << std::endl;
            break;
        }

        std::cout << "\nComparing all algorithms...\n"
                  << std::endl;

        Solution dpSolution, greedyA, greedyB, approx, ilpSolution, ilpPythonSolution;
        bool useExact = optimizer.getPallets().size() <= 30;
        Solution exactSolution;

        std::cout << "Running Dynamic Programming algorithm..." << std::endl;
        dpSolution = optimizer.solveDynamicProgramming();

        if (useExact)
        {
            std::cout << "Running Backtracking algorithm..." << std::endl;
            exactSolution = optimizer.solveBacktracking();
        }

        std::cout << "Running Greedy-A algorithm..." << std::endl;
        greedyA = optimizer.solveGreedyA();

        std::cout << "Running Greedy-B algorithm..." << std::endl;
        greedyB = optimizer.solveGreedyB();

        std::cout << "Running Approximation algorithm..." << std::endl;
        approx = optimizer.solveApproximation();

        std::cout << "Running ILP (Recursive) algorithm..." << std::endl;
        ilpSolution = optimizer.solveILP();

        std::cout << "Running ILP (Python) algorithm..." << std::endl;
        ilpPythonSolution = optimizer.solveILPPython();

        std::cout << "\n============================================= Algorithm Comparison =============================================" << std::endl;
        std::cout << std::left << std::setw(50) << "Algorithm"
                  << std::setw(15) << "Total Profit"
                  << std::setw(15) << "Total Weight"
                  << std::setw(20) << "Execution Time (ms)"
                  << std::setw(15) << "Pallets Used" << std::endl;
        std::cout << "----------------------------------------------------------------------------------------------------------------" << std::endl;

        if (useExact)
        {
            std::cout << std::left << std::setw(50) << exactSolution.algorithmName
                      << std::setw(15) << exactSolution.totalProfit
                      << std::setw(15) << exactSolution.totalWeight
                      << std::setw(20) << exactSolution.executionTime
                      << std::setw(15) << exactSolution.selectedPallets.size() << std::endl;
        }

        std::cout << std::left << std::setw(50) << dpSolution.algorithmName
                  << std::setw(15) << dpSolution.totalProfit
                  << std::setw(15) << dpSolution.totalWeight
                  << std::setw(20) << dpSolution.executionTime
                  << std::setw(15) << dpSolution.selectedPallets.size() << std::endl;

        std::cout << std::left << std::setw(50) << greedyA.algorithmName
                  << std::setw(15) << greedyA.totalProfit
                  << std::setw(15) << greedyA.totalWeight
                  << std::setw(20) << greedyA.executionTime
                  << std::setw(15) << greedyA.selectedPallets.size() << std::endl;

        std::cout << std::left << std::setw(50) << greedyB.algorithmName
                  << std::setw(15) << greedyB.totalProfit
                  << std::setw(15) << greedyB.totalWeight
                  << std::setw(20) << greedyB.executionTime
                  << std::setw(15) << greedyB.selectedPallets.size() << std::endl;

        std::cout << std::left << std::setw(50) << approx.algorithmName
                  << std::setw(15) << approx.totalProfit
                  << std::setw(15) << approx.totalWeight
                  << std::setw(20) << approx.executionTime
                  << std::setw(15) << approx.selectedPallets.size() << std::endl;

        std::cout << std::left << std::setw(50) << ilpSolution.algorithmName
                  << std::setw(15) << ilpSolution.totalProfit
                  << std::setw(15) << ilpSolution.totalWeight
                  << std::setw(20) << ilpSolution.executionTime
                  << std::setw(15) << ilpSolution.selectedPallets.size() << std::endl;

        std::cout << std::left << std::setw(50) << ilpPythonSolution.algorithmName
                  << std::setw(15) << ilpPythonSolution.totalProfit
                  << std::setw(15) << ilpPythonSolution.totalWeight
                  << std::setw(20) << ilpPythonSolution.executionTime
                  << std::setw(15) << ilpPythonSolution.selectedPallets.size() << std::endl;

        std::cout << "================================================================================================================" << std::endl;

        Solution &optimalSolution = useExact ? exactSolution : dpSolution;
        std::cout << "\n================== Approximation Accuracy =================" << std::endl;

        double greedyAAccuracy = static_cast<double>(greedyA.totalProfit) / optimalSolution.totalProfit * 100.0;
        double greedyBAccuracy = static_cast<double>(greedyB.totalProfit) / optimalSolution.totalProfit * 100.0;
        double approxAccuracy = static_cast<double>(approx.totalProfit) / optimalSolution.totalProfit * 100.0;
        double ilpAccuracy = static_cast<double>(ilpSolution.totalProfit) / optimalSolution.totalProfit * 100.0;
        double ilpPythonAccuracy = static_cast<double>(ilpPythonSolution.totalProfit) / optimalSolution.totalProfit * 100.0;

        std::cout << "Greedy-A accuracy: " << greedyAAccuracy << "%" << std::endl;
        std::cout << "Greedy-B accuracy: " << greedyBAccuracy << "%" << std::endl;
        std::cout << "Approximation accuracy: " << approxAccuracy << "%" << std::endl;
        std::cout << "ILP (Recursive) accuracy: " << ilpAccuracy << "%" << std::endl;
        std::cout << "ILP (Python) accuracy: " << ilpPythonAccuracy << "%" << std::endl;

        std::cout << "===========================================================" << std::endl;
    }
    break;

    case 8:
    {
        if (optimizer.getCurrentDataset().empty())
        {
            std::cerr << "\nPlease load a dataset first." << std::endl;
            break;
        }

        std::cout << "\nRunning Full Performance Analysis with Visualization...\n" << std::endl;
        
        std::vector<Solution> solutions = optimizer.runFullPerformanceAnalysis();
        
        if (!solutions.empty())
        {
            // Display summary table
            std::cout << "\n============================================= Performance Summary =============================================" << std::endl;
            std::cout << std::left << std::setw(50) << "Algorithm"
                      << std::setw(15) << "Total Profit"
                      << std::setw(15) << "Total Weight"
                      << std::setw(20) << "Execution Time (ms)"
                      << std::setw(15) << "Pallets Used" << std::endl;
            std::cout << "----------------------------------------------------------------------------------------------------------------" << std::endl;

            for (const auto &sol : solutions)
            {
                std::cout << std::left << std::setw(50) << sol.algorithmName
                          << std::setw(15) << sol.totalProfit
                          << std::setw(15) << sol.totalWeight
                          << std::setw(20) << sol.executionTime
                          << std::setw(15) << sol.selectedPallets.size() << std::endl;
            }
            std::cout << "================================================================================================================" << std::endl;

            // Generate visualizations
            std::cout << "\nGenerating performance visualizations..." << std::endl;
            bool success = optimizer.generatePerformanceVisualization(datasetNumber);
            
            if (success)
            {
                std::cout << "\n✓ Performance analysis and visualization completed successfully!" << std::endl;
                std::cout << "Check the 'performance_graphs' directory for generated charts." << std::endl;
            }
            else
            {
                std::cout << "\n⚠ Performance analysis completed, but visualization generation failed." << std::endl;
                std::cout << "Performance data has been exported to JSON format." << std::endl;
            }
        }
    }
    break;

    case 9:
    {
        if (optimizer.getCurrentDataset().empty())
        {
            std::cerr << "\nPlease load a dataset first." << std::endl;
            break;
        }

        std::cout << "\nGenerating performance graphs for Dataset " << datasetNumber << "...\n" << std::endl;
        
        bool success = optimizer.generatePerformanceVisualization(datasetNumber);
        
        if (success)
        {
            std::cout << "\n✓ Performance visualizations generated successfully!" << std::endl;
            std::cout << "Check the 'performance_graphs' directory for charts." << std::endl;
        }
        else
        {
            std::cout << "\n⚠ Failed to generate visualizations." << std::endl;
            std::cout << "Make sure you have run the performance analysis first (option 8)" << std::endl;
            std::cout << "and that Python3 with matplotlib is installed." << std::endl;
        }
    }
    break;

    case 10:
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

    const std::chrono::seconds dura(1);

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

    std::cout << "Selected Pallets:" << std::endl;

    const std::vector<Pallet> &pallets = optimizer.getPallets();

    for (const int &palletId : solution.selectedPallets)
    {
        for (const auto &pallet : pallets)
        {
            if (pallet.id == palletId)
            {
                std::cout << palletId << ", " << pallet.weight << ", " << pallet.profit << std::endl;
                break;
            }
        }
    }
    std::cout << "==============================" << std::endl;
}
