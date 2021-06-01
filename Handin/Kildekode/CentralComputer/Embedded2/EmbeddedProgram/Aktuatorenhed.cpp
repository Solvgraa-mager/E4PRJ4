//////////////////////////////////////
// Developed by Christian and David //
// Digitalizing is assuming reality //
//////////////////////////////////////
#include "Aktuatorenhed.hpp"

//Contrstructor for Aktuatorenhed
Aktuatorenhed::Aktuatorenhed(double volume, double saltKonc)
{
    //std::cout << "Constructor for Aktuatorenhed" << std::endl;
    //std::cout << "AE: Volume = " << volume << std::endl;
    //std::cout << "AE: saltKonc = " << saltKonc << std::endl;
}

//Set light method for light on/off
void Aktuatorenhed::setLight(float light)
{
    //Functionality with PWM for designated Aktuatorenhed gruppe - for test with on/off..
    if(light == 1){
        cout << "AE: Light ON" << endl;
    }
    else{
        cout << "AE: Light OFF" << endl;
    }
    
}

//Set Psu method for adding water or saltwater to aquarium. Prints which is done according to inputtet parameters.
void Aktuatorenhed::setPsu(double salt, double currentSalt, double maxPsuChange)
{
    //cout << "AE: " << maxPsuChange << endl;
    double diff = salt - currentSalt;
    //cout << "AE: Salt difference ";
    //Functionality with PWM for designated Aktuatorenhed gruppe - for test of salinity
    //cout << diff << endl;
    if(diff > 0){
    cout << "AE: Start saltpump" << endl;
    sleep(1);
    //sleep(diff);
    cout << "AE: Stop saltpump" << endl;
    }
    else if (diff < 0){
    cout << "AE: Start waterpump" << endl;
    sleep(1);
    //sleep(-diff);
    cout << "AE: Stop waterpump" << endl;
    }
    //else { cout << "AE: Right amount of salt :)" << endl;}
}    

//Set waterlevel for changing waterlevel.
void Aktuatorenhed::setWaterLevel(double waterLevel, double currentWaterLevel, double currentSalt)
{
     double diff = waterLevel - currentWaterLevel;
     //cout << "AE: WaterLevel difference ";
     //cout << diff << endl;
     //Functionality with PWM for designated Aktuatorenhed gruppe - for test of waterLevel
     if(diff > 0){
        cout << "AE: Start waterpump + salt pump" << endl;
        sleep(1);
        //sleep(diff);
        cout << "AE: Stop waterpump + salt pump" << endl;
    }
    else if (diff < 0){
        cout << "AE: Start remove water pump" << endl;
        sleep(1);
        //sleep(-diff);
        cout << "AE: Stop remove water pump" << endl;
    }
    //else { cout << "AE: Right amount of water :)" << endl;}
     
}

//Set temperaturmethod - just output that PWM is updated
void Aktuatorenhed::setTemperature(double temperature, double currentTemperature)
{
    double diff = temperature - currentTemperature;
    cout << "AE: Temp set" << endl;
    // - setPWM for temperature with difference to setPoint" << diff << endl;   
}

//Destructor for AktautorEnhed
Aktuatorenhed::~Aktuatorenhed()
{

}