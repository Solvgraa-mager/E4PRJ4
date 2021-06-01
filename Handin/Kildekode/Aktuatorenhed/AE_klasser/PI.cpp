



#include "PI.hpp"
#define 

PI::PI(double Kp, double Ti, double Ts, double minOut, double maxOut){
        _Kp = Kp;                       //proportional konstant
        _Ti = Ti;                       //Integral konstant
        _Ts = Ts;                       //Tid mellem hvert sample
        _preError = 0;                  //Afstand mellem setpoint og mplte værdi 
        _preIntegral = 0;               //Samlet integrale        
        _minOut = minOut;               //Minimum afgrænsning (0% dutycycle)
        _maxOut = maxOut;               //Maximum afgrænsning (100% dutycycle)
        _setpoint = 0;                  //aktuelle setpoint for regulatoren
        _oldSetpoint = 0;               //sidste setpoint for regulatoren
        _newSetpoint = 0;               //nye etpoint for regulatoren (gående fra setpoint mod newSetpoint i rateLimiter)
    }

int PI::calculate(double measured, double resultBuffer){
        
    double error = _setpoint-measured;   //calculate error

    //-------------Proportional part--------------

    double proportional = error;         //proportional part

    //-------------Integral part-----------------
  
    double integral = (_Ts/2)*(error+_preError)+_preIntegral;

    //-------------Anti windyp -------------------

    double maxIntegral = (100*_Ti)/_Kp;     //Integralets afgrænses, såledsden alene ikke kan leveremere end 100% pwm.

    if (integral > maxIntegral) 
        integral = maxIntegral;
    else if (integral < 0)
        integral = 0;

    //-------------control signal------------------------
    double controlSignal = _Kp*(proportional+(1/_Ti)*integral);




    if (controlSignal < _minOut)            //minimum output
        controlSignal = _minOut;            
    else if (controlSignal > _maxOut)       //Maximum output
        controlSignal = _maxOut;

    resultBuffer = controlSignal;           //return result
    _preError = error;                      //save last error
    _preIntegral = integral;                //save last integral
    

    //--------------------Return report---------------------

    if (controlSignal == _minOut)           //return output was limited by minumum 
        return -1;          
    else if (controlSignal == _maxOut)      //return output was limited by maximum 
        return -2;

    return 0;                               //return output was not limited 
    
    }


void PI::setNewSetpoint(double newSetpoint)
{
    _newSetpoint = newSetpoint;
}

void PI::rateLimit()
    {
        if (_newSetpoint - _oldSetpoint > 0.25)	 //undersøger forkel på sidste setpoint og nyt setpoint
        {                                        //0.25 er max steps PI regulatoren må ændre pr kvarter.                                            
            _setpoint = _oldSetpoint + 0.25;     //Aktuelle stepoint rykkes 0.25 grader op
            _oldSetpoint = _setpoint;            //Husker sidste setpoint 
        }
        else
        {
            _setpoint = _newSetpoint;            //temperturen er opnået, eller der nedkøles.
        }
    }