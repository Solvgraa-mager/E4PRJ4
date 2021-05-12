/* 
* ADCBlokIF.h
*
* Created: 29-04-2021 14:04:38
* Author: fogh1
*/


#ifndef __ADCBLOKIF_H__
#define __ADCBLOKIF_H__
#include <stdint-gcc.h>

class ADCBlokIF
{
//functions
public:
	ADCBlokIF();
	void multiplex(uint8_t sensorNo);
	uint16_t read();
	~ADCBlokIF();
private:
	uint8_t SPI(uint8_t temp);
	uint8_t _multiplexProtokol[4];
}; //ADCBlokIF

#endif //__ADCBLOKIF_H__
