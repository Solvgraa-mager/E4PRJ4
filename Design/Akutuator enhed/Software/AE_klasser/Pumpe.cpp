#include "Pumpe.hpp"

Pumpe::Pumpe(int GPIO)
 {
    setDutyCycle(0);
    setState(false);
    //############## INIT GPIO PIN ################
      int _GPIO = GPIO;

 }

int Pumpe::setDutyCycle(int speed)    //duty cycle 0-100%
{
    //_GPIO får sat sin duty cycle til speed
    
}
int Pumpe::setState(bool state)   //ON or Off
{
    _state = state;
}

int Pumpe::getDutyCycle(void)
{
    return _speed;
}

bool Pumpe::getState(void){
    return _state;
}

Pumpe::~Pumpe()
 {
    setDutyCycle(0);
    setState(false);
    //############## terminate GPIO PIN ###############

 }