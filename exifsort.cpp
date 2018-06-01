#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>

// Imported Libraries
#include "src/ExifTool.h"
#include "nlohmann/json.hpp"

// Created Libraries
#include "PlaceList.hpp"
#include "ModelList.hpp"

#define EXCLUSIONARY_PARAMETERS "parameters/to_exlcude.json"
#define INCLUSIONARY_PARAMETERS "parameters/to_inclcude.json"

// for convenience
using json = nlohmann::json;
using namespace std;


int buildExclusions(char** arg){
    // Create a linked-list to store device models in
    PlaceList *list = new PlaceList();
    
    // create our ExifTool object
    ExifTool *et = new ExifTool();
    
    // read metadata from the image
    TagInfo *info;
    float radius = .0005;
    if(strcmp(arg[2], "-r") == 0){
        info = et->ImageInfo(arg[4]);
        radius = atof(arg[3]);
    }
    else
        info = et->ImageInfo(arg[2]);

    // write a JSON file to string stream
    ofstream f(EXCLUSIONARY_PARAMETERS);
    ostringstream o;
    f << "{" << endl << "\t" << "\"to_exclude\": {" << endl << "\t\t" <<  "\"GPSPosition\": [" << endl;
    
    if (info) {
        // create a linked list of locations
        TagInfo *i;
        for (i=info; i; i=i->next) {
            if(strcmp(i->name, "GPSPosition") == 0){
                list->addPlace(i->value, radius);
            }
        }
        
        // Print each link in the list to the JSON file
        Place *head = list->getHead();
        Place *tail = list->getTail();
        Place *temp = head;
        
        while(temp->next() != tail){
            f << "\t\t\t" << temp->placeString() << "," << endl;
            temp = temp->next();
        }
        f << "\t\t\t" << temp->placeString() << endl;
        
        // we are responsible for deleting the information when done
        delete info;
        delete i;
    }
	else if (et->LastComplete() <= 0) {
        cerr << "Error executing exiftool!" << endl;
    }

    // Finish our JSON creation
    f << "\t\t" << "]" << endl << "\t" << "}" << endl << "}";
    f.close();	// close output stream
    // print exiftool stderr messages
    char *err = et->GetError();
    if (err) cout << err;
    delete list;    // delete our list
    delete et;      // delete our ExifTool object
    return 0;
}


int buildInclusions(char** arg){
    // Create a linked-list to store device models in
    ModelList *list = new ModelList();
    
    // create our ExifTool object
    ExifTool *et = new ExifTool();
    
    // read metadata from the image
    TagInfo *info = et->ImageInfo(arg[2]);

    // write a JSON file
    ofstream f(INCLUSIONARY_PARAMETERS);
    f << "{" << endl << "\t" << "\"to_include\": {" << endl << "\t\t" <<  "\"Model\": [" << endl;

    if (info) {
        // create a linked list of devices without duplicates
        TagInfo *i;
        for (i=info; i; i=i->next) {
            if(strcmp(i->name, "Model") == 0){
                list->addModel(i->value, 1);
            }
        }

        // Print each link in the list to the JSON file
        Model *head = list->getHead();
        Model *tail = list->getTail();
        Model *temp = head;
        
        while(temp->next() != tail){
            f << "\t\t\t" << "\"" << temp->modelString() << "\"," << endl;
            temp = temp->next();
        }
        f << "\t\t\t" << "\"" << temp->modelString() << "\"" << endl;
        
        // we are responsible for deleting the information when done
        delete info;
        delete i;
    }
	else if (et->LastComplete() <= 0) {
        cerr << "Error executing exiftool!" << endl;
    }
    else{
        cout << "Error, check your input. " << arg[2] << endl;
    }

    // Finish our JSON creation
    f << "\t\t" << "]" << endl << "\t" << "}" << endl << "}";
    f.close();	// close output stream
    // print exiftool stderr messages
    char *err = et->GetError();
    if (err) cout << err;
    delete list;    // delete our linked list
    delete et;      // delete our ExifTool object
    return 0;
}


