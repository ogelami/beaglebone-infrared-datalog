#include <sys/time.h>
#include "SimpleGPIO.h"

using namespace std;

//http://cholla.mmto.org/computers/beagle/hardware/pinout1-1024x585.png
//https://github.com/derekmolloy/boneDeviceTree/blob/master/gpio/TestApplication.cpp

// P9_12 = GPIO1_28 = (1x32) + 28 = 60
#define LEDGPIO 60

int main(int argc, char *argv[])
{
	gpio_export(LEDGPIO);
//	gpio_set_dir(LEDGPIO, INPUT_PIN);
	gpio_set_dir(LEDGPIO, OUTPUT_PIN);
	
	unsigned int previousState = 0;
	unsigned int newState = 0;
	
	timespec timeSpec;

	gpio_get_value(LEDGPIO, &previousState);	
//	clock_gettime(NULL, &timeSpec);
	struct timeval start_time; 
    gettimeofday( &start_time, NULL ); 
	
//	printf("Started %ds %dns %s.\n", timeSpec->tv_sec, timeSpec->tv_nsec, previousState ? "HIGH" : "LOW");
//	fflush(stdout);
	
	for(int i = 0; i < 3; i++)
	{
		do
		{
			gpio_get_value(LEDGPIO, &newState);
		}
		while (previousState == newState);
		
//		clock_gettime(CLOCK_REALTIME, &timeSpec);
//		printf("Switched to %s %ds %dns\n", newState ? "HIGH" : "LOW", timeSpec->tv_sec, timeSpec->tv_nsec);
		
		previousState = newState;
	}
	
	gpio_unexport(LEDGPIO);

	return 0;
}
