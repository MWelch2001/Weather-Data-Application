#include "Menu.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>

Menu::Menu(int menuIndex) {
    std::string filename;
    switch (menuIndex) {
    case 0:
        filename = "MainMenu.txt";
        break;
    case 1:
        filename = "ManageLocation.txt";
        break;
    case 2:
        filename = "SearchWeatherData.txt";
        break;
    }
    LoadMenuFromFile(filename);
}

void Menu::LoadMenuFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    menuItems.clear();
    std::string line;
    while (std::getline(file, line)) {
        menuItems.push_back(line);
    }

    file.close();
}

void Menu::DisplayMenu() {
    std::cout << "Enter the number of the option you wish to select" << std::endl;
    for (const auto& menuItem : menuItems) {
        std::cout << menuItem << std::endl;
    }
}

int Menu::CheckInput()
{
    int input;
    std::cin >> input;
    while (1)
    {
        if (std::cin.fail() || input > menuItems.size() || input < 0)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input, please try again" << std::endl;
            std::cin >> input;
        }
        if (!std::cin.fail())
            break;
    }
    return input;
}


int Menu::RunMenu()
{ 
    system("CLS");
    DisplayMenu();
    return CheckInput();
}