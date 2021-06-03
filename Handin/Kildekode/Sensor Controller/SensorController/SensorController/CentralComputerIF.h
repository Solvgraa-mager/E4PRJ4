/* 
* CentralComputerIF.h
*
* Created: 27-04-2021 13:44:53
* Author: fogh1
*/


#ifndef __CENTRALCOMPUTERIF_H__
#define __CENTRALCOMPUTERIF_H__
#include <stdint-gcc.h>
#include <avr/interrupt.h>

class CentralComputerIF
{
public:
	CentralComputerIF();
	int getRequest();
	void send(uint16_t value, uint8_t valid, uint8_t request);
	~CentralComputerIF();

}; //CentralComputerIF

#endif //__CENTRALCOMPUTERIF_H__
