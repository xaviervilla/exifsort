// Creates a JSON configuration file containing GPS coordinates derived from image metadata taken at unwanted locations
// Usage "./create_config [path_to_exclusionaries]"

#include <iostream>
#include <fstream>
#include <string.h>

#include "src/ExifTool.h"
#include "nlohmann/json.hpp"

#include "Place.hpp"

#define CONFIG_FILE "inclusion_exclusion_parameters_CREATED.json"

// for convenience
using json = nlohmann::json;

using namespace std;

int main(int argc, char **argv)
{
    // read a JSON file
//    ifstream i(CONFIG_FILE);
//    json j;
//    i >> j;
//    i.close();

    //write a JSON file
    json j;
    ofstream o(CONFIG_FILE);
    o << "{" << endl << setw(4) << "\"to_exclude\": {" << endl << setw(4) <<  "\"GPSPosition\": [";
//    {
//    "to_exclude": {
//        "GPSPosition": [
//
//      "37 deg 21' 54.65\" N, 120 deg 37' 3.91\" W",
//            "37 deg 21' 54.65\" N, 120 deg 37' 3.91\" W",
////            "37 deg 21' 54.65\" N, 120 deg 37' 3.91\" W"
//            ]
//    }
//    }

    if (argc < 2) {
        cout << "Example1: Read metadata from an image." << endl;
        cout << "Please specify input file name" << endl;
        return 1;
    }

    // create new Place Object
    Place* location = new Place();
    // create our ExifTool object
    ExifTool *et = new ExifTool();
    // read metadata from the image
    TagInfo *info = et->ImageInfo(argv[1]);
    if (info) {
        // print returned information
        for (TagInfo *i=info; i; i=i->next) {
            if(strcmp(i->name, "GPSPosition") == 0){
                location->setPlace(i->value, 0.6f);
                cout << "Latitude: " << location->getLatitude() << ",     Longitude: " << location->getLongitude() << endl << endl;
                //o << setw(4) << (i->value) << endl;//cords
                //cout << "ivalue") << (i->value) << endl << endl;
                //delete location;
            }
        }
        // we are responsible for deleting the information when done
        delete info;
        delete location;
    } else if (et->LastComplete() <= 0) {
        cerr << "Error executing exiftool!" << endl;
    }
    // print exiftool stderr messages
    char *err = et->GetError();
    if (err) cout << err;
    delete et;      // delete our ExifTool object
    o << setw(4) << "]" << endl << "}" << endl << "}";
    o.close();	// close output stream
    return 0;
}

char* formatGPSPosition(char *position){

}
