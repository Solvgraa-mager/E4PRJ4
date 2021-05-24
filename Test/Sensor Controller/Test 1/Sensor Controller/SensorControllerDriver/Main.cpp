#include "Sensor.hpp"
#include "Exception.hpp"
#include <iostream>
#include <unistd.h>

using namespace std;

int main(void){

    try
    {
        Sensor S0(0,"testConfig.txt");
        S0.sensorRead();
        sleep(3);
        Sensor S1(1,"testConfig.txt");
        S0.sensorRead();
        sleep(3);
        Sensor S2(2,"testConfig.txt");
        S0.sensorRead();
        sleep(3);
        Sensor S3(3,"testConfig.txt");
        S0.sensorRead();
        sleep(3);
    }
    catch(const Exception& e)
    {
        std::cerr << e.getError() << '\n';
    }
    return 0; 
}