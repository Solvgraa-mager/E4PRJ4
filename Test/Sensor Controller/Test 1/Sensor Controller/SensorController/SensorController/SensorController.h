/* 
* SensorController.h
*
* Created: 27-04-2021 13:08:17
* Author: fogh1
*/



#ifndef __SENSORCONTROLLER_H__
#define __SENSORCONTROLLER_H__

//Includes
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "ADCBlokIF.hpp"
#include "CentralComputerIF.h"

class SensorController
{

//functions
public:
	SensorController(ADCBlokIF *ADCBlok, CentralComputerIF *CC);
	void Run();
	void Sleep();
	~SensorController();
private:
	ADCBlokIF *ADCBlok_;
	CentralComputerIF *CC_;
}; //SensorController

#endif //__SENSORCONTROLLER_H__
