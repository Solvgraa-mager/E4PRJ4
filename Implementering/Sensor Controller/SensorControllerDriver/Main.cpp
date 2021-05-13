#include "Sensor.hpp"
#include "Exception.hpp"
#include <iostream>
#include <unistd.h>

using namespace std;

int main(void){

    try
    {
        Sensor S1(3,"testConfig.txt");

            S1.sensorRead();
 
    }
    catch(const Exception& e)
    {
        std::cerr << e.getError() << '\n';
    }

    return 0; 
}