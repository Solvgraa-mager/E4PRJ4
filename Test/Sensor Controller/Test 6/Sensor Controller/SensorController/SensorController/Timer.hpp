/* 
* Timer.h
*
* Created: 29-04-2021 14:29:46
* Author: fogh1
*/


#ifndef __TIMER_H__
#define __TIMER_H__
#define F_CPU 16000000
#include <util/delay.h>

class Timer
{
//variables
public:
	Timer();
	void wait(int timeInMs);
	~Timer();
}; //Timer

#endif //__TIMER_H__
