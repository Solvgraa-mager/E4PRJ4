#ifndef _AE_HPP
#define _AE_HPP


#include "Pumpe.hpp"
#include "Varmelegeme.hpp"
#include "PI.hpp"
#include <wiringPi.h>                   //Gør brug af wiring pi bibloteket. http://wiringpi.com/reference/software-pwm-library/
#include <softPwm.h>                    //Wiring pi, software PWM til GPIO pins.
#include <iostream>                     //For printfunktioner: cout

class Aktuatorenhed
{
    public:
        Aktuatorenhed(double volume, double saltKonc);
        int setTemperatur(double setTemperatur, double currentTemperatur);
        int setPsu(double setPsu, double currentPsu, double maxPsuChange);
        int setWaterLevel(double setWaterLevel, double currentWaterLevel, double currentPsu);
        int updateTemperature(double currentTemperature);
        ~Aktuatorenhed();
    
    protected: 
        int addPsu(double amountPsuToAdd);
        int substractPsu(double amountPsuTosubstract, double currentPsu);
        int addWater(double ml, double currentPsu);
        int removeWater(double ml);
        
        
    private: 
        double _volume;     //Total mængde vand i akvariet
        double _saltKonc;   //Saltkoncentrationen af saltvandet der tilføjes akvariet i procent
        Pumpe * _saltPumpe;
        Pumpe * _demiPumpe;
        Pumpe * _toemPumpe;
        Varmelegeme * _varmelegeme;
        PI * _PI;      
};

#endif