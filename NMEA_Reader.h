#ifndef NMEA_Reader_h
#define NMEA_Reader_h


#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// using namespace std;

class NMEA_Reader
{
private:
    bool status;
    double Long ;
    double Lat ;
    double Alt ;
    int dataValidation;
    double geoid ; // meter
    int satNumber;
    char Lat_dir;
    char Long_dir;
    double UTC;
    // std::string NMEA_GPRMC ;
    std::string NMEA_GPGGA  ;

public:
    NMEA_Reader();
    ~NMEA_Reader();
    double getLat();
    double getLong();
    double getAlt();
    double getUTC();
    double getGeoid();
    char getLongDir();
    char getLatDir();
    int getDataValidation();
    int getSatNumber();
    
    bool getStatus();

    // bool setNMEA_GPRMC(char* str); 
    // bool setNMEA_GPRMC(std::string str); 
    bool setNMEA_GPGGA(char* str); 
    bool setNMEA_GPGGA(std::string str); 
    std::vector<std::string> NMEA_split(std::string l, std::string k);
};

NMEA_Reader::NMEA_Reader()
{
    this->status = false;
    this->Alt = 0;
    this->Lat = 0;
    this->Long = 0;
    this->dataValidation = 0;
    this->geoid = 0;
    this->Lat_dir = 'N';
    this->Long_dir = 'E';
    this->UTC = 0;
    this->satNumber = 0;

    this->NMEA_GPGGA = "";
    // this->NMEA_GPRMC = "";
}

NMEA_Reader::~NMEA_Reader()
{

}

// bool NMEA_Reader::setNMEA_GPRMC(char* str)
// {
//     this->status = false;
//     //TODO:
//     return false;
// }

// bool NMEA_Reader::setNMEA_GPRMC(std::string str)
// {
//     this->status = false;
//     this->NMEA_GPRMC = str;
//     if (str.compare(0,6,"$GPRMC") == 0)
//     {
//         // valid input 
//     }

//     return false;
    
// }

bool NMEA_Reader::setNMEA_GPGGA(char * str)
{
    std::string s = str;
    return this->setNMEA_GPGGA(s);
}

bool NMEA_Reader::setNMEA_GPGGA(std::string str)
{
    this->status = false;
    this->NMEA_GPGGA = str;
    if (str.compare(0,6,"$GPGGA") == 0)
    {
        // valid input 
        double gps_lat,gps_long,gps_alt,gps_utc,geoid;
        char gps_lat_dir,gps_long_dir; // N , E
        int validation,satNumber;
        std::vector<std::string> ggaData = this->NMEA_split(str , ",");
        try
        {
            gps_utc = std::stod(ggaData.at(1));
            gps_lat = std::stod(ggaData.at(2));
            gps_lat_dir = (ggaData.at(3)).at(0);
            gps_long = std::stod(ggaData.at(4));
            gps_long_dir = (ggaData.at(5)).at(0);
            validation = (int)std::stod(ggaData.at(6));
            satNumber = (int)std::stod(ggaData.at(7));
            gps_alt = std::stod(ggaData.at(9));
            geoid = std::stod(ggaData.at(11));
            this->status = true;
        }
        catch(const std::exception& e)
        {
            gps_utc = 0;
            gps_lat = 0;
            gps_lat_dir = 'N';
            gps_long = 0;
            gps_long_dir = 'E';
            validation =0;
            satNumber = 0;
            gps_alt = 0;
            geoid =0;
            this->status = false;
        }
        this->Alt = gps_alt;
        this->Lat = gps_lat;
        this->Long = gps_long;
        this->dataValidation = validation;
        this->geoid = geoid;
        this->Lat_dir = gps_lat_dir;
        this->Long_dir = gps_long_dir;
        this->UTC = gps_utc;
        this->satNumber = satNumber;

        return true;
    }

    return false;
    
}

double NMEA_Reader::getLat()
{
    return this->Lat;
}
double NMEA_Reader::getLong()
{
    return this->Long;
}
double NMEA_Reader::getAlt()
{
    return this->Alt;
}
double NMEA_Reader::getGeoid()
{
    return this->geoid;
}
char NMEA_Reader::getLongDir()
{
    return this->Long_dir;
}
char NMEA_Reader::getLatDir()
{
    return this->Lat_dir;
}
int NMEA_Reader::getSatNumber()
{
    return this->satNumber;
}
int NMEA_Reader::getDataValidation()
{
    return this->dataValidation;
}
double NMEA_Reader::getUTC()
{
    return this->UTC;
}
bool NMEA_Reader::getStatus()
{
    return this->status;
}

// for string delimiter
std::vector<std::string> NMEA_Reader::NMEA_split (std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

#endif