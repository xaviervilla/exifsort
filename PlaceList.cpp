#include "PlaceList.hpp"

PlaceList::PlaceList(){
    this->headPlace = new Place();
    this->tailPlace = headPlace->next();
}


PlaceList::PlaceList(char *place, float radius){
    this->headPlace = new Place(place, radius);
    this->tailPlace = headPlace->next();
}


void PlaceList::addPlace(char *place, float radius){
    // Create node for our new place
    Place *temp = new Place(place, radius);
    
    // This is the case when the linked list is empty
    if(!headPlace->placeString().compare("NULL")){
        std::cout <<  "Unwanted place detected:\t" << place << std::endl;
        headPlace = temp;
        tailPlace = temp->next();
    }
    
    // This is the case when the list is not empty
    else{
        std::cout <<  "Unwanted place detected:\t" << place << std::endl;
        *tailPlace = *temp;
        tailPlace = temp->next();
    }
}

void PlaceList::printList(){
    Place *temp = headPlace;
    while(temp!=NULL){
        std::cout << temp->placeString() << std::endl;
        temp = temp->next();
    }
}

Place* PlaceList::getHead(){
    return this->headPlace;
}

Place* PlaceList::getTail(){
    return this->tailPlace;
}


PlaceList::~PlaceList(){
    Place *it = headPlace;
    Place *tmp;
    while(it!=tailPlace){
        tmp = it;
        it = it->next();
        delete tmp;
    }
    delete it;
}