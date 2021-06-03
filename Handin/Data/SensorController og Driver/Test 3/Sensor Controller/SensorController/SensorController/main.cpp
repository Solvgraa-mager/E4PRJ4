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
	ADCBlokIF ADCBlok;
	SensorController SC(&ADCBlok, &CCIF); 
	
	unsigned char channel;
	
	channel = 3; 
	//Følgende er inspireret af https://github.com/adgzlanl/atmega2560-PWM-example/blob/master/PWM.c
	
	SendString("Test starting for channel ");
	SendInteger(channel);
	SendString("\n");
	
	uint8_t cnt;

	TCCR0A |= (1<<WGM01)|(1<<COM0A1)|(1<<WGM00);
	TCCR0B |= (1 << CS00) ;
	DDRB |= (1<<PB7);

	for(cnt = 0; cnt<255; ++cnt){
		OCR0A = cnt;
		_delay_ms(1);
		SendString("PWM: ");
		SendInteger(cnt);
		SendString(" Value: ");
		SendInteger(ADCBlok.read(channel));
		SendString("\n");	
	}
	DDRB = 0xFF;
	PORTB |= 0b01100000;
	while(1)
	{
		SendString("Done\n");
		_delay_ms(10000);	
	}
	
	//SC.Run();
}


