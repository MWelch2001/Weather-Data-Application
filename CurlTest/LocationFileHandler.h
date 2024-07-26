#ifndef LOCATIONLOADER_H
#define LOCATIONLOADER_H

#include <string>
#include <unordered_map>
#include "Location.h"

class LocationFileHandler
{
    private:
	    std::string locFilename;

    public:
        LocationFileHandler();
        std::unordered_map<int, Location> LoadLocationsFromFile(int& idCounter);
        void SaveLocationsToFile(std::unordered_map<int, Location> locations);
};

#endif