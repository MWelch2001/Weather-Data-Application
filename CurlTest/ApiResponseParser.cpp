#include "ApiResponseParser.h"

void ApiResponseParser::FormatData(size_t maxArraySize, json data) 
{

    // Iterate over the arrays and print values side by side with proper alignment
    for (size_t i = 0; i < maxArraySize; ++i) {
        for (auto it = data.begin(); it != data.end(); ++it) {
            if (it.value().is_array()) {
                const auto& dataArray = it.value();
                // format time data separately to avoid adding extra white spaces
                if (it.key() == "time") 
                {
                    if (i < dataArray.size()) {
                        responseStream << std::left << it.key() << ":" << dataArray[i] << "  ";
                    }
                    else {
                        responseStream << std::left << it.key() << ":";
                    }
                }
                else 
                {
                    if (i < dataArray.size()) {
                        responseStream << std::setw(10) << std::left << it.key() << ":" << dataArray[i] << "  ";
                    }
                    else {
                        responseStream << std::setw(10) << std::left << it.key() << ":";
                    }
                }
                
            }
        }
        responseStream << "\n";
    }
}

size_t ApiResponseParser::GetMaxArraySize(json jsonArray) 
{
    // finds the size of the longest array in the JSON api response
    size_t maxArraySize = 0;
    for (auto it = jsonArray.begin(); it != jsonArray.end(); ++it) {
        if (it.value().is_array()) {
            const auto& dataArray = it.value();
            maxArraySize = std::max(maxArraySize, dataArray.size());
        }
    }

    return maxArraySize;
}


void ApiResponseParser::GetData(json data, std::string objName)
{
    if (data.contains(objName)) {

        //Gets specifc array for hourly or daily based on parameter, which then contains more arrays with the data
        const json& jsonArray = data[objName];

        if (jsonArray.is_object()) {

            responseStream << objName <<" data:\n";

            size_t maxArraySize = GetMaxArraySize(jsonArray);
            FormatData(maxArraySize, jsonArray);
        }
        else {
            std::cout << "Error: " << objName << " data is not in the expected format.\n";
        }
    }
}

std::string ApiResponseParser::ParseResponse(std::string response, ApiRequestHandler& request) {
    try {
        json data = json::parse(response);
        GetData(data, "hourly");
        GetData(data, "daily");
    }
    catch (const std::exception& e) {
        std::cout << "Error: Exception occurred during JSON parsing: " << e.what() << "\n";
    }

    return responseStream.str();
}