#include "Sensor.hpp"
#include "Exception.hpp"
#include <iostream>
#include <unistd.h>

using namespace std;

int main(void){

    try
    {
        Sensor S1(2,"testConfig.txt");
        S1.readRaw();
 
    }
    catch(const Exception& e)
    {
        std::cerr << e.getError() << '\n';
    }

    return 0; 
}