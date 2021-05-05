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
	/****** Init Multiplex *****/
	//Port C as output
	DDRC = 0xFF; 
	PORTC = 0; 
	//MultiplexProtokol
	_multiplexProtokol[0] = (1<<0);
	_multiplexProtokol[1] = (1<<1);
	_multiplexProtokol[2] = (1<<2);
	_multiplexProtokol[3] = (1<<3);
	
	/***** Init SPI *****/
	//SCK, MOSI, SS as output 
	DDRB |= (1<<1)|(1<<2)|(1<<0);
	//MISO as input
	DDRB &= ~(1<<3);
	//Set as Master
	SPCR |= (1<<MSTR); //Not confirmed
	// Divide clock by 128 
	SPCR |= (1<<SPR0)|(1<<SPR1); //Not confirmed
	//Enable SPI
	SPCR |= (1<<SPE); //Not confirmed
		
} //ADCBlokIF

void ADCBlokIF::multiplex(uint8_t sensorNo){
	PORTC = _multiplexProtokol[sensorNo];
	return; 
}

uint16_t ADCBlokIF::read(){
	SPI(0xAA);
	SPI(0xFA);
}

uint8_t ADCBlokIF::SPI(uint8_t temp){
	SPDR = temp; 
	while(!(SPSR & (1<<SPIF)));
	return SPSR;
}

// default destructor
ADCBlokIF::~ADCBlokIF()
{
} //~ADCBlokIF
