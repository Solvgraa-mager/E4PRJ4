#include "Pumpe.hpp"

Pumpe::Pumpe(int GPIO)
 {
    _GPIO = GPIO;

    int err = softPwmCreate(_GPIO, 0, 100);      //initialize GPIO til PWM pin, med range 0-100%
    if (err != 0)
        std::cout << "PWM pin for pump, with GPIO (" << _GPIO << ") not initialized. ERROR: " << err << endl;   
    softPwmWrite(_GPIO, 0);
}

void Pumpe::activatePump(int dutycycle)
{
    softPwmWrite(_GPIO, dutycycle);              //wiring pi metode. Sætter PWM dutycycle
}

void Pumpe::deactivatePump()
{
    softPwmWrite(_GPIO, 0);                      //wiring pi metode. Sætter PWM dutycycle 
}

Pumpe::~Pumpe()
 {
    softPwmWrite(_GPIO, 0);                      //Wiring pi frigiver selv GPIO pins. 
 }