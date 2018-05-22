#include "ModelList.hpp"

ModelList::ModelList(){
    this->headModel = new Model();
    this->tailModel = headModel->next();
}


ModelList::ModelList(std::string model){
    this->headModel = new Model(model);
    this->tailModel = headModel->next();
}


void ModelList::addModel(std::string model){
    // Create node for our new model
    Model *temp = new Model(model);
    
    // This is the case when the linked list is empty
    if(!headModel->modelString().compare("NULL")){
        std::cout <<  "Unwanted device detected:\t" << model << std::endl;
        headModel = temp;
        tailModel = temp->next();
    }
    
    // This is the case when the list is not empty
    else{
        // Iterate through our linked list to find match
        Model *it = headModel;
        while(it->next() != tailModel){
            if(it->matches(model)){
                return;
            }
            it = it->next();
        }
        if(it->matches(model)){
            return;
        }
        std::cout <<  "Unwanted device detected:\t" << model << std::endl;
        it->setNext(temp);
        tailModel = it->next()->next();
    }
}

void ModelList::printList(){
    Model *temp = headModel;
    while(temp!=NULL){
        std::cout << temp->modelString() << std::endl;
        temp = temp->next();
    }
}

Model* ModelList::getHead(){
    return this->headModel;
}

Model* ModelList::getTail(){
    return this->tailModel;
}


ModelList::~ModelList(){
    Model *it = headModel;
    Model *tmp;
    while(it!=tailModel){
        tmp = it;
        it = it->next();
        delete tmp;
    }
    delete it;
}