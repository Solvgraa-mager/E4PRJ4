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
	InitUART(BAUDRATE,WORDLENGTH,1);
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
}

int CentralComputerIF::getRequest(){
	return ReadChar();
}

// default destructor
CentralComputerIF::~CentralComputerIF()
{
} //~CentralComputerIF
