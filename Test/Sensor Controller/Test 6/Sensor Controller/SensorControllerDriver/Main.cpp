#include "Exception.hpp"
#include "Sensor.hpp"
#include <chrono>
#include <iostream>
#include <unistd.h>

using namespace std;


int main(void)
{
  cout << "Test 6, Channel 0 active" << endl;
  try
  {
    
    for (int i = 0; i < 1000; i++)
    {
        Sensor S0((i%4), "testConfig.txt");
        cout << "Run #"<< i; 
        S0.sensorRead(); 
        usleep(50000);
    }
  }
  catch (const Exception &e)
  {
    std::cerr << e.getError() << '\n';
  }
  return 0;
}