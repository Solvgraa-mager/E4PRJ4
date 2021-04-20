#include "PID.hpp"

PID::PID(double Kp, double Ki, double Kd, double dt, double minOut, double maxOut){
        _Kp = Kp;
        _Ki = Ki;
        _Kd = Kd;
        _deltaTime = dt;
        _preError = 0;
        _integral = 0;
        _out = 0;
    }

int PID::calculate(double setpoint, double measured, double resultBuffer){
        
    double error = setpoint-measured;   //calculate error

    //-------------Proportional part--------------

    double pOut = _Kp * error;         //proportional part

    //-------------Integral part-----------------
    _integral = error * _deltaTime;    //Integral
    double iOut = _Ki * _integral;     //Integral part

    //-------------Derivative part-----------------
    double derivative, dOut;
    if (_preError != 0)                //Sikre der er taget min to målinger, før hældningen udregnes.
    {
        derivative = (error - _preError) / _deltaTime;
        dOut = derivative * _Kd;
    }
    //-------------Total out------------------------
    _out = pOut + iOut + dOut;

    if (_out < _minOut)
        _out = _minOut;
    if (_out > _maxOut)
        _out = _maxOut;

    resultBuffer = _out;
    _preError = error;                  //save last error.

    return 0;
    
    }

double PID::getOutput(){
    return _out;
}