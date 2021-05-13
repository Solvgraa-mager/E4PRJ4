/*
 * SensorController.cpp
 *
 * Created: 27-04-2021 12:58:54
 * Author : fogh1
 */ 

#include <avr/io.h>
#include "CentralComputerIF.h"
#include "Timer.hpp"
#include "ADCBlokIF.hpp"
#include "led.hpp"

int main(void)
{
	//DDRB |= 0b11110000;
	//ADCBlokIF ADCBlok;
	CentralComputerIF CC;
	//Timer T;
	
	//For test only
	initLEDport();
	
	char request = 0;
    while (1) 
    {
		request = CC.getRequest();
		CC.send(0xAAAA,0xFF,request);
    }
}

