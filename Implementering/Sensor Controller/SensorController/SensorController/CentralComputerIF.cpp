/* 
* CentralComputerIF.cpp
*
* Created: 27-04-2021 13:44:53
* Author: fogh1
*/


#include "CentralComputerIF.h"
#include "uart_int.hpp"


// default constructor
CentralComputerIF::CentralComputerIF()
{
	/***** Init UART and UART Interrupt *****/
	InitUART(9600,8,1);
	sei();
} //CentralComputerIF
void CentralComputerIF::send(uint16_t value, uint8_t valid, uint8_t request)
{
	//Data bytes
	SendChar(value >> 8);
	SendChar(value & 0xFF);
	//Kontrol-byte
	SendChar(valid ? 0xFF : 0x00);
	//Checksum-byte
	SendChar((value+request) & 0xFF);
	return; 
}

int CentralComputerIF::getRequest(){
	char requestRaw = 0, requestDecoded = 0; 
	requestRaw = ReadChar();
	if(requestRaw == 0b00000001)
		requestDecoded = 0; 
	else if(requestRaw == 0b00000010)
		requestDecoded = 1; 
	else if(requestRaw == 0b00000100)
		requestDecoded = 2; 
	else if(requestRaw == 0b00001000)
		requestDecoded = 3;
	else 
		requestDecoded = 255;
	return requestDecoded;
}

// default destructor
CentralComputerIF::~CentralComputerIF()
{
} //~CentralComputerIF
