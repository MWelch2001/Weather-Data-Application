#include "LocationFileHandler.h"
#include <iostream>
#include <fstream>
#include <sstream>

LocationFileHandler::LocationFileHandler() 
{
	locFilename = "LocationsSaved.txt";
}

//saves all locations the user has added to the txt file 
void LocationFileHandler::SaveLocationsToFile(std::unordered_map<int, Location> locations) 
{
	std::ofstream saveFile(locFilename);
	if (!saveFile.is_open()) 
	{
		std::cerr << "Error: Unable to open file " << locFilename << std::endl;
		return;
	}

	for (auto& pair : locations) 
	{
		Location& loc = pair.second;
		saveFile << loc.GetLocationID() << " " << loc.GetLocationName() << " " << loc.GetLongitude() << " " << loc.GetLatitude() << std::endl;
	}

	saveFile.close();
}
//loads all locations the user has added from the txt file 
std::unordered_map<int, Location> LocationFileHandler::LoadLocationsFromFile(int& idCounter)
{
	std::unordered_map<int, Location> loadedLocations;
	std::ifstream loadedFile (locFilename);
	if (!loadedFile.is_open()) {
		std::cerr << "Error: Unable to open file " << locFilename << std::endl;
		return loadedLocations; 
	}

	std::string line;
	while (std::getline(loadedFile, line)) 
	{
		//Loads location data
		std::istringstream iss(line);
		int locationID;
		std::string locationName;
	    float longitude, latitude;
		if (iss >> locationID >> locationName >> longitude >> latitude) 
		{
			loadedLocations.insert({ locationID, Location(locationID, locationName, longitude, latitude) });
			
		}
		else 
		{
			std::cerr << "Error: Invalid line in file: " << line << std::endl;
		}
	}

	loadedFile.close();
	idCounter = loadedLocations.size();
	return loadedLocations;
}
