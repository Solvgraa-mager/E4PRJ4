class Pumpe
{
    public:
        Pumpe(int GPIO);
        int setSpeed(int speed);    //duty cycle 0-100%
        int setState(bool state);   //ON or Off
        int getSpeed(void);
        bool getState(void);
        ~Pumpe();
    private:
        int _speed;
        bool _state;
        int _GPIO;
};