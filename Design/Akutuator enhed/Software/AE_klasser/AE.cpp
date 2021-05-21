#include "AE.hpp"
//#include <unistd.h> 

Aktuatorenhed::Aktuatorenhed(double volume, double saltKonc)
{
    _volume = volume;
    _saltKonc = saltKonc; 
    _saltPumpe = new Pumpe(1); 
    _demiPumpe = new Pumpe(2);    
    _toemPumpe = new Pumpe(3);  
    _varmelegeme = new Varmelegeme();
    _PID = new PID(1, 2, 3, 4, 5, 6); 
}

//###########PROTECTED MOTHODS


int Aktuatorenhed::addPsu(double psu)
{                      
    double ml = (_volume/(10*_saltKonc))*psu;       //Mængde saltvand der skal tilføjdes (se Analyse/Aktuatorenhed/Pumper)
     
    _toemPumpe->setDutyCycle(10);                   //dutycycle 10%, pumper langsomt 1 ml/0.07 sekunder
    _toemPumpe->setState(true);                     //Pumpe ON (fjerner akvarievand)
    sleep(ml * 0.07);                               //wait "pumping"
    _toemPumpe->setState(false);                    //Pumpe OFF


    _saltPumpe->setDutyCycle(10);                   //dutycycle 10%, pumper langsomt 1 ml/0.07 sekunder
    _saltPumpe->setState(true);                     //Pumpe ON  (tilføjer saltvand)
    sleep(ml * 0.07);                               //wait "pumping"
    _saltPumpe->setState(false);                    //Pumpe OFF

    return 0;
}

int Aktuatorenhed::substractPsu(double psu, double currentPsu)
{
    double ml = psuToMl(psu, currentPsu, _volume);  //retunere mængden af akvarievand der skal erstattes med demineraliseretvand for at reducere med x psu
    
    _toemPumpe->setDutyCycle(90);                   //dutycycle 90%, pumper hutigt 1 ml/0.044 sekunder
    _toemPumpe->setState(true);                     //Pumpe ON (fjerner akvarievand)
    sleep(ml * 0.044);                               //wait "pumping"
    _toemPumpe->setState(false);                    //Pumpe OFF


    _demiPumpe->setDutyCycle(90);                   //dutycycle 90%, pumper hutigt 1 ml/0.044 sekunder
    _demiPumpe->setState(true);                     //Pumpe ON  (tilføjer demineraliseret vand)
    sleep(ml * 0.044);                               //wait "pumping"
    _demiPumpe->setState(false);                    //Pumpe OFF
    
    return 0;
}

int Aktuatorenhed::addWater(double ml, double currentPsu)
{
    double mlSaltvand = (ml/(10*_saltKonc))*currentPsu; //Mængde saltvand der skal tilføjdes (se Analyse/Aktuatorenhed/Pumper)

    _demiPumpe->setDutyCycle(90);                   //dutycycle 90%, pumper hutigt 1 ml/0.044 sekunder
    _saltPumpe->setDutyCycle(90);                   //dutycycle 90%, pumper hutigt 1 ml/0.044 sekunder

    _saltPumpe->setState(true);                     //Pumpe ON  (tilføjer saltvand)
    _demiPumpe->setState(true);                     //Pumpe ON  (tilføjer demineraliseret vand)
    
    sleep(mlSaltvand * 0.044);                       //wait "pumping"

    _saltPumpe->setState(false);                    //Pumpe OFF

    sleep((ml-mlSaltvand) * 0.044);                 //wait "pumping"
    
    _demiPumpe->setState(false);                    //Pumpe OFF

   
    return 0;
}

int Aktuatorenhed::removeWater(double ml)
{
    _toemPumpe->setDutyCycle(90);                   //dutycycle 90%, pumper hutigt 1 ml/0.044 sekunder
    _toemPumpe->setState(true);                     //Pumpe ON (fjerner akvarievand)
    sleep(ml * 0.044);                               //wait "pumping"
    _toemPumpe->setState(false);                    //Pumpe OFF

    return 0;
}

int Aktuatorenhed::setTemperatur(double temperatur, double currentTemperatur)
{
    double reguleretTemerature;
    _PID->calculate(temperatur, currentTemperatur, reguleretTemerature); //PID regulering, 
    _varmelegeme->setTemperatur(reguleretTemerature, currentTemperatur);

    return 0;
}


int Aktuatorenhed::setWaterLevel(double setWaterLevel, double currentWaterLevel, double currentPsu)
{
    if (currentWaterLevel > setWaterLevel){
        removeWater(currentWaterLevel-setWaterLevel);
        return 1;
        }    
    else if (currentWaterLevel < setWaterLevel){
        addWater(setWaterLevel - currentWaterLevel, currentPsu);
        return 2;
        }
    
    return 0;

}

int Aktuatorenhed::setPsu(double setPsu, double currentPsu, double maxPsuChange)
{
    if (currentPsu > setPsu)
        {
        if ((currentPsu - setPsu) > maxPsuChange)
            {
            substractPsu(maxPsuChange, currentPsu);
            return 1;
            }
        else 
            {
            substractPsu(currentPsu-setPsu, currentPsu);
            return 2;
            }
        }    
    else if (currentPsu < setPsu)
        {
        if((setPsu - currentPsu) > maxPsuChange)
            {
            addPsu(maxPsuChange);
            return 3;
            }
        else
            {
            addPsu(setPsu - currentPsu);
            return 4;
            }     
    }
    return 0;
}


double Aktuatorenhed::psuToMl(double psu, double currentPsu, double volume)
{
    return (volume/currentPsu)*psu;
};

Aktuatorenhed::~Aktuatorenhed()
{
    delete _saltPumpe, _demiPumpe, _toemPumpe, _varmelegeme, _PID;
}



