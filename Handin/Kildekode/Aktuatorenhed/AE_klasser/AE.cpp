#include "AE.hpp"
//#include <unistd.h> 

Aktuatorenhed::Aktuatorenhed(double volume, double saltKonc)
{
    _volume = volume;
    _saltKonc = saltKonc; 
    _saltPumpe = new Pumpe(1); 
    _demiPumpe = new Pumpe(2);    
    _toemPumpe = new Pumpe(3);  
    _varmelegeme = new Varmelegeme(4);
    _PI = new PI(46.0802, 0.00034014, 60, 0, 100);          //Kp, Ti og Ts udregnet i design af temperturregulator
}


int Aktuatorenhed::addPsu(double amountPsuToAdd)
{                      
    double ml = (_volume/(10*_saltKonc))*amountPsuToAdd;       //Mængde saltvand der skal tilføjdes (se Analyse/Aktuatorenhed/Pumper)
     
    _toemPumpe->activatePump(10)                    //dutycycle 25%, pumper langsomt 1 ml pr 0.062 sekunder
    sleep(ml * 0.062);                               //wait "pumping" (fjerner akvarievand)
    _toemPumpe->deactivatePump();                    //Pumpe OFF

    _saltPumpe->activatePump(10);                   //dutycycle 25%, pumper langsomt 1 ml pr 0.062 sekunder
    sleep(ml * 0.062);                               //wait "pumping" (tilføjer saltvand)
    _saltPumpe->deactivatePump();                    //Pumpe OFF

    return 0;
}

int Aktuatorenhed::substractPsu(double psu, double currentPsu)
{
    double ml = psuToMl(psu, currentPsu, _volume);  //retunere mængden af akvarievand der skal erstattes med demineraliseretvand for at reducere med x psu
    
    _toemPumpe->activatePump(90);                    //dutycycle 100%, pumper hutigt 1 ml pr 0.042 sekunder
    sleep(ml * 0.042);                               //wait "pumping" (fjerner akvarievand)
    _toemPumpe->deactivatePump();                    //Pumpe OFF

    _demiPumpe->activatePump(90);                    //dutycycle 100%, pumper hutigt 1 ml/0.042 sekunder
    sleep(ml * 0.042);                               //wait "pumping" (tilføjer demineraliseret vand)
    _demiPumpe->deactivatePump();                    //Pumpe OFF
    
    return 0;
}

int Aktuatorenhed::addWater(double ml, double currentPsu)
{
    double mlSaltvand = (ml/(10*_saltKonc))*currentPsu; //Mængde saltvand der skal tilføjdes (se Analyse/Aktuatorenhed/Pumper)

    _demiPumpe->activatePump(90);                    //dutycycle 100%, pumper hutigt 1 ml/0.042 sekunder
    _saltPumpe->activatePump(90);;                   //dutycycle 100%, pumper hutigt 1 ml/0.042 sekunder
    sleep(mlSaltvand * 0.042);                       //wait "pumping" (tilføjer saltvand og demineraliseret vand) 

    _saltPumpe->deactivatePump();                    //Saltvandspumpe OFF
    sleep((ml-mlSaltvand) * 0.042);                  //wait "pumping" (demineraliseret vand) 
    _demiPumpe->deactivatePump();                    //Demineraliseret vandpumpe OFF

    return 0;
}

int Aktuatorenhed::removeWater(double ml)
{
    _toemPumpe->activatePump(90);                   //dutycycle 100%, pumper hutigt 1 ml/0.042 sekunder
    sleep(ml * 0.042);                               //wait "pumping" (fjerner akvarievand)
    _toemPumpe->deactivatePump();                    //Pumpe OFF

    return 0;
}

int Aktuatorenhed::setTemperatur(double temperatur)
{
    _PI->setNewSetpoint(temperatur);                //Setpoint sættes hvert kvarter
    _PI->rateLimit();                               //Setpoint begrænses således én grader celsius pr time overholdes. 

    return 0;
}

int Aktuatorenhed::updateTemperature(double currentTemperature)
{
    int dutycycle;
    int report = _PI->calculate(currentTemperature, 0, 100, dutycycle); //Regulere temperturen, og retunere en dutycycle. 
    _varmelegeme->setDutycycle(dutycycle);                              //varmelegemet opdateres til dutycyclen fra reguleringen 
    
    return report;                                                      //retunere om reguleringen gik i mætning. min max eller non.
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

Aktuatorenhed::~Aktuatorenhed()
{
    delete _saltPumpe, _demiPumpe, _toemPumpe, _varmelegeme, _PID;
}



