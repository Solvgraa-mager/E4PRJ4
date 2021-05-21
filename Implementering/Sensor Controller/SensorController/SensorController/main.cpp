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
	ADCBlokIF ADCBlok;
	CentralComputerIF CC;
	Timer T;
	
	//For test only
	//initLEDport();
	DDRB |= (1<<4)|(1<<5)|(1<<6);
	unsigned char answer = 0;
    while (1) 
    {
		
    }
}

