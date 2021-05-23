#include "Varmelegeme.hpp"

Varmelegeme::Varmelegeme()
{
    PIDregulerineg = new PID(1,2,3,4,5,6);

}


int Varmelegeme::setTemperatur(double temperatur, double maaltTemperatur)
{
    double result;
    int dutyCycle;
    
    PIDregulerineg->calculate(temperatur, maaltTemperatur, result);  
    double temperaturOut = PIDregulerineg->getOutput();

    temepratureToDutyCylce(temperaturOut, dutyCycle);
    //set GPIO port til ønsket duty cycle.
    return 0;
}

int Varmelegeme::temepratureToDutyCylce(double temperature, int dutyCycleBuffer)
{   
    //############### MATEMATIK ##########

    int k = 1;  //konstant eller funktion der oversætter en temperatur til en dutycycle. 
                //Denne konstant/Funktion kan ikke laves før vi ved hvad de forskellige
                //pulsbredder giver af temperatur. AKA freddy skal lave sin tmperatur
                //del færdig først.
    dutyCycleBuffer = temperature*k;
    
    return 0;
}

Varmelegeme::~Varmelegeme()
{
    delete PIDregulerineg;
}
