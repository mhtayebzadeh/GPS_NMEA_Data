#include <stdio.h>
#include "SerialPort.h"
#include "NMEA_Reader.h"
using namespace std;
int main()
{
    SerialPort* serial = new SerialPort("/dev/ttyO4" , 9600);
    NMEA_Reader* nm  = new NMEA_Reader();
    std::string ss = "$GPGGA,123519,4807.038,N,01131.000,E,1,08,0.9,545.4,M,46.9,M,,*47";
    nm->setNMEA_GPGGA(ss);
    std::cout << std::endl;
    std::cout <<"utc = " << nm->getUTC() <<std::endl;
    std::cout <<"lat = " << nm->getLat() <<std::endl;
    std::cout <<"long = " << nm->getLong() <<std::endl;
    std::cout <<"alt = " << nm->getAlt() <<std::endl;
    std::cout <<"geoid = " << nm->getGeoid() <<std::endl;
    std::cout <<"data validation = " << nm->getDataValidation() <<std::endl;

    while(1)
    {
        ss = serial->readString(150);//<< std::endl;
        if (ss.compare(0,6,"$GPGGA") == 0)
        {
            nm->setNMEA_GPGGA(ss);
            std::cout << std::endl;
            std::cout <<"utc = " << nm->getUTC() <<std::endl;
            std::cout <<"lat = " << nm->getLat() <<std::endl;
            std::cout <<"long = " << nm->getLong() <<std::endl;
            std::cout <<"alt = " << nm->getAlt() <<std::endl;
            std::cout <<"geoid = " << nm->getGeoid() <<std::endl;
            std::cout <<"data validation = " << nm->getDataValidation() <<std::endl;


        }


    }
    return 0;
}
