#ifndef PLACELIST_HPP
#define PLACELIST_HPP

#include <iostream>
#include <string.h>
#include <sstream>
#include <cmath>

#include "Place.hpp"

// This class is a linked-list for Places

class PlaceList{
    Place *headPlace;
    Place *tailPlace;
public:
    PlaceList();
    PlaceList(char *place, float radius);
    Place* getHead();
    Place* getTail();
    bool unwanted(char* place);
    void addPlace(char *place, float radius);
    void addPlace(std::string place);
    void printList();
    ~PlaceList();
};

#endif