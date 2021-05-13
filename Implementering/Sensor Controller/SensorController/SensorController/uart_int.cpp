/************************************************
* "uart.c":                                     *
* Implementation file for Mega2560 UART driver. *
* Using UART 0.                                 *
* Henning Hargaard, 5/4 2019                    *
*************************************************/
#include <avr/io.h>
#include <stdlib.h>
#include "uart_int.hpp"
#include "avr/iom2560.h"
#include "led.hpp"

// Target CPU frequency
#define XTAL 16000000

/*************************************************************************
UART 0 initialization:
    Asynchronous mode.
    Baud rate = 9600.
    Data bits = 8.
    RX and TX enabled.
    No interrupts enabled.
    Number of Stop Bits = 1.
    No Parity.
    Baud rate = 9600.
    Data bits = 8.
*************************************************************************/
void InitUART(unsigned long BaudRate, unsigned char DataBit, unsigned char Rx_Int)
{
	if ((BaudRate >= 300) && (BaudRate <= 115200) && (DataBit >=5) && (DataBit <= 8))
	{
		// "Normal" clock, no multiprocessor mode (= default)
		UCSR1A = 0b00100000;
		// No interrupts enabled
		// Receiver enabled
		// Transmitter enabled
		// No 9 bit operation
		UCSR1B = 0b00011000;
		// Asynchronous operation, 1 stop bit
		// Bit 2 and bit 1 controls the number of data bits
		UCSR1C = (DataBit-5)<<1;
		// Set Baud Rate according to the parameter BaudRate:
		// Adding (8*Baudrate) ensures correct rounding (up/down)
		UBRR1 = (XTAL+(8*BaudRate))/(16*BaudRate) - 1;
		//Hvis Rx_Int er 0 skal UART modtager-interupt være disabled, hvis Rx_Int (!= 0) skal UART modtager-interupt være enabled
		UCSR1B |= ((Rx_Int == 0) ? 0 : (1<<7));
	}
}
/*************************************************************************
  Returns 0 (FALSE), if the UART has NOT received a new character.
  Returns value <> 0 (TRUE), if the UART HAS received a new character.
*************************************************************************/
unsigned char CharReady()
{
	return UCSR1A & (1<<7);
}

/*************************************************************************
Awaits new character received.
Then this character is returned.
*************************************************************************/
char ReadChar()
{
  // Wait for new character received
  while ( (UCSR1A & (1<<7)) == 0 )
  {}
  // Then return it
  return UDR1;
}

/*************************************************************************
Awaits transmitter register ready.
Then send the character.
Parameter :
	Tegn : Character for sending. 
*************************************************************************/
void SendChar(char Tegn)
{
  // Wait for transmitter register empty (ready for new character)
  while ( (UCSR1A & (1<<5)) == 0 )
  {}
  // Then send the character
  UDR1 = Tegn;
}

/*************************************************************************
Sends 0 terminated string.
Parameter:
   Streng: Pointer to the string. 
*************************************************************************/
void SendString(char* Streng)
{
	while (*Streng != 0)
	{
		SendChar(*Streng);
		Streng++;
	}
}

/*************************************************************************
Converts the integer "Tal" to an ASCII string - and then sends this string
using the USART.
Makes use of the C standard library <stdlib.h>.
Parameter:
    Tal: The integer to be converted and sent. 
*************************************************************************/
void SendInteger(int Tal)
{
	char array[7];
	// Convert the integer to an ASCII string (array), radix = 10
	itoa(Tal, array, 10);
	// - then send the string
	SendString(array);
}
void SendCharSW(char Tegn)
{
	UCSR1B = 0;
}

/************************************************************************/