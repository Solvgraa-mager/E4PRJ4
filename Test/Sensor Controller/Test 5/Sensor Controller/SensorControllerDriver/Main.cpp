#include "Sensor.hpp"
#include "Exception.hpp"
#include <iostream>
#include <unistd.h>

using namespace std;

int main(void){

    try
    {
        Sensor S0(0,"testConfig.txt");
        for(int i = 0; i<100; )
        {
            cout << "Reading: " << S0.sensorRead() << endl;
            usleep(50000);
        }
    }
    catch(const Exception& e)
    {
        std::cerr << e.getError() << '\n';
    }
    return 0; 
}