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
bool TempFlag;
double currentTemperature;
bool LightFlag;
bool SaltFlag;
double currentSalt;
float salt;
float light;
float waterLevel;
float temperature;
double currentWaterLevel;

//Constants
const int period = 1;
const int heaterPeriod = 2;
const int timeHeat = 1;

//Objects of classes
SensorEnhed tempSensor(1);
SensorEnhed saltSensor(2);
SensorEnhed waterLevelSensor(3);
Init_ini Initfil;
AktuatorEnhed Aktuator;


// <-------- Use Case 1 - Measurements -------> //
PI_THREAD(MEASUREMENTS)
{
  int i = 0;
  string minuteString;
  string hourString;
  string hourStringTMP;
  int hour = 0;
  int minute = 0;
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
    string intro = "INSERT INTO measurements (temp, waterLevel, salt, dateTime) VALUES(";
    string seperator = ", ";
    
    string timeStamp = "2021-05-22 ";
    
    if(i%4 == 0){
      minute = 0;
       minuteString = "00";
       cout << "0" << endl;

      if(hour < 10 && hour > 0){
        hourStringTMP = to_string(hour);
        hourString = "0" + hourStringTMP;
       
        cout << "1" << endl;
      }
      else if(hour >= 10 && hour < 24){
        hourStringTMP = to_string(hour);
        hourString = hourStringTMP;
        
        cout << "2" << endl;
      }
      else if(hour == 24 || hour == 0){
        hour = 0;
        hourString = "00";
        cout << "3" << endl;
        
      }
      hour++;
    }
    else if(i%4 == 1){
      minute = 15;
       minuteString = to_string(minute);
       cout << "4" << endl;
    }
     else if(i%4 == 2){
      minute = 30;
       minuteString = to_string(minute);
       cout << "5" << endl;
    }
     else if(i%4 == 3){
      minute = 45;
       minuteString = to_string(minute);
       cout << "6" << endl;
    }
   

    string last = ");"; 
    string colon = ":";
    string secondString = "00";
    
    //Put string togehter and cout for terminaltest
    string upload_msg = intro + tempString + seperator + saltString + seperator + waterLevelString + seperator + "'" + timeStamp + hourString + colon + minuteString + colon + secondString + "'" + last;
    std::cout << "MEASUREMENT: Upload message for database: " << upload_msg << std::endl;

    //Mysql upload with valid string
    Initfil.MysqlUpload(upload_msg);
   
    //Stop stopwatch, read duration cout for terminal and sleep for the wished time with handling of the thread termination time.
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end-start;
    cout << "MEASUREMENT: Time spent " << elapsed_time.count() << endl;

    auto start2 = std::chrono::high_resolution_clock::now();
    //By test 2 we found an average of 0.0001 - could be implemented with chrono... Yet it works
    usleep(((period - elapsed_time.count()) - 0.0001)*1000000); 
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time2 = end2-start2;
    cout << "MEASUREMENT: Time slept" << elapsed_time2.count() << endl; 
    i++;
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
  //piThreadCreate(SWL);
  //piThreadCreate(TMP);
  while(1){};
  return 0;
}



