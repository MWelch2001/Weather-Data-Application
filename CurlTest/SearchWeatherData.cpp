#include "SearchWeatherData.h"

SearchWeatherData::SearchWeatherData()
{
    
}

void SearchWeatherData::SetSearchLocations(std::unordered_map<int, Location> locations)
{
    searchLocations = locations;
}

std::vector<std::string> SearchWeatherData::GetParamChanges(std::vector<std::string> paramChanges)
{
    bool exit = false;
    std::string input;
    while (!exit)
    {

        std::cout << "Please enter the name of the variable you would like to change?" << std::endl;
        std::cin >> input;
        paramChanges.push_back(input);

        system("CLS");
        std::cout << "Is that every parameter you wish to change? (Y/N)" << std::endl;
        std::cin >> input;
        if (input == "y" || input == "Y")
        {
            exit = true;
        }
        system("CLS");
    }
    return paramChanges;
}

void SearchWeatherData::ChangeParams(ApiRequestHandler& request, std::vector<std::string> paramChanges)
{
    for (auto& param : paramChanges)
    {
        request.EditParams(param);
    }
}

int SearchWeatherData::GetSearchLocation()
{
    int input = 0;
    if (!searchLocations.empty()) {
        std::cout << "Please enter the ID of the location that you wish to search:" << std::endl;
        input = ValidateIntInput(1, searchLocations.size());
        auto it = searchLocations.find(input);
        system("CLS");
        if (it != searchLocations.end()) {
            input = it->second.GetLocationID();
        }
        else
        {
            std::cout << "Location with ID " << input << " not found." << std::endl;
        }
        Pause();
    }
    else
    {
        std::cout << "You have no saved locations, please add a location to search";
        Pause();
    }
    return input;
}

//Gets search timeframe between hourly and daily
std::string GetRequestTimeFrame() 
{
    system("CLS");
    std::cout << "Would you like the hourly(1) or daily(2) weather data?" << std::endl;
    int input = ValidateIntInput(1, 2);
    if (input == 1) 
    {
        return "hourly";
    }
    else
    {
        return "daily";
    }
}

void SearchWeatherData::SearchForWeatherData(std::vector<std::string> paramChanges)
{
    std::string requestTimeframe = GetRequestTimeFrame();
    int searchID = GetSearchLocation();
    if (searchID != 0)
    {
        system("CLS");
        ApiRequestHandler request = ApiRequestHandler(searchLocations.at(searchID), requestTimeframe);
        if (!paramChanges.empty())
        {
            ChangeParams(request, paramChanges);
        }
        std::string data = request.SendRequest();
        ApiResponseParser parser;
        data = parser.ParseResponse(data, request);
        std::cout << searchLocations.at(searchID).GetLocationName() << "'s ";
        std::cout << data << std::endl;
    }
}

void SearchWeatherData::SearchWeather()
{
    bool exit = false;
    Menu weatherMenu = Menu(2);
    std::vector<std::string> paramChanges;
    while (!exit) {
        switch (weatherMenu.RunMenu()) {
        case 1:
            paramChanges = GetParamChanges(paramChanges);
            break;
        case 2:
            SearchForWeatherData(paramChanges);
            Pause();
            break;
        case 3:
            exit = true;
            break;
        }
    }
}