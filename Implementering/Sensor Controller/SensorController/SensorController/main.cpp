/*
 * SensorController.cpp
 *
 * Created: 27-04-2021 12:58:54
 * Author : fogh1
 */ 

#include <avr/io.h>
#include <avr/sleep.h>
#include "CentralComputerIF.h"
#include "Timer.hpp"
#include "ADCBlokIF.hpp"
#include "led.hpp"
#include "uart_int.hpp"
#include <avr/interrupt.h>

int ReceivedSem = 0; 

int main(void)
{
	CentralComputerIF CCIF;
	ADCBlokIF ADCBlok;
	int request = 0, readValue = 0;
	volatile int i = 0; 
	DDRB = 0xFF;
	PORTB = 0b00000000;
	while(1)
	{
		i++;
		PORTB |= 0b10000000;
		if(ReceivedSem == 1)
		{
			ReceivedSem = 0;
			request = CCIF.getRequest();
			readValue = ADCBlok.read(request);
			CCIF.send(readValue,true,request);
			_delay_ms(1);
		}
		PORTB &= ~(0b10000000);
		//Sleep mode
		cli();
		sleep_enable();
		sei();
		sleep_cpu();
		sleep_disable();
	}
}

ISR(USART2_RX_vect)
{
	ReceivedSem = 1;
}
