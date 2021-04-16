#include "Pumpe.hpp"

Pumpe::Pumpe(int GPIO)
 {
    setSpeed(0);
    setState(false);
    //############## INIT GPIO PIN ################
      int _GPIO = GPIO;

 }

int Pumpe::setSpeed(int speed)    //duty cycle 0-100%
{
    //_GPIO får sat sin duty cycle til speed
    
}
int Pumpe::setState(bool state)   //ON or Off
{
    _state = state;
}

int Pumpe::getSpeed(void)
{
    return _speed;
}

bool Pumpe::getState(void){
    return _state;
}