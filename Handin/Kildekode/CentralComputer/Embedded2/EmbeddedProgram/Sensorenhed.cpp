//////////////////////////////////////
// Developed by Christian and David //
// Digitalizing is assuming reality //
//////////////////////////////////////
#include "Sensorenhed.hpp"

//Constructor for Sensorenhed-dummy
Sensorenhed::Sensorenhed(int sensorNumber)
{
    _sensorNumber = sensorNumber;
    if(_sensorNumber == 1){name_ = "TempSensor";}
    else if(_sensorNumber == 2){name_ = "SaltSensor";}
    else if(_sensorNumber == 3){name_ = "WaterLevelSensor";}
    else if(_sensorNumber == 4){name_ = "pHSensor";}
    //std::cout << "Constructor for Sensorenhed_" << _sensorNumber  << " with name: " << name_ << std::endl;
}

//read()-method for returning af random value between 21 and 30..
double Sensorenhed::read()
{
    //std::cout << "SE: " << name_ << " read() for 1 second" << std::endl;
    sleep(1);

    //Random number for 
    value = rand() % 9 + 21 ;
    //cout << "SE: "<< name_ << " measured: " << value << endl;
    return value;
}

//Destructor for Sensorenhed
Sensorenhed::~Sensorenhed()
{
    //cout << "Deleted Sensorenhed" << endl;
}