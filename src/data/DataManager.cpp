#include "DataManager.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

// Initialize static instance pointer
DataManager *DataManager::instance = nullptr;

bool DataManager::readTruckData(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
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

    // Return to main menu after processing any option (except exit)
    std::getline(ss, capacityStr, ',');
    std::getline(ss, palletsCountStr, ',');

    truckCapacity = std::stoi(capacityStr);
    int palletsCount = std::stoi(palletsCountStr);

    file.close();
    return true;
}

bool DataManager::readPalletsData(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    pallets.clear();
    std::string line;
    // Skip header line
    std::getline(file, line);

    // Read each pallet data
    while (std::getline(file, line))
    {
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

bool DataManager::loadDataset(const std::string &datasetNumber)
{
    std::string truckFileName = "../../datasets/TruckAndPallets_" + datasetNumber + ".csv";
    std::string palletsFileName = "../../datasets/Pallets_" + datasetNumber + ".csv";

    if (!readTruckData(truckFileName))
    {
        return false;
    }

    if (!readPalletsData(palletsFileName))
    {
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

    for (const auto &pallet : pallets)
    {
        if (count >= 5)
            break; // Only show the first 5 pallets
        std::cout << std::left << std::setw(10) << pallet.id
                  << std::setw(10) << pallet.weight
                  << std::setw(10) << pallet.profit << std::endl;
        count++;
    }

    if (pallets.size() > 5)
    {
        std::cout << "... and " << pallets.size() - 5 << " more pallets" << std::endl;
    }

    return true;
}

void DataManager::displayDatasetInfo() const
{
    if (currentDataset.empty())
    {
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

    for (const auto &pallet : pallets)
    {
        double ratio = static_cast<double>(pallet.profit) / pallet.weight;
        std::cout << std::left << std::setw(10) << pallet.id
                  << std::setw(10) << pallet.weight
                  << std::setw(10) << pallet.profit
                  << std::setw(15) << std::fixed << std::setprecision(4) << ratio << std::endl;
    }
}
