/*************************************************
* "LED.C"                                        *
* Implementation file for "Mega2560 LED driver"  *
* Henning Hargaard, 22/9 2015                    *
**************************************************/
#include <avr/io.h>
#define MAX_LED_NR 7

void initLEDport() //Skal typisk kun bruges én gang ifm opstart af program 
{
	DDRB = 0xFF; 
	PORTB = 0; 
}

void writeAllLEDs(unsigned char pattern) //Tager et binært tal ind og 
{
  PORTB = pattern;   
}

void turnOnLED(unsigned char led_nr)
{
// Lokal variabel
unsigned char mask;
  // Vi skal kun lave noget, hvis led_nr < 8
  if (led_nr <= MAX_LED_NR)
  {
    // Dan maske på basis af parameteren (led_nr)
    mask = 0b00000001 << led_nr;
    // Tænd den aktuelle lysdiode (de andre ændres ikke)
    PORTB = PINB | mask;
  }   
}

void turnOffLED(unsigned char led_nr)
{
	unsigned char mask;
	if (led_nr <= MAX_LED_NR) 
		{
		mask = 0b00000001 << led_nr; //Skubber nullet hen til den LED-plads vi gerne vil slukke
		PORTB = PINB & ~mask;		
	}
}

void toggleLED(unsigned char led_nr)
{
		unsigned char mask;
		if (led_nr <= MAX_LED_NR)
		{
			mask = 0b00000001 << led_nr; //Skubber nullet hen til den LED-plads vi gerne vil slukke
			PORTB = PINB ^ mask; //XOR
		}
}