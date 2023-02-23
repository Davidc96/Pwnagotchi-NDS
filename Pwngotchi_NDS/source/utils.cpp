#include "utils.h"

#define TIMER_SPEED (BUS_CLOCK/1024)

int getRandomNumber()
{
    return rand() % 100;
}

void delay(int seconds)
{	
	int ticks = 0;
	int secs = 1;
	timerStart(0, ClockDivider_1024, 0, NULL);
	while(secs < seconds)
	{
		ticks += timerElapsed(0);
		secs = ticks/TIMER_SPEED;
	}

	timerPause(0);
}

// Extracted from Arduino CC https://www.arduino.cc/reference/en/language/functions/math/map/
long map(long x, long in_min, long in_max, long out_min, long out_max) 
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}