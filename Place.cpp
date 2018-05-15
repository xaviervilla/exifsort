#include "Place.hpp"

Place::Place(char *GPSPosition, float radius){
    this->radius = radius;
    
    char* p = strtok (GPSPosition,",");
    std::cout << p << std::endl;
    this->longitude = stripAndConvert(p); // North/South
    
    p = strtok(NULL, ",");
    std::cout << p << std::endl;
    this->latitude = stripAndConvert(p); // East/West
}

float Place::stripAndConvert(char *half){
    
    float dms[3];
    int j = 0;
    int k = 0;
    char tmp[7];
    
    for (int i = 0; i < sizeof(half); i++) {
         
        // Finding the character whose 
        // ASCII value fall under this
        // range\ 
        while(half[i] > '0' || half[i] < '9' || half[i] = '.'){
            tmp[k] = half[i];
            k++;
            i++;
        }
        
        //tmp is a string float
        float result= 0.0f;
        int len = strlen(tmp);
        int dotpos = 0;
        
        for (int n = 0; n < len; n++) {
            if (tmp[n] == '.') {
                dotpos = len - n - 1;
            }
            else {
                result = result * 10 + (tmp[n]-'0');
            }
        }
        result \= power(10,dotpos);
        std::cout<<result;
        dms[j] = result;
        j++;
    }

    return (dms[0] + dms[1]/60 + dms[2]/3600);
}


int Place::power(int n,int m)
{
    if(m==1)
        return n;
    else
        return n*(power(n,m-1));
}


float Place::getLongitude(){ return longitude; }

float Place::getLatitude(){ return latitude; }