#include "PID.hpp"

class Varmelegeme{
    
    private:
        PID * PIDregulerineg;
        int GPIO_;
    public:
        Varmelegeme();
        int setTemperatur(double temperatur, double maaltTemperatur);
        int temepratureToDutyCylce(double temp, int dutyCycleBuffer);
        int setGPIODutyCycle(int dutyCycle);
        ~Varmelegeme();
    
};