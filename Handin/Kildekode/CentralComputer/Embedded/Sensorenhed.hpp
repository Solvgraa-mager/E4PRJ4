//////////////////////////////////////
// Developed by Christian and David //
// Digitalizing is assuming reality //
//////////////////////////////////////
#pragma once
#include <iostream>
#include <wiringPi.h>
#include <unistd.h>
#include <string>
#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
using namespace std;

class Sensorenhed{
public:
    Sensorenhed(int);
    double read();
    ~Sensorenhed();

private:
    int _sensorNumber;
    string name_;
    double value;
    int iterator;
};
