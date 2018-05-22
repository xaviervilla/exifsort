#include "Model.hpp"

Model::Model(){
    this->model = "NULL";
    this->nextModel = NULL;
}

Model::Model(std::string model){
    this->model = model;
    this->nextModel = NULL;
}

Model* Model::next(){
    return nextModel;
}

void Model::setNext(Model *nextModel){
    this->nextModel = nextModel;
}

std::string Model::modelString(){
    return model;
}

bool Model::matches(std::string model){
    return !((this->model).compare(model));
}

Model::~Model(){
    
}