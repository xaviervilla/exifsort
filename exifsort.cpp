// Creates a JSON configuration file containing GPS coordinates derived from image metadata taken at unwanted locations
// Usage "./create_config [path_to_exclusionaries]"

#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>

// Imported Libraries
#include "src/ExifTool.h"
#include "nlohmann/json.hpp"

// Created Library
#include "Build.hpp"
#include "Place.hpp"

#define JSON_FILE "to_exlcude.json"

// for convenience
using json = nlohmann::json;
using namespace std;

int buildExclusions(char* arg){
    // create new Place Object
    Place *location = new Place();
    // create our ExifTool object
    ExifTool *et = new ExifTool();
    // read metadata from the image
    TagInfo *info = et->ImageInfo(arg);

    // write a JSON file to string stream
    ofstream f(JSON_FILE);
    ostringstream o;
    f << "{" << endl << "\t" << "\"to_exclude\": {" << endl << "\t\t" <<  "\"GPSPosition\": [" << endl;
    // temporary string for comma purposes

    if (info) {
        // print and save returned information
        string filename;
        for (TagInfo *i=info; i; i=i->next) {
            if (!strcmp(i->name, "FileName")) filename = i->value;
            if(strcmp(i->name, "GPSPosition") == 0){
                location->setPlace(i->value, 0.6f);
                f << o.str();
                o.str("");
                cout << filename << ":" << endl << i->value << endl;
                o << "\t\t\t" << "\"" << location->getLatitude() << "," << location->getLongitude() << "\"," << endl;
            }
        }
        f << "\t\t\t" << "\"" << location->getLatitude() << "," << location->getLongitude() << "\"" << endl;
        // we are responsible for deleting the information when done
        delete info;
        delete location;
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
    delete et;      // delete our ExifTool object
    return 0;
}

int filter(char *arg){
    return 0;
}

int main(int argc, char **argv)
{

    if (argc < 2) {
        cout << "Example1: Read metadata from an image." << endl;
        cout << "Please specify input file or directory name" << endl;
        return 1;
    }
    
    if(strcmp(argv[1], "-build-exclusions") == 0){
        int err = buildExclusions(argv[2]);
        if(err) cout << "Something went wrong building the exclusions." << endl;
    }
    else if(strcmp(argv[1], "-filter") == 0){
        int err = filter(argv[2]);
        if(err) cout << "Something went wrong building the exclusions." << endl;
    }
    else{
        cout << "Usage:" << endl << endl;
        
        cout << "./exifsort -build-exclusions (Optionally: -r <radius>) <filepath_to_exclusions>" << endl << endl;
        cout << "This option recursively writes the GPS coordinates of all images in the directory provided to a JSON file as an exclusionary parameter to be utilized during the filtering process. During filtering, any image tested within radius (provided with -r <float>) of an exclusionary parameter will be moved to the deleted folder." << endl << endl;
        
        cout << "./exifsort -build-inclusions <filepath_to_inclusions>" << endl << endl;
        cout << "This option recursively writes the model of phone/camera of all images in the directory provided to a JSON file as an inclusionary parameter to be utilized during the filtering process. During filtering, any image tested that was taken with a camera or phone model that is not an inclusionary parameter will be moved to the deleted folder." << endl << endl;
        
        cout << "./exifsort -filter <filepath_to_filter>" << endl << endl;
        cout << "This filtering process utilizes two methods to screen image files. 1) This option recursively checks the Model of camera and/or phone used to take the photo, and compares it to a list of inclusionary parameters saved in a JSON file. These inclusionary parameters can be created using the `-build-inclusions` flag. If the camera or phone's model checked is not an inclusionary parameter, it will be immediately moved to the deleted folder. 2) This option also recursively checks the GPS coordinates of all images in the directory provided, comparing the GPS coordinates with exclusion parameters saved in a JSON file. These exclusionary parameters can be created using the `-build-exclusions` flag. If any image in the directory provided is within radius of an exclusion parameter, it will be moved to the deleted folder." << endl << endl;
    }
}