#ifndef PLACE_HPP
#define PLACE_HPP

#include <iostream>
#include <string.h>
#include <math.h>

class Place{
    float longitude;
    float latitude;
    float radius;
    float stripAndConvert(char* half);
    float power(int n, int m);
public:
    Place();
    void setPlace(char *GPSPosition, float radius);
    bool samePlace(char *GPSPosition);
    float getLongitude();
    float getLatitude();
    float getRadius();
};

#endif