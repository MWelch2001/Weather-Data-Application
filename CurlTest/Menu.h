#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>

class Menu {
public:
    Menu(int menuNumber); // Constructor to load menu based on menu number
    int RunMenu();

private:
    void DisplayMenu();
    std::vector<std::string> menuItems;
    void LoadMenuFromFile(const std::string& filename);
    int CheckInput();
};

#endif // MENU_H
