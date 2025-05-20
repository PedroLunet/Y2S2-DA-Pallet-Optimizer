#ifndef MENU_H
#define MENU_H

#include "../optimizer/PalletPackingOptimizer.h"
#include <string>

class Menu
{
    void optionPicker();
    PalletPackingOptimizer optimizer;
    std::string datasetNumber;

    /**
     * @brief Displays the solution to the knapsack problem
     * @param solution The solution to display
     */
    void displaySolution(const Solution &solution);

public:
    Menu();

    static void credits();

    void mainMenu();
};

#endif // MENU_H
