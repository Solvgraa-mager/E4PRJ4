/*
 * SensorController.cpp
 *
 * Created: 27-04-2021 12:58:54
 * Author : fogh1
 */ 

#include <avr/io.h>

#include "CentralComputerIF.h"
#include "SensorController.h"
#include "ADCBlokIF.hpp"
#include "led.hpp"
#include "uart_int.hpp"



int main(void)
{
	CentralComputerIF CCIF;
	ADCBlokIF ADCBlok;
	SensorController SC(&ADCBlok, &CCIF); 
	
	for(int i = 0; i < 0xFFFF : i++){
		CentralComputerIF.send(i,(i%2),(i%4))
	}
	//SC.Run();
}


