/* 
* ADCBlokIF.cpp
*
* Created: 29-04-2021 14:04:38
* Author: fogh1
*/

#include "ADCBlokIF.hpp"
#include <stdint-gcc.h>
#include <AVR/io.h>
#define F_CPU 16000000
#include <util/delay.h>

// default constructor
ADCBlokIF::ADCBlokIF()
{
	/***** Init SPI *****/
	//MSB First 
	//SCK, MOSI, SS as output 
	DDRB |= (1<<1)|(1<<2)|(1<<0);
	//MISO as input
	DDRB &= ~(1<<3);
	//SS high
	PORTB |= 1<<0;
	//Set as Master
	SPCR |= (1<<MSTR); //Not confirmed
	// Divide clock by 128 = 125KHz
	SPCR |= (1<<SPR0)|(1<<SPR1); //Not confirmed
	//Enable SPI
	SPCR |= (1<<SPE); //Not confirmed
		
} //ADCBlokIF

uint16_t ADCBlokIF::read(int channel){
	//Check channel is between 0 and 4
	if ((channel > 4) || (channel < 0)) return -1;
	
	uint8_t request[3] = {0};
	uint8_t answer[3] = {0};
	request[0] |= (1 << 1) | (1 << 2);
	request[1] |= (channel << 6);
	answer[0] = SPI(request[0]);
	answer[1] = SPI(request[1]);
	answer[2] = SPI(request[2]);
	
	return ((answer[1] & 0xF) << 8 | (answer[2]))  
}

uint8_t ADCBlokIF::SPI(uint8_t temp){
	//PORTB &= ~(0b1) //SS low
	SPDR = temp; 
	while(!(SPSR & (1<<SPIF)));
	//PORTB |= 0b1 //SS high
	return SPSR;
}

// default destructor
ADCBlokIF::~ADCBlokIF()
{
} //~ADCBlokIF
