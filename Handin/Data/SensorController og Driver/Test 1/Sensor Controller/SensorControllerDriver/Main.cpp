#include "Sensor.hpp"
#include "Exception.hpp"
#include <iostream>
#include <unistd.h>

using namespace std;

int main(void){

    try
    {
        for(int i = 0; i<4;i++){
        Sensor S0(i,"testConfig.txt");
        cout << S0.sensorRead() << endl; 
        sleep(3);
        }

    }
    catch(const Exception& e)
    {
        std::cerr << e.getError() << '\n';
    }
    return 0; 
}