#include "ApiRequestHandler.h"
#define CURL_STATICLIB

#include <iostream>
#include "curl/curl.h"
#include <iostream>
#include <fstream>
#include <sstream>


ApiRequestHandler::ApiRequestHandler(Location search, std::string requestTimeframe):searchLocation(search)
{
	baseUrl = "https://api.open-meteo.com/v1/forecast?";
	if (requestTimeframe == "hourly") 
	{
		paramFilename = "HourlyParams.txt";
	}
	else if (requestTimeframe == "daily") 
	{
		paramFilename = "DailyParams.txt";
	}

	
	LoadParamsFromFile();
}

//Returns all of the currently loaded parameters
std::vector<std::pair<std::string, std::string>> ApiRequestHandler::GetParams() 
{
	return params;
}


//Loads parameters from file
void ApiRequestHandler::LoadParamsFromFile()
{
	std::ifstream loadedFile(paramFilename);
	if (!loadedFile.is_open()) {
		std::cerr << "Error: Unable to open file " << paramFilename << std::endl;
		return;
	}


	//loads the parameter name and value into a pair that is then stored in the vector
	std::string line;
	while (std::getline(loadedFile, line))
	{
		std::istringstream iss(line);
		std::string paramName;
		std::string paramValue;
		if (iss >> paramName >> paramValue)
		{
			params.insert(params.end(), { paramName, paramValue });
		}
		else
		{
			std::cerr << "Error: Invalid line in file: " << line << std::endl;
		}
	}

	loadedFile.close();
}


bool ApiRequestHandler::ContainsDigit(std::string value) 
{
	return std::any_of(value.begin(), value.end(), ::isdigit);
}

void ApiRequestHandler::EditParams(std::string paramName) 
{
	for (auto &param : params) {
		if (param.first == paramName)
		{
			if (param.second == "true")
			{
				param.second = "false";
			}
			else if (param.second == "false")
			{
				param.second = "true";
			}
		}		
	}
}

size_t ApiRequestHandler::WriteCallback(void* buffer, size_t size, size_t nmemb, void* param) {
	std::string& text = *static_cast<std::string*>(param);
	size_t totalsize = size * nmemb;
	text.append(static_cast<char*>(buffer), totalsize);
	return totalsize;
}

std::string ApiRequestHandler::SendRequest() 
{
	std::string result;
	CURL* curl;
	CURLcode res; 
	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, BuildRequest().c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if (CURLE_OK != res) {
			std::cerr << "CURL error: " << res << '\n';
		}
	}
	curl_global_cleanup();
	//returns unparsed json result as a string 
	return result;
}

//create the request to be returned straight into curl
std::string ApiRequestHandler::BuildRequest()
{
	//integer to check if the it is the first parameter or not
	int paramCounter = 0;
	std::stringstream requestStream;
	//adds desired location to url //
	requestStream << baseUrl;
	//adds current search location data
	requestStream << "latitude=" << searchLocation.GetLatitude() << "&longitude=" << searchLocation.GetLongitude();

	// sorts through loaded parameters and adds to request if the value is set to true
	for (auto& param : params) {
		std::string paramValue = param.second;
		if (paramValue.find("include") != std::string::npos)
		{
			requestStream.seekp(-1, requestStream.cur);
			requestStream << param.first;
		}
		else if (paramValue == "true")
		{
			requestStream << param.first << ",";			
		}
		else if (ContainsDigit(paramValue)) 
		{
			
			requestStream << "&" << param.first << "=" << param.second << ",";
		}
	}
	
	std::string requestUrl = requestStream.str();
	requestUrl.pop_back();
	return requestUrl;
}

