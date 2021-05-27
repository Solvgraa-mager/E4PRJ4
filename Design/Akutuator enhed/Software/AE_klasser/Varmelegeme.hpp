#ifndef _VARMELEGEME_HPP
#define _VARMELEGEME_HPP
class Varmelegeme{
    
    private:
        int _GPIO;
    public:
        Varmelegeme(int GPIO);
        int setDutycycle(double dutycycle);
};

#endif