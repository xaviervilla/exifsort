#ifndef PLACE_HPP
#define PLACE_HPP

#include <iostream>
#include <string.h>
#include <sstream>
#include <math.h>

class Place{
    float longitude;
    float latitude;
    float radius;
    float stripAndConvert(char* half);
    float power(int n, int m);
    std::string place;
    Place *nextPlace;
public:
    Place();
    Place(char *place, float radius);
    void setPlace(char *GPSPosition, float radius);
    bool samePlace(char *GPSPosition);
    float getLongitude();
    float getLatitude();
    float getRadius();
    Place* next();
    void setNext(Place *nextPlace);
    std::string placeString();
};

#endif