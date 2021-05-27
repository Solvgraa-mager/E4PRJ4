#include "Varmelegeme.hpp"

Varmelegeme::Varmelegeme(int GPIO)
{
    _GPIO = GPIO;

    int err = softPwmCreate(_GPIO, 0, 100);         //initialize GPIO til PWM pin, med range 0-100%
    if (err != 0)
        std::cout << "PWM pin for varmelegeme, with GPIO (" << _GPIO << ") not initialized. ERROR: " << err << endl;
    softPwmWrite(_GPIO, 0); 
}

 int Varmelegeme::setDutycycle(double dutycycle)
{
    softPwmWrite(_GPIO, (int)dutycycle);                 //wiring PI metode. Sætter PWM dutycycle. 
}

Varmelegeme::~Varmelegeme()
{
    softPwmWrite(_GPIO, 0);                         //Sætter dutycycle til 0, Wiring PI frigiver selv GPIO porten.
}