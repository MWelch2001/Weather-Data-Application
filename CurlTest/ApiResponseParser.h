#ifndef API_RESPONSE_PARSER_H
#define API_RESPONSE_PARSER_H

//#define NOMINMAX
#include <algorithm>

#include "ApiRequestHandler.h"
#include "nlohmann/json.hpp"

#include <string>
#include <sstream>
#include <iostream>


using json = nlohmann::json;
class ApiResponseParser
{
public:
	std::string ParseResponse(std::string response, ApiRequestHandler& request);

private:
	void GetData(json data, std::string objName);
	void FormatData(size_t maxArraySize, json data);
	std::stringstream responseStream;
	size_t GetMaxArraySize(json jsonArray);
};

#endif