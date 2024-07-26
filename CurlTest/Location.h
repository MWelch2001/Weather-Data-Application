#ifndef LOCATION_H
#define LOCATION_H

#include <string>

class Location {
public:
    Location(int locID, std::string locName, float inputLongitude, float inputLatitude);

    void SetLocationID(int locID);
    void SetLocationName(std::string locName);
    void SetLongitude(float inputLongitude);
    void SetLatitude(float inputLatitude);


    int GetLocationID();
    std::string GetLocationName();
    float GetLongitude();
    float GetLatitude();

private:
    int locationID;
    std::string locationName;
    float longitude;
    float latitude;
};

#endif