#include "Location.h"
#include <string>

Location::Location(int locID, std::string locName, float inputLongitude, float inputLatitude)
{
	locationID = locID;
	locationName = locName;
	longitude = inputLongitude;
	latitude = inputLatitude;
}


void Location::SetLocationID(int locID)
{
	locationID = locID;
}

void Location::SetLocationName(std::string locName)
{
	locationName = locName;
}

void Location::SetLongitude(float inputLongitude)
{
	longitude = inputLongitude;
}

void Location::SetLatitude(float inputLatitude)
{
	latitude = inputLatitude;
}



int Location::GetLocationID()
{
	return locationID;
}

std::string Location::GetLocationName()
{
	return locationName;
}

float Location::GetLongitude()
{
	return longitude;
}

float Location::GetLatitude()
{
	return latitude;
}
