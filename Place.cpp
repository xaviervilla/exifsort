#include "Place.hpp"

Place::Place(){
    this->radius = 0.0f;
    this->longitude = 0.0f;
    this->latitude = 0.0f;
}

void Place::setPlace(char *GPSPosition, float radius){
    this->radius = radius;
    
    char* p = strtok (GPSPosition,",");
    
    std::cout << p << std::endl;
    this->longitude = stripAndConvert(p); // North/South

    p = strtok(NULL, ",");
    std::cout << p << std::endl;
    this->latitude = stripAndConvert(p); // East/West
}

float Place::power(int n,int m)
{
    if(m==1)
        return n;
    else
        return n*(power(n,m-1));
}

float Place::stripAndConvert(char *half){
    
    float dms[3] = {0.0f};
    int i = 0;
    int j = 0;
    int k = 0;
    char tmp[7];
    bool dot = false;
    
    //tmp is a string float
    float result= 0.0f;
    int len = 0;
    int dotpos = 0;
    // Finding the character whose 
    // ASCII value fall under this
    // range\ 
    while(j < 3)
    {
        while( !((half[i] >= '0' && half[i] <= '9') || half[i] == '.') )
        {
            // Do nothing
            i++;
        }
        while((half[i] >= '0' && half[i] <= '9') || half[i] == '.')
        {
            tmp[k] = half[i];
            k++;
            i++;
        }

        //tmp is a string float
        result = 0.0f;
        len = k;
        dotpos = 0;

        for (int n = 0; n < len; n++)
        {    if (tmp[n] == '.')
            {
                dotpos = len - n - 1;
                dot = true;
            }
            else
                result = result * 10 + (tmp[n]-'0');
        }
        
        if(dotpos)
            result = result / power(10, dotpos);//segfault
        dms[j] = result;
        j++;
        k = 0;
    }
    return dms[1];
    //return (dms[0] + dms[1]/60.0f + dms[2]/3600.0f);
}

float Place::getLongitude(){ return longitude; }

float Place::getLatitude(){ return latitude; }