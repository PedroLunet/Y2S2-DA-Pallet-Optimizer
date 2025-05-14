#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include <cmath>
#include <unordered_map>

/**
 * @brief Structure to represent a Pallet with its properties
 */
struct Pallet {
    int id;      ///< Unique identifier for the pallet
    int weight;  ///< Weight of the pallet
    int profit;  ///< Profit value of the pallet
};

/**
 * @brief Structure to represent a solution to the knapsack problem
 */
struct Solution {
    std::vector<int> selectedPallets; ///< IDs of selected pallets
    int totalWeight;                 ///< Total weight of selected pallets
    int totalProfit;                 ///< Total profit of selected pallets
    double executionTime;            ///< Execution time in milliseconds
    std::string algorithmName;       ///< Name of the algorithm used
};

/**
 * @brief Class to handle the Pallet Packing Optimization Problem
 */
class PalletPackingOptimizer {
private:
    int truckCapacity;              ///< Maximum weight capacity of the truck
    std::vector<Pallet> pallets;    ///< List of available pallets
    std::string currentDataset;     ///< Name of the currently loaded dataset
    
    /**
     * @brief Reads the truck capacity and number of pallets from the file
     * @param filename The path to the TruckAndPallets file
     * @return True if the file was read successfully, false otherwise
     * @time_complexity O(1) - Reads only a single line from the file
     * @space_complexity O(1) - Uses a fixed amount of memory
     */
    bool readTruckData(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return false;
        }
        
        std::string line;
        // Skip header line
        std::getline(file, line);
        
        // Read capacity and number of pallets
        std::getline(file, line);
        std::stringstream ss(line);
        std::string capacityStr, palletsCountStr;
        
        std::getline(ss, capacityStr, ',');
        std::getline(ss, palletsCountStr, ',');
        
        truckCapacity = std::stoi(capacityStr);
        int palletsCount = std::stoi(palletsCountStr);
        
        file.close();
        return true;
    }
    
    /**
     * @brief Reads the pallet data from the file
     * @param filename The path to the Pallets file
     * @return True if the file was read successfully, false otherwise
     * @time_complexity O(n) where n is the number of pallets
     * @space_complexity O(n) where n is the number of pallets
     */
    bool readPalletsData(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return false;
        }
        
        pallets.clear();
        std::string line;
        // Skip header line
        std::getline(file, line);
        
        // Read each pallet data
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string idStr, weightStr, profitStr;
            
            std::getline(ss, idStr, ',');
            std::getline(ss, weightStr, ',');
            std::getline(ss, profitStr, ',');
            
            Pallet pallet;
            pallet.id = std::stoi(idStr);
            pallet.weight = std::stoi(weightStr);
            pallet.profit = std::stoi(profitStr);
            
            pallets.push_back(pallet);
        }
        
        file.close();
        return true;
    }

