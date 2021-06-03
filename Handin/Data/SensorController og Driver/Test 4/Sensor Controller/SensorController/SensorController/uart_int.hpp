/****************************************
* "uart.h":                             *
* Header file for Mega2560 UART driver. *
* Using UART 0.                         *
* Henning Hargaard, 5/4 2019            *
*****************************************/ 
void InitUART(unsigned long BaudRate, unsigned char DataBit, unsigned char Rx_Int);
unsigned char CharReady();
char ReadChar();
void SendChar(char Tegn);
void SendString(char* Streng);
void SendInteger(int Tal);
void SendCharSW(char Tegn);
/****************************************/
