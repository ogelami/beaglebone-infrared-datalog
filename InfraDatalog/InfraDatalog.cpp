#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include "SimpleGPIO.h"

using namespace std;

//http://cholla.mmto.org/computers/beagle/hardware/pinout1-1024x585.png
//https://github.com/derekmolloy/boneDeviceTree/blob/master/gpio/TestApplication.cpp

// P9_12 = GPIO1_28 = (1x32) + 28 = 60
#define LEDGPIO 60

//void prettyOutput(unsigned short state, struct timeval timestamp)
void prettyOutput(unsigned char* state, timeval *timestamp, int cycles)
{
	for(int i = 0; i < cycles; i++)
	{
		printf("%c %d%06d\n", state[i], (int)timestamp[i].tv_sec, (int)timestamp[i].tv_usec);
	}
//	printf("%d %d %d\n", state, timestamp.tv_sec, timestamp.tv_usec);
//	fflush(stdout);
}

int main(int argc, char *argv[])
{
	int cycles = argc > 1 ? atoi(argv[1]) : 10;
	
	gpio_export(LEDGPIO);
	gpio_set_dir(LEDGPIO, INPUT_PIN);
	
	unsigned int previousState = 0;
	unsigned int newState = 0;
	
	struct timeval *timestamp = (struct timeval*)malloc(cycles * sizeof(timeval));
	unsigned char *state = new unsigned char[cycles];

	gpio_get_value(LEDGPIO, &previousState);
	
	for(int i = 0; i < cycles; i++)
	{
		do
		{
			gpio_get_value(LEDGPIO, &newState);
		}
		while (previousState == newState);

		gettimeofday(&timestamp[i], 0);
		state[i] = newState ? '0' : '1';

		if(i > 0)
		{
			timestamp[i].tv_sec -= timestamp[0].tv_sec;
//			timestamp[i].tv_usec -= timestamp[0].tv_usec;
		}

//		prettyOutput(newState, timestamp);
		
		previousState = newState;
	}
	
	timestamp[0].tv_sec = 0;
/*	timestamp[0].tv_usec = 0;*/

	prettyOutput(state, timestamp, cycles);
	
	gpio_unexport(LEDGPIO);

	return 0;
}
