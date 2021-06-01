#include "AE.hpp"


Aktuatorenhed AE(30000, 26.3);

int main(void)
{
    

    //tråd 1 en gang hver 15 min
    AE.setPsu(GUI.getsalt(), sensor.getsalt(),0.25);
    AE.setTemperatur(30,21);
    
    AE.setWaterLevel(25, sensor.getWaterLevel(), sensor.getsalt())


    //tråd 2 en gang hver 60 sek
    AE.updateTemperature(sensor.getsalt());
}
