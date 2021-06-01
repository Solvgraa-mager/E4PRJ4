//////////////////////////////////////
// Developed by Christian and David //
// Digitalizing is assuming reality //
//////////////////////////////////////
#pragma once
#include <string>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Aktuatorenhed{
public:
    Aktuatorenhed(double, double);
    void setLight(float);
    void setPsu(double, double, double);
    void setWaterLevel(double, double, double);
    void setTemperature(double, double);

    ~Aktuatorenhed();
 

private:

};