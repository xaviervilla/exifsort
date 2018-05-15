//------------------------------------------------------------------------------
// File:        example1.cpp
//
// Description: Simple example to read metadata from a file
//
// Syntax:      example1 FILE
//
// License:     Copyright 2013-2016, Phil Harvey (phil at owl.phy.queensu.ca)
//
//              This is software, in whole or part, is free for use in
//              non-commercial applications, provided that this copyright notice
//              is retained.  A licensing fee may be required for use in a
//              commercial application.
//
// Created:     2013-11-28 - Phil Harvey
//------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string.h>
#include "inc/ExifTool.h"
#include "nlohmann/json.hpp"

#define CONFIG_FILE "inclusion_exclusion_parameters.json"

// for convenience
using json = nlohmann::json;

using namespace std;

int main(int argc, char **argv)
{
    // read a JSON file
    ifstream i(CONFIG_FILE);
    json j;
    i >> j;
    i.close();

    if (argc < 2) {
        cout << "Example1: Read metadata from an image." << endl;
        cout << "Please specify input file name" << endl;
        return 1;
    }
    // create our ExifTool object
    ExifTool *et = new ExifTool();
    // read metadata from the image
    TagInfo *info = et->ImageInfo(argv[1]);
    if (info) {
        // print returned information
        for (TagInfo *i=info; i; i=i->next) {\
            if(strcmp(i->name, "GPSLatitude") == 0){
                cout << i->name << " = " << i->value << endl;
            }
            else if(strcmp(i->name, "Model") == 0){
                cout << i->name << " = " << i->value << endl;
            }
            else{
                cout << i->name << " = " << i->value << endl;
            }
            
        }
        // we are responsible for deleting the information when done
        delete info;
    } else if (et->LastComplete() <= 0) {
        cerr << "Error executing exiftool!" << endl;
    }
    // print exiftool stderr messages
    char *err = et->GetError();
    if (err) cout << err;
    delete et;      // delete our ExifTool object
    return 0;
}
