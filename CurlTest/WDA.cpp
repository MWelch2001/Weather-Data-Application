#include "WDA.h"
using namespace Util;

bool ExitProgram()
{
    std::string input;
    system("CLS");
    std::cout << "Are you sure you want to leave? (Y/N)" << std::endl;
    std::cin >> input;
    if (input == "y" || input == "Y")
    {
        return true;
    }
    return false;
}

int main(){
    LocationManager locManager = LocationManager();
    bool exit = false;
    Menu mainMenu = Menu(0);
    SearchWeatherData dataSearch = SearchWeatherData();
    while (!exit){
        switch (mainMenu.RunMenu()) {
        case 1:
            locManager.ManageLocations();
            break;
        case 2:  
            //gets locations straight from location manager here to avoid a connection between SearchWeatherData and LocationManager
            dataSearch.SetSearchLocations(locManager.GetLocations());
            dataSearch.SearchWeather();
            Pause();
            break;
        case 3:
            exit = ExitProgram();
            break;
        }
    }  
}