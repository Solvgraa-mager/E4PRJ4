#include <iostream>
#include <wiringPi.h>
#include <unistd.h>
#include <string>
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include "Init_ini.hpp"
#include "SensorEnhed.hpp"
#include "AktuatorEnhed.hpp"
using namespace std;

//Flags and doubles from sensorInput
double currentWaterLevel, currentSalt, currentTemperature;
bool LightFlag, SaltFlag, TempFlag;;
float salt, light, waterLevel, temperature;

//Constants
const int period = 10;
const int heaterPeriod = 2;
const int timeHeat = 1;
//This value is added my measurements, where the drift
// with chrono compensation is active.. 
const double drift = 0.008935127;

//Objects of classes
SensorEnhed tempSensor(1);
SensorEnhed saltSensor(2);
SensorEnhed waterLevelSensor(3);
Init_ini Initfil;
AktuatorEnhed Aktuator;


// <-------- Use Case 1 - Measurements -------> //
PI_THREAD(MEASUREMENTS)
{
  while(1){
    //Start stopwatch
    auto start = std::chrono::high_resolution_clock::now();


    //Startup message
    // std::cout << endl << endl << "Measurement - THREAD" << std::endl;

    //Read temperature and pass to string
    temperature = (float)tempSensor.getSensorInput();
    string tempString = std::to_string(temperature);

    //Read salt and pass to string
    salt = (float)saltSensor.getSensorInput();
    string saltString = std::to_string(salt);

    //Read waterlevel and pass to string
    waterLevel = (float)waterLevelSensor.getSensorInput();
    string waterLevelString = std::to_string(waterLevel);

    //String constants
    string intro = "INSERT INTO measurements (temp, waterLevel, salt) VALUES(";
    string seperator = ", ";
    string last = ");"; 

    //Put string togehter and cout for terminaltest
    string upload_msg = intro + tempString + seperator + saltString + seperator + waterLevelString + last;
    //std::cout << "MEASUREMENT: Upload message for database: " << upload_msg << std::endl;

    //Mysql upload with valid string
    Initfil.MysqlUpload(upload_msg);
   
    //Stop stopwatch, read duration cout for terminal and sleep for the wished time with handling of the thread termination time.
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end-start;
    cout << "MEASUREMENT: Time spent " << elapsed_time.count() << endl;

    auto start2 = std::chrono::high_resolution_clock::now();
    //By test 2 we found an average of 0.0001 - could be implemented with chrono...Yet it works
    usleep(((period - elapsed_time.count()) - drift)*1000000); 
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time2 = end2-start2;
    cout << "MEASUREMENT: Time slept" << elapsed_time2.count() << endl; 
  }
}
 
// <-------- Use Case 1 - Salt WaterLevel Light -------> //
PI_THREAD(SWL)
{
  //With inspiration from https://en.cppreference.com/w/cpp/chrono
  //Take two timestamps before and after the needed proces.. Difference gives the time it took
  //Then wait for the time before threads should execute again.Plus offset here ->
  sleep(4);
  while(1){
    //Start stopwatch
    auto start = std::chrono::high_resolution_clock::now();
    // cout << endl << endl << "SWL - THREAD" << endl;
    
    //Light read and set
    //Connection and data acqusition
    //cout << "SWL: Read LightFlag..." << endl;
    if(Initfil.getFlag("LightFlag") == true){
      //cout << "SWL: LightFlag ON" << endl;
      //cout << "SWL: Setting Light" << endl;
      light = Initfil.getSetPoint("Light");
      Aktuator.setLight(light);
    } 
    //else{cout << "SWL: OFF" << endl;}

    //cout << "SWL: Read SaltFlag..." << endl;
    if(Initfil.getFlag("SaltFlag") == true){
      //cout << "SWL: SaltFlag ON" << endl;
      //cout << "SWL: Setting Salt" << endl;
      currentSalt = saltSensor.getSensorInput();
      salt = Initfil.getSetPoint("Salt");
      Aktuator.setSalt((double)salt, currentSalt);

      //AND then waterlevel
      currentWaterLevel = waterLevelSensor.getSensorInput(); 
      waterLevel = Initfil.getSetPoint("WaterLevel");
      Aktuator.setWaterLevel((double)waterLevel, currentWaterLevel);

    }
    //else{ cout << "SWL: SaltFlag OFF" << endl; }
     
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end-start;
    //Sleep for time until period is fulfilled
    //cout << "SWL: Time spent " << elapsed_time.count() << endl;
    
    usleep((period - elapsed_time.count())*1000000);
    //Simple sleep for test
  }
}

// <-------- Use Case 1 - Temperature -------> //
PI_THREAD(TMP)
{
  while(1){
    auto start = std::chrono::high_resolution_clock::now();
    //cout << "TMP: Read TempFlag..." << endl;
    if(Initfil.getFlag("TempFlag") == true){
        //cout << "TMP: TempFlag ON" << endl;
        //cout << "TMP: Setting heat" << endl;
        currentTemperature = tempSensor.getSensorInput(); 
        temperature = Initfil.getSetPoint("Temp");
        Aktuator.setTemperature((double)temperature, currentTemperature);
    }
    //else{cout << "TMP: TempFlag OFF" << endl;}
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed_time = end-start;
    //Sleep for time until period is fulfilled
    //cout << "TMP: Time spent " << elapsed_time.count() << endl;
    usleep((heaterPeriod - elapsed_time.count())*1000000);
    //Simple sleep for test
  }
}


// <------------- MAIN ------------->> //
int main(int argc, char **argv)
{
  piThreadCreate(MEASUREMENTS);
  piThreadCreate(SWL);
  piThreadCreate(TMP);
  while(1){};
  return 0;
}



