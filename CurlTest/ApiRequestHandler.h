#ifndef API_REQUEST_BUILDER_H
#define API_REQUEST_BUILDER_H

#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cctype>
#include "Location.h"

class ApiRequestHandler {
public:

    ApiRequestHandler(Location search, std::string requestTimeframe);
    std::string SendRequest();
    void EditParams(std::string paramName);
    std::vector<std::pair<std::string, std::string>> GetParams();

private:
    std::string baseUrl;
    std::string paramFilename;
    Location searchLocation;
    std::vector<std::pair<std::string, std::string>> params;

    std::string BuildRequest();
    void LoadParamsFromFile();
    bool ContainsDigit(std::string value);
    static size_t WriteCallback(void* buffer, size_t size, size_t nmemb, void* param);
};

#endif // API_REQUEST_BUILDER_H
