class Pumpe
{
    public:
        Pumpe(int GPIO);
        int setDutyCycle(int dutyCycle);    //duty cycle 0-100%
        int setState(bool state);   //ON or Off
        int getDutyCycle(void);
        bool getState(void);
        ~Pumpe();
    private:
        int _speed;
        bool _state;
        int _GPIO;
};