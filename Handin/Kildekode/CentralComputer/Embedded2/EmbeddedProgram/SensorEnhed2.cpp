//////////////////////////////////////
// Developed by Christian and David //
// Digitalizing is assuming reality //
//////////////////////////////////////
#include "SensorEnhed.hpp"

SensorEnhed::SensorEnhed(int SensorNummer)
{
    SensorNummer_ = SensorNummer;
    if(SensorNummer_ == 1){name_ = "TempSensor";}
    else if(SensorNummer_ == 2){name_ = "SaltSensor";}
    else if(SensorNummer_ == 3){name_ = "WaterLevelSensor";}
    //std::cout << "Constructor for SensorEnhed_" << SensorNummer_  << " with name: " << name_ << std::endl;
    iterator = 0;
}

//Gives more valuable graphs, again just dummy data.
double SensorEnhed::read()
{
    //std::cout << "SE: " << name_ << " getinput() for 1 second" << std::endl;
    //sleep(1);
    if(SensorNummer_ == 1){
    //Random number for
    if(iterator < 25){
        value = 21 + iterator * 0.2;
        iterator++;  
    }
    else if(iterator >= 25 && iterator < 60){
        value = 25.8 - (iterator-25) * 0.1; 
        iterator++;   
    }
    else if(iterator >= 60 && iterator < 96){
        value = 21 + (iterator-60) * 0.2 ;
        iterator++;   
    }
    else if(iterator == 96){
        iterator = 0;
    }
    }


 else if(SensorNummer_ == 2){
    //Random number for
    if(iterator < 25){
        value = 28 - iterator * 0.2;
        iterator++;  
    }
    else if(iterator >= 25 && iterator < 60){
        value = 25.8 + (iterator-25) * 0.1; 
        iterator++;   
    }
    else if(iterator >= 60 && iterator < 96){
        value = 29 - (iterator-60) * 0.2 ;
        iterator++;   
    }
    else if(iterator == 96){
        iterator = 0;
    }
 }


 else if(SensorNummer_ == 3){
    //Random number for
    if(iterator < 25){
        value = 24 + iterator * 0.1;
        iterator++;  
    }
    else if(iterator >= 25 && iterator < 60){
        value = 30 - (iterator-25) * 0.1; 
        iterator++;   
    }
    else if(iterator >= 60 && iterator < 96){
        value = 21 - (iterator-60) * 0.2 ;
        iterator++;   
    }
    else if(iterator == 96){
        iterator = 0;
    }

    }
    //cout << "SE: "<< name_ << " measured: " << value << endl;
    return value;
}

SensorEnhed::~SensorEnhed()
{
    cout << "Deleted SensorEnhed" << endl;
}