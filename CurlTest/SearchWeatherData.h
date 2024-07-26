#ifndef SEARCH_WEATHER_DATA_H
#define SEARCH_WEATHER_DATA_H

#include "ApiRequestHandler.h"
#include "ApiResponseParser.h"
#include "LocationManager.h"
#include "Location.h";
#include "menu.h"
#include "Util.h"


#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

using namespace Util;

class SearchWeatherData
{

public:
	SearchWeatherData();
	void SearchWeather();
	void SetSearchLocations(std::unordered_map<int, Location> locations);

private:

	std::unordered_map<int, Location> searchLocations;
	std::vector<std::string> GetParamChanges(std::vector<std::string> paramChanges);
	int GetSearchLocation();
	void ChangeParams(ApiRequestHandler& request, std::vector<std::string> paramChanges);
	void SearchForWeatherData(std::vector<std::string> paramChanges);
};

#endif