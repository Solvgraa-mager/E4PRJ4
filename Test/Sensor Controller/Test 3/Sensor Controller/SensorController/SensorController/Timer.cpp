/* 
* Timer.cpp
*
* Created: 29-04-2021 14:29:46
* Author: fogh1
*/


#include "Timer.hpp"

// default constructor
Timer::Timer()
{
} //Timer

void Timer::wait(int timeInMs){
	for(int i = 0 ;i<timeInMs;i++)
		_delay_ms(1);
	return;
}

// default destructor
Timer::~Timer()
{
} //~Timer
