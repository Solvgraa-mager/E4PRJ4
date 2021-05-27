#ifndef _PI_HPP
#define _PI_HPP

class PI{
    private:
        double _Kp;             //proportional konstant
        double _Ti;            //Integral konstant
        double _Ts;             //Tid mellem hvert sample
        double _preError;       //Afstand mellem setpoint og mplte værdi 
        double _preIntegral;       //Samlet integrale
        double _minOut;         //Minimum afgrænsning (0% dutycycle)
        double _maxOut;         //Maximum afgrænsning (100% dutycycle)
        double _setpoint;       //aktuelle setpoint for regulatoren
        double _oldSetpoint;    //sidste setpoint for regulatoren
        double _newSetpoint;    //nye etpoint for regulatoren (gående fra setpoint mod newSetpoint i rateLimiter)
    public:
        PI(double Kp, double Ti, double Ts, double minOut, double maxOut);
        int calculate(double measured, double resultBuffer);
        void setNewSetpoint(double newSetpoint);
        void rateLimit();
    };

#endif