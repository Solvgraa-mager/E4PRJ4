#include "Varmelegeme.hpp"
#define HALF_HERTZ_CONSTANT 2000000/100                            //Opløsning af PWM = 100ms. 2 mil = 0.5 Hz. 1%PWM = 2mil/100

Varmelegeme::Varmelegeme(int GPIO)
{
    _GPIO = GPIO;

    int err = softPwmCreate(_GPIO, 0, 2000000);                         //initialize GPIO til PWM pin, 0.5 Hz med range 0-100%
    if (err != 0)
        std::cout << "PWM pin for varmelegeme, with GPIO (" << _GPIO << ") not initialized. ERROR: " << err << endl;
    softPwmWrite(_GPIO, 0); 

    
}

 int Varmelegeme::setDutycycle(double dutycycle)
{
    softPwmWrite(_GPIO, (int)(dutycycle*HALF_HERTZ_CONSTANT));      //wiring PI metode. Sætter PWM dutycycle.                                                                     //
}                                                                        //convertere dutycycle til hvor mange steps af de 2 milioner, der skal være on.

Varmelegeme::~Varmelegeme()
{
    softPwmWrite(_GPIO, 0);                                             //Sætter dutycycle til 0, Wiring PI frigiver selv GPIO porten.
}