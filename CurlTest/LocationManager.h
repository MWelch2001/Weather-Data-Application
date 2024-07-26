#ifndef LOCATIONMANAGER_H
#define LOCATIONMANAGER_H

#include "Menu.h"
#include "Location.h"
#include "Util.h"
#include "LocationFileHandler.h"

#include <unordered_map>
#include <iostream>

using namespace Util;

class LocationManager
{

public:
	void ManageLocations();
	LocationManager();
	std::unordered_map<int, Location> GetLocations();

private:
	
	int idCounter;
	std::unordered_map<int, Location> locations;
	LocationFileHandler locFileHandler = LocationFileHandler();

	bool CheckSearchByName();
	void SearchLocation();
	void RemoveLocation();
	void ModifyLocationData();
	void GetLocationsByName(std::string searchName);
	void AddLocation();
	void DisplayAllLocations();
	void DisplayLocationData(Location location);

};

#endif
