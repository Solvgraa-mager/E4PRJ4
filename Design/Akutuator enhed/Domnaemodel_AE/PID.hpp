class PID{
    private:
        double _Kp;         //proportional konstant
        double _Ki ;        //Integral konstant
        double _Kd;         //Differntial konstant
        double _deltaTime;  //Tid mellem hvert sample (bruges til integral regning)
        double _preError;   //Afstand mellem setpoint og mplte værdi 
        double _integral;   //Samlet integrale
        double _minOut;      
        double _maxOut;
        double _out;
    public:
        PID(double Kp, double Ki, double Kd, double dt, double minOut, double maxOut);
        int calculate(double setpoint, double measured, double resultBuffer);
        void setKp(double Kp);
        void setKi(double Kp);
        void setKd(double Kp);
        double getKp(void);
        double getKi(void);
        double getKd(void);
        double getOutput(void);
    };
