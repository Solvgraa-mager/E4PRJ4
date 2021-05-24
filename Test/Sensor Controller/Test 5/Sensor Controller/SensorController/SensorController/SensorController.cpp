/* 
* SensorController.cpp
*
* Created: 27-04-2021 13:08:17
* Author: fogh1
*/


#include "SensorController.h"
#include "uart_int.hpp"
#include "avr\iom2560.h"
#define F_CPU 16000000
#include <util/delay.h>

int ReceivedSem = 0; 

// default constructor
SensorController::SensorController(ADCBlokIF *ADCBlok, CentralComputerIF *CC)
{
	ADCBlok_ = ADCBlok;
	CC_ = CC; 
}

void SensorController::Run(){
	int request = 0, readValue = 0;
	
	while(1)
	{
		if(ReceivedSem == 1)
		{
			ReceivedSem = 0;
			PORTD |= 0b1;
			request = CC_->getRequest();
			
			readValue = ADCBlok_->read(request);
			CC_->send(readValue,true,request);
			PORTD &= ~(0b1);
			_delay_ms(1);
		}
		//Sleep mode
		Sleep();
	}
}

void SensorController::Sleep(){
	cli();
	sleep_enable();
	sei();
	sleep_cpu();
	sleep_disable();
}

// default destructor
SensorController::~SensorController()
{
} //~SensorController

ISR(USART2_RX_vect)
{
	ReceivedSem = 1;
	
}