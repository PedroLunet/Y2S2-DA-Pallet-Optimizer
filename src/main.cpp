#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

#include "menu/Menu.h"
#include "data/DataManager.h"

/**
 * @brief Main function to run the Pallet Packing Optimization Tool
 * @return 0 on successful execution
 */
int main()
{
    Menu menu;
    menu.credits();
    menu.mainMenu();

    DataManager::destroyInstance();

    return 0;
}
