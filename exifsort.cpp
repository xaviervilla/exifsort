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
#include "Place.hpp"

#define JSON_FILE "to_exlcude.json"

// for convenience
using json = nlohmann::json;
using namespace std;

int main(int argc, char **argv)
{

    if (argc < 2) {
        cout << "Example1: Read metadata from an image." << endl;
        cout << "Please specify input file or directory name" << endl;
        return 1;
    }

    // create new Place Object
    Place *location = new Place();
    // create our ExifTool object
    ExifTool *et = new ExifTool();
    // read metadata from the image
    TagInfo *info = et->ImageInfo(argv[1]);

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
