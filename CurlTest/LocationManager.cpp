#include "LocationManager.h"


LocationManager::LocationManager() 
{
    locations = locFileHandler.LoadLocationsFromFile(idCounter);
}

//Used by WDA to avoid an extra association between this class and SearchWeatherData
std::unordered_map<int, Location> LocationManager::GetLocations()
{
    return locations;
}

void LocationManager::ModifyLocationData() 
{
    system("CLS");
    system("CLS");
    int input;
    std::cout << "Please enter the ID of the location that you wish to edit:" << std::endl;
    input = ValidateIntInput(1, locations.size());
    auto it = locations.find(input);
    system("CLS");
    if (it != locations.end())
    {
        std::cout << "the current longitude is " << it->second.GetLongitude() << " please enter the new longitude" << std::endl;
        float newLongitude = ValidateFloatInput(-180, 180);
        std::cout << "the current latitude is " << it->second.GetLatitude() << " please enter the new latitude" << std::endl;
        float newLatitude = ValidateFloatInput(-90, 90);
        it->second.SetLongitude(newLongitude);
        it->second.SetLatitude(newLatitude);
        locFileHandler.SaveLocationsToFile(locations);
        std::cout << "Location " << input << " has been changed" << std::endl;
    }
    else
    {
        std::cout << "Location with ID " << input << " not found." << std::endl;
    }
    Pause();
}

void LocationManager::RemoveLocation() 
{
    system("CLS");
    int input;
    std::cout << "Please enter the ID of the location that you wish to remove:" << std::endl;
    input = ValidateIntInput(1, locations.size());
    auto it = locations.find(input);
    system("CLS");
    if (it != locations.end())
    {
        locations.erase(it);
        std::cout << "Location " << input << " removed" << std::endl;
    }
    else
    {
        std::cout << "Location with ID " << input << " not found." << std::endl;
    }
    Pause();
    
    locFileHandler.SaveLocationsToFile(locations);
}

void LocationManager::AddLocation()
{
    system("CLS");
    std::string name;
    float longitude;
    float latitude;
    std::cout << "Please enter the name of the location that you wish to add:" << std::endl;
    std::cin >> std::ws;
    std::getline(std::cin, name);
    std::cout << "Please enter the longitude of the location that you wish to add" << std::endl;
    longitude = ValidateFloatInput(-180, 180);
    std::cout << "Please enter the latitude of the location that you wish to add" << std::endl;
    latitude = ValidateFloatInput(-90, 90);
    idCounter++;
    Location addLoc = Location(idCounter, name, longitude, latitude);
    locations.insert({ addLoc.GetLocationID(), addLoc });
    locFileHandler.SaveLocationsToFile(locations);
}

void LocationManager::DisplayLocationData(Location location)
{
    std::cout << "Location ID: " << location.GetLocationID() << ", ";
    std::cout << "Location Name: " << location.GetLocationName() << ", ";
    std::cout << "Longitude: " << location.GetLongitude() << ", ";
    std::cout << "Latitude: " << location.GetLatitude() << std::endl;
}

void LocationManager::GetLocationsByName(std::string searchName)
{
    system("CLS");
    std::vector<Location> searchLocations;
    for (auto& pair : locations) {
        if (pair.second.GetLocationName() == searchName) {
            searchLocations.push_back(pair.second);
        }
    }

    if (!searchLocations.empty()) {
        std::cout << searchLocations.size() << " Locations found with the name " << searchName << std::endl;
        for (auto& location : searchLocations) {
            DisplayLocationData(location);
        }
    }
    else {
        std::cout << "No locations found with name " << searchName << std::endl;
    }

}

void LocationManager::DisplayAllLocations()
{
    system("CLS");
    if (locations.empty())
    {
        std::cout << "No locations saved" << std::endl;
        return;
    }

    std::cout << "All saved locations:" << std::endl;
    for (auto& pair : locations)
    {
        Location& loc = pair.second;
        DisplayLocationData(loc);
    }
    Pause();
}

bool LocationManager::CheckSearchByName()
{
    std::cout << "would you like to search by name(1) or ID(2)?" << std::endl;
    int input = ValidateIntInput(1, 2);
    if (input == 2) {
        return false;
    }
    return true;
}


void LocationManager::SearchLocation()
{
    system("CLS");
    if (!locations.empty()) {
        if (CheckSearchByName())
        {
            std::string input;
            std::cout << "Please enter the name of the location that you wish to search:" << std::endl;
            std::cin >> input;
            system("CLS");
            GetLocationsByName(input);
            Pause();
        }
        else
        {
            int input;
            std::cout << "Please enter the ID of the location that you wish to search:" << std::endl;
            input = ValidateIntInput(1, locations.size());
            auto it = locations.find(input);
            system("CLS");
            if (it != locations.end()) {
                DisplayLocationData(it->second);

            }
            else
            {
                std::cout << "Location with ID " << input << " not found." << std::endl;
            }
            Pause();
        }
    }
    else
    {
        std::cout << "You have no saved locations, please add a location to search";
    }
}

void LocationManager::ManageLocations()
{
    bool exit = false;
    Menu manageLocationsMenu = Menu(1);
    while (!exit) {
        switch (manageLocationsMenu.RunMenu()) {
        case 1:
            AddLocation();
            break;
        case 2:
            DisplayAllLocations();
            break;
        case 3:
            ModifyLocationData();
            break;
        case 4:
            RemoveLocation();
            break;
        case 5:
            SearchLocation();
            break;
        case 6:
            exit = true;
            break;
        }
    }
}