public:
    PalletPackingOptimizer() : truckCapacity(0), currentDataset("") {}
    
    /**
     * @brief Loads a dataset from the specified files
     * @param datasetNumber The dataset number to load (e.g., 01, 02)
     * @return True if the dataset was loaded successfully, false otherwise
     * @time_complexity O(n) where n is the number of pallets
     * @space_complexity O(n) where n is the number of pallets
     */
    bool loadDataset(const std::string& datasetNumber) {
        std::string truckFileName = "datasets/TruckAndPallets_" + datasetNumber + ".csv";
        std::string palletsFileName = "datasets/Pallets_" + datasetNumber + ".csv";
        
        if (!readTruckData(truckFileName)) {
            return false;
        }
        
        if (!readPalletsData(palletsFileName)) {
            return false;
        }
        
        currentDataset = datasetNumber;
        
        // Print a summary of the loaded data
        std::cout << "\n--- Dataset " << datasetNumber << " Summary ---" << std::endl;
        std::cout << "Truck Capacity: " << truckCapacity << std::endl;
        std::cout << "Number of Pallets: " << pallets.size() << std::endl;
        std::cout << "First few pallets:" << std::endl;
        
        // Print the first few pallets (up to 5)
        int count = 0;
        std::cout << std::left << std::setw(10) << "ID" 
                  << std::setw(10) << "Weight" 
                  << std::setw(10) << "Profit" << std::endl;
        std::cout << std::string(30, '-') << std::endl;
        
        for (const auto& pallet : pallets) {
            if (count >= 5) break; // Only show the first 5 pallets
            std::cout << std::left << std::setw(10) << pallet.id 
                      << std::setw(10) << pallet.weight 
                      << std::setw(10) << pallet.profit << std::endl;
            count++;
        }
        
        if (pallets.size() > 5) {
            std::cout << "... and " << pallets.size() - 5 << " more pallets" << std::endl;
        }
        
        return true;
    }
    
    /**
     * @brief Gets the list of available pallets
     * @return The list of available pallets
     */
    const std::vector<Pallet>& getPallets() const {
        return pallets;
    }
    
    /**
     * @brief Gets the truck capacity
     * @return The truck capacity
     */
    int getTruckCapacity() const {
        return truckCapacity;
    }
    
    /**
     * @brief Gets the name of the currently loaded dataset
     * @return The name of the currently loaded dataset
     */
    std::string getCurrentDataset() const {
        return currentDataset;
    }
    
    /**
     * @brief Displays information about the currently loaded dataset
     * @time_complexity O(n) where n is the number of pallets
     * @space_complexity O(1) - Uses a fixed amount of memory
     */
    void displayDatasetInfo() const {
        if (currentDataset.empty()) {
            std::cout << "No dataset loaded." << std::endl;
            return;
        }
        
        std::cout << "Dataset: " << currentDataset << std::endl;
        std::cout << "Truck Capacity: " << truckCapacity << std::endl;
        std::cout << "Number of Pallets: " << pallets.size() << std::endl;
        
        std::cout << "\nPallets Information:" << std::endl;
        std::cout << std::left << std::setw(10) << "ID"
                  << std::setw(10) << "Weight"
                  << std::setw(10) << "Profit"
                  << std::setw(15) << "Profit/Weight" << std::endl;
        std::cout << std::string(45, '-') << std::endl;
        
        for (const auto& pallet : pallets) {
            double ratio = static_cast<double>(pallet.profit) / pallet.weight;
            std::cout << std::left << std::setw(10) << pallet.id
                      << std::setw(10) << pallet.weight
                      << std::setw(10) << pallet.profit
                      << std::setw(15) << std::fixed << std::setprecision(4) << ratio << std::endl;
        }
    }
    
    // Algorithm implementations will be added in future tasks
    
    // T2.1: Exhaustive (Brute-Force) Approach
    // T2.2: Dynamic Programming Approach
    // T2.3: Approximation Algorithms (Greedy Approach)
    // T2.4: Integer Linear Programming Algorithm
};

/**
 * @brief Displays the solution to the knapsack problem
 * @param solution The solution to display
 */
void displaySolution(const Solution& solution) {
    std::cout << "\nAlgorithm: " << solution.algorithmName << std::endl;
    std::cout << "Execution Time: " << solution.executionTime << " ms" << std::endl;
    std::cout << "Total Profit: " << solution.totalProfit << std::endl;
    std::cout << "Total Weight: " << solution.totalWeight << std::endl;
    
    std::cout << "Selected Pallets: ";
    for (size_t i = 0; i < solution.selectedPallets.size(); ++i) {
        std::cout << solution.selectedPallets[i];
        if (i < solution.selectedPallets.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

/**
 * @brief Main function to run the Pallet Packing Optimization Tool
 * @return 0 on successful execution
 */
int main() {
    PalletPackingOptimizer optimizer;
    int choice;
    std::string datasetNumber;
    
    while (true) {
        std::cout << "\n==== Pallet Packing Optimization Tool ====" << std::endl;
        std::cout << "1. Load Dataset" << std::endl;
        std::cout << "2. Display Dataset Information" << std::endl;
        std::cout << "3. Solve using Brute Force (Exhaustive Search)" << std::endl;
        std::cout << "4. Solve using Dynamic Programming" << std::endl;
        std::cout << "5. Solve using Greedy Approximation" << std::endl;
        std::cout << "6. Solve using Integer Linear Programming" << std::endl;
        std::cout << "7. Compare All Algorithms" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                std::cout << "Enter dataset number (e.g., 01, 02): ";
                std::cin >> datasetNumber;
                if (optimizer.loadDataset(datasetNumber)) {
                    std::cout << "Dataset " << datasetNumber << " loaded successfully." << std::endl;
                } else {
                    std::cout << "Failed to load dataset " << datasetNumber << "." << std::endl;
                }
                break;
                
            case 2:
                optimizer.displayDatasetInfo();
                break;
                
            case 3:
                std::cout << "Brute Force algorithm not implemented yet." << std::endl;
                // Will be implemented in T2.1
                break;
                
            case 4:
                std::cout << "Dynamic Programming algorithm not implemented yet." << std::endl;
                // Will be implemented in T2.2
                break;
                
            case 5:
                std::cout << "Greedy Approximation algorithm not implemented yet." << std::endl;
                // Will be implemented in T2.3
                break;
                
            case 6:
                std::cout << "Integer Linear Programming algorithm not implemented yet." << std::endl;
                // Will be implemented in T2.4
                break;
                
            case 7:
                std::cout << "Algorithm comparison not implemented yet." << std::endl;
                // Will be implemented after all algorithms are completed
                break;
                
            case 0:
                std::cout << "Exiting the program. Goodbye!" << std::endl;
                return 0;
                
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
    
    return 0;
}
