/* 
* SensorController.cpp
*
* Created: 27-04-2021 13:08:17
* Author: fogh1
*/


#include "SensorController.h"
#include "uart_int.hpp"
#include "avr\iom2560.h"

// default constructor
SensorController::SensorController()
{
	//Init
	Init();
}

void SensorController::Init()
{
	/***** Init GPIO'er *****/
	//Port C as output
	DDRC = 0xFF;
	//Port C all low
	PORTC = 0; 
		
	/***** Init SPI *****/
	// Set MOSI and SCK output, all others input
	DDRB = (1<<DDB2)|(1<<DDB1);
	// Enable SPI, Master, set clock rate fck/128, Spi mode 0
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1>>SPR1);
}

// default destructor
SensorController::~SensorController()
{
} //~SensorController
