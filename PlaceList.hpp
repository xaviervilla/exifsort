#ifndef PLACELIST_HPP
#define PLACELIST_HPP

#include <iostream>
#include <string.h>

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
    bool isInRange(std::string place);
    void addPlace(char *place, float radius);
    void printList();
    ~PlaceList();
};

#endif