int filter(char **arg){
    // read JSON inclusion file
    ifstream is(INCLUSIONARY_PARAMETERS);
    json inc;
    is >> inc;
    is.close();
    // read JSON inclusion file
    ifstream es(EXCLUSIONARY_PARAMETERS);
    json exc;
    es >> exc;
    es.close();
    
    auto includes = inc.find("to_include");
    auto excludes = exc.find("to_exclude");
    
    ModelList *models = new ModelList();
    PlaceList *places = new PlaceList();
    
    cout << endl;
    cout << "Only including the following devices:" << endl;
    for (int i = 0; i < includes.value()["Model"].size(); i++){
        models->addModel(includes.value()["Model"][i], 0);
    }
    cout << endl;
    
    cout << "Excluding all of the following locations:" << endl;
    for (int i = 0; i < excludes.value()["GPSPosition"].size(); i++){ 
        places->addPlace(excludes.value()["GPSPosition"][i]);
    }
    cout << endl;
    
    // Now we actually need to read in a new image and compare the metadata.
    // create our ExifTool object
    ExifTool *et = new ExifTool();
    
    // read metadata from the image
    TagInfo *info = et->ImageInfo(arg[2]);
    
    // Compare Metadata
    if (info) {
        // create a linked list of devices without duplicates
        TagInfo *i;
        for (i=info; i; i=i->next) {
            if(strcmp(i->name, "Model") == 0){
                //Check model list for absence
                //if absent, delete
                //if (models->unwanted(i->value)){
                //    cout << "Device is unwanted:\t" << i->value << endl;
                //}
            }
            else if(strcmp(i->name, "GPSPosition") == 0){
                //check GPS position for containment
                //if contained, delete
                if (places->unwanted(i->value)){
                    cout << "Place is unwanted:\t " << i->value << endl;
                }
                else {
                    cout << "Place is WANTED:\t " << i->value << endl;
                }
            }
        }
    }
    
    delete et; // We are responsible for deleting this
    return 0;
}


void readRights(){
        cout << "Usage:" << endl << endl;
        
        cout << "./exifsort -build-exclusions (Optionally: -r <radius>) <filepath_to_exclusions>" << endl << endl;
        cout << "This option recursively writes the GPS coordinates of all images in the directory provided to a JSON file as an exclusionary parameter to be utilized during the filtering process. During filtering, any image tested within radius (provided with -r <float>) of an exclusionary parameter will be moved to the deleted folder." << endl << endl;
        
        cout << "./exifsort -build-inclusions <filepath_to_inclusions>" << endl << endl;
        cout << "This option recursively writes the model of phone/camera of all images in the directory provided to a JSON file as an inclusionary parameter to be utilized during the filtering process. During filtering, any image tested that was taken with a camera or phone model that is not an inclusionary parameter will be moved to the deleted folder." << endl << endl;
        
        cout << "./exifsort -filter <filepath_to_filter>" << endl << endl;
        cout << "This filtering process utilizes two methods to screen image files. 1) This option recursively checks the Model of camera and/or phone used to take the photo, and compares it to a list of inclusionary parameters saved in a JSON file. These inclusionary parameters can be created using the `-build-inclusions` flag. If the camera or phone's model checked is not an inclusionary parameter, it will be immediately moved to the deleted folder. 2) This option also recursively checks the GPS coordinates of all images in the directory provided, comparing the GPS coordinates with exclusion parameters saved in a JSON file. These exclusionary parameters can be created using the `-build-exclusions` flag. If any image in the directory provided is within radius of an exclusion parameter, it will be moved to the deleted folder." << endl << endl;
    }

int main(int argc, char **argv){
    if (argc < 3) {
        readRights();
        return 1;
    }
    
    if(strcmp(argv[1], "-build-exclusions") == 0){
        int err = buildExclusions(argv);
        if(err) cout << "Something went wrong building the exclusions." << endl;
    }
    else if(strcmp(argv[1], "-build-inclusions") == 0){
        int err = buildInclusions(argv);
        if(err) cout << "Something went wrong building the inclusions." << endl;
    }
    else if(strcmp(argv[1], "-filter") == 0){
        int err = filter(argv);
        if(err) cout << "Something went wrong building the exclusions." << endl;
    }
    else{
        readRights();
    }
}
