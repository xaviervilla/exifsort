#ifndef MODEL_HPP
#define MODEL_HPP

#include <iostream>
#include <string.h>

class Model{
    std::string model;
    Model* nextModel;
public:
    Model();
    Model(std::string model);
    std::string modelString();
    ~Model();
    Model* next();
    void setNext(Model* nextModel);
    bool matches(std::string model);
};

#endif