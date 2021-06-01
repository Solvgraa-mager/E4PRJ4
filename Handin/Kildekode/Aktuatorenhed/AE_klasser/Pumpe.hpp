#ifndef _PUMPE_HPP
#define _PUMPE_HPP
class Pumpe
{
    public:
        Pumpe(int GPIO);
        void activatePump(int dutycycle);
        void deactivatePump();
        ~Pumpe();
    private:
        int _GPIO;
};

#endif 