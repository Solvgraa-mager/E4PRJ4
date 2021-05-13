#include "Sensor.hpp"
#include "Exception.hpp"
#include <iostream>
#include <unistd.h>

using namespace std;

int main(void){

    Sensor S(1,"/home/stud/E4PRJ4/Implementering/Sensor Controller/SensorControllerDriver/testConfig.txt");
    S.sensorRead();
    return 0; 
}