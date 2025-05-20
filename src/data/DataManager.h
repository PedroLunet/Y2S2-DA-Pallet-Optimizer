#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <string>
#include <vector>

/**
 * @brief Structure to represent a Pallet with its properties
 */
struct Pallet
{
    int id;     ///< Unique identifier for the pallet
    int weight; ///< Weight of the pallet
    int profit; ///< Profit value of the pallet
};

/**
 * @brief Singleton class to handle loading and managing pallet data from files
 *
 * This class follows the singleton design pattern to ensure that only one
 * instance of the data handler exists, maintaining a single copy of the dataset
 * throughout the application.
 */
class DataManager
{
private:
    // Singleton instance
    static DataManager *instance;

    // Private constructor to prevent direct instantiation
    DataManager() : truckCapacity(0), currentDataset("") {}

    // Private copy constructor and assignment operator to prevent duplication
    DataManager(const DataManager &) = delete;
    DataManager &operator=(const DataManager &) = delete;

    int truckCapacity;           ///< Maximum weight capacity of the truck
    std::vector<Pallet> pallets; ///< List of available pallets
    std::string currentDataset;  ///< Name of the currently loaded dataset

    /**
     * @brief Reads the truck capacity and number of pallets from the file
     * @param filename The path to the TruckAndPallets file
     * @return True if the file was read successfully, false otherwise
     * @time_complexity O(1) - Reads only a single line from the file
     * @space_complexity O(1) - Uses a fixed amount of memory
     */
    bool readTruckData(const std::string &filename);

    /**
     * @brief Reads the pallet data from the file
     * @param filename The path to the Pallets file
     * @return True if the file was read successfully, false otherwise
     * @time_complexity O(n) where n is the number of pallets
     * @space_complexity O(n) where n is the number of pallets
     */
    bool readPalletsData(const std::string &filename);

public:
    /**
     * @brief Destructor
     */
    ~DataManager() {}

    /**
     * @brief Gets the singleton instance of the DataHandler
     * @return The singleton instance
     */
    static DataManager *getInstance()
    {
        if (!instance)
        {
            instance = new DataManager();
        }
        return instance;
    }

    /**
     * @brief Destroys the singleton instance
     */
    static void destroyInstance()
    {
        if (instance)
        {
            delete instance;
            instance = nullptr;
        }
    }

    /**
     * @brief Loads a dataset from the specified files
     * @param datasetNumber The dataset number to load (e.g., 01, 02)
     * @return True if the dataset was loaded successfully, false otherwise
     * @time_complexity O(n) where n is the number of pallets
     * @space_complexity O(n) where n is the number of pallets
     */
    bool loadDataset(const std::string &datasetNumber);

    /**
     * @brief Gets the list of available pallets
     * @return The list of available pallets
     */
    const std::vector<Pallet> &getPallets() const
    {
        return pallets;
    }

    /**
     * @brief Gets the truck capacity
     * @return The truck capacity
     */
    int getTruckCapacity() const
    {
        return truckCapacity;
    }

    /**
     * @brief Gets the name of the currently loaded dataset
     * @return The name of the currently loaded dataset
     */
    std::string getCurrentDataset() const
    {
        return currentDataset;
    }

    /**
     * @brief Displays information about the currently loaded dataset
     * @time_complexity O(n) where n is the number of pallets
     * @space_complexity O(1) - Uses a fixed amount of memory
     */
    void displayDatasetInfo() const;
};

#endif // DATAHANDLER_H
