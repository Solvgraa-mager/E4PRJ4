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
#define F_CPU 16000000
#include <util/delay.h>



int main(void)
{
	CentralComputerIF CCIF;
	//ADCBlokIF ADCBlok;
	//SensorController SC(&ADCBlok, &CCIF); 
	
	DDRB = 0xFF;
	
	for(uint16_t i = 0; i < 0xFFFF ; i++){
		PORTB = i; 
		CCIF.send(i,(i%2),(i%4));
		_delay_us(1);
	}
	volatile int i;
	while(1){
		SendString("DONE");
	}
	//SC.Run();
}


