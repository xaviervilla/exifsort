#ifndef MODELLIST_HPP
#define MODELLIST_HPP

#include <iostream>
#include <string.h>

#include "Model.hpp"

// This class is a linked-list that only adds nodes for unique strings.
// If the Model string passed in to the list is already in the linked list,
// then nothing is added to the list.

class ModelList{
    Model *headModel;
    Model *tailModel;
public:
    ModelList();
    ModelList(std::string model);
    Model* getHead();
    Model* getTail();
    void addModel(std::string model);
    void printList();
    ~ModelList();
};

#endif