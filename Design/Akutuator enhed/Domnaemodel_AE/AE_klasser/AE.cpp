#include "AE.hpp"

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

int Aktuatorenhed::addPsu(double psu)
{                      
    double ml = (_volume/(10*_saltKonc))*psu;       //Mængde saltvand der skal tilføjdes (se Analyse/Aktuatorenhed/Pumper)
     
    _toemPumpe->setDutyCycle(10);                   //dutycycle 10%, pumper langsomt 1 ml/0.07 sekunder
    _toemPumpe->setState(true);                     //Pumpe ON (fjerner akvarievand)
    //-------- Wait ml*0.07 ------------
    _toemPumpe->setState(false);                    //Pumpe OFF


    _saltPumpe->setDutyCycle(10);                   //dutycycle 10%, pumper langsomt 1 ml/0.07 sekunder
    _saltPumpe->setState(true);                     //Pumpe ON  (tilføjer saltvand)
   
    //-------- Wait ml*0.07 ------------
    _saltPumpe->setState(false);                    //Pumpe OFF

    return 0;
}

int Aktuatorenhed::substractPsu(double psu, double currentPsu)
{
    double ml = psuToMl(psu, currentPsu, _volume);  //retunere mængden af akvarievand der skal erstattes med demineraliseretvand for at reducere med x psu
    
    _toemPumpe->setDutyCycle(90);                   //dutycycle 90%, pumper hutigt 1 ml/0.044 sekunder
    _toemPumpe->setState(true);                     //Pumpe ON (fjerner akvarievand)
    //-------- Wait ml*0.044 ------------
    _toemPumpe->setState(false);                    //Pumpe OFF


    _demiPumpe->setDutyCycle(90);                   //dutycycle 90%, pumper hutigt 1 ml/0.044 sekunder
    _demiPumpe->setState(true);                     //Pumpe ON  (tilføjer demineraliseret vand)
    //-------- Wait ml*0.044 ------------
    _demiPumpe->setState(false);                    //Pumpe OFF
    
    return 0;
}

int Aktuatorenhed::addWater(double ml, double currentPsu)
{
    double mlSaltvand = (ml/(10*_saltKonc))*currentPsu; //Mængde saltvand der skal tilføjdes (se Analyse/Aktuatorenhed/Pumper)

    _saltPumpe->setDutyCycle(90);                   //dutycycle 90%, pumper hutigt 1 ml/0.044 sekunder
    _saltPumpe->setState(true);                     //Pumpe ON  (tilføjer saltvand)
    //-------- Wait mlSaltvand*0.044 ------------
    _saltPumpe->setState(false);                    //Pumpe OFF


    _demiPumpe->setDutyCycle(90);                   //dutycycle 90%, pumper hutigt 1 ml/0.044 sekunder
    _demiPumpe->setState(true);                     //Pumpe ON  (tilføjer demineraliseret vand)
    //-------- Wait (ml-mlSaltvand)*0.044 ------
    _demiPumpe->setState(false);                    //Pumpe OFF

    return 0;
}

int Aktuatorenhed::removeWater(double ml)
{
    _toemPumpe->setDutyCycle(90);                   //dutycycle 90%, pumper hutigt 1 ml/0.044 sekunder
    _toemPumpe->setState(true);                     //Pumpe ON (fjerner akvarievand)
    //-------- Wait ml*0.044 ------------
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

Aktuatorenhed::~Aktuatorenhed()
{
    delete _saltPumpe, _demiPumpe, _toemPumpe, _varmelegeme, _PID;
}
