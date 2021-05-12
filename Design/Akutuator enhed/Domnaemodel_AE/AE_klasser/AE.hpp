#include "Pumpe.hpp"
#include "Varmelegeme.hpp"
#include "PID.hpp"

class Aktuatorenhed
{
    public:
        Aktuatorenhed(double volume, double saltKonc);
        int setTemperatur(double setTemperatur, double currentTemperatur);
        int setPsu(double setPsu, double currentPsu, double maxPsuChange);
        int setWaterLevel(double setWaterLevel, double currentWaterLevel, double currentPsu);
        ~Aktuatorenhed();
    
    protected: 
        double psuToMl(double psu, double currentPsu, double volume);
        int addPsu(double psu);
        int substractPsu(double psu, double currentPsu);
        int addWater(double ml, double currentPsu);
        int removeWater(double ml);
        
    private: 
        double _volume;     //Total mængde vand i akvariet
        double _saltKonc;   //Saltkoncentrationen af saltvandet der tilføjes akvariet i procent
        Pumpe * _saltPumpe;
        Pumpe * _demiPumpe;
        Pumpe * _toemPumpe;
        Varmelegeme * _varmelegeme;
        PID * _PID;

       
};