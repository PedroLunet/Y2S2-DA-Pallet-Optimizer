#ifndef MENU_H
#define MENU_H

#include "../optimizer/PalletPackingOptimizer.h"
#include <string>

class Menu
{
    void optionPicker();
    PalletPackingOptimizer optimizer;
    std::string datasetNumber;

public:
    Menu();

    static void credits();

    void mainMenu();
};

#endif // MENU_H
