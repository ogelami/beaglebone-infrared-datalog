#include <sys/time.h>
#include <stdio.h>
#include "SimpleGPIO.h"

using namespace std;

//http://cholla.mmto.org/computers/beagle/hardware/pinout1-1024x585.png
//https://github.com/derekmolloy/boneDeviceTree/blob/master/gpio/TestApplication.cpp

// P9_12 = GPIO1_28 = (1x32) + 28 = 60
#define LEDGPIO 60

void prettyOutput(unsigned short state, struct timeval* timestamp)
{
	printf("%d %l %l\n", state, timestamp->tv_sec, timestamp->tv_usec);
	fflush(stdout);
}

int main(int argc, char *argv[])
{
	gpio_export(LEDGPIO);
//	gpio_set_dir(LEDGPIO, INPUT_PIN);
	gpio_set_dir(LEDGPIO, OUTPUT_PIN);
	
	unsigned int previousState = 0;
	unsigned int newState = 0;
	
	struct timeval timestamp;

	gpio_get_value(LEDGPIO, &previousState);
    gettimeofday(&timestamp, 0);
	
//	printf("Started %ds %dns %s.\n", timestamp.tv_sec, timestamp.tv_usec, previousState ? "HIGH" : "LOW");
//	fflush(stdout);

	prettyOutput(previousState, (struct timeval*)&timestamp);
	
	for(int i = 0; i < 3; i++)
	{
		do
		{
			gpio_get_value(LEDGPIO, &newState);
		}
		while (previousState == newState);
		
//		clock_gettime(CLOCK_REALTIME, &timeSpec);
//		gettimeofday(&timestamp, 0);
//		printf("Switched to %s %ds %dns\n", newState ? "HIGH" : "LOW", timestamp.tv_sec, timestamp.tv_usec);
		
		previousState = newState;
	}
	
	gpio_unexport(LEDGPIO);

	return 0;
}
