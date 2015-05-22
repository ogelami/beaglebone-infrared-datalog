#include <stdio.h>
#include <stdlib.h>
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
	
	for(int i = 0; i < 3; i++)
	{
		gpio_get_value(LEDGPIO, &previousState);
		
		printf("%s", previousState ? "HIGH" : "LOW");
		
		do
		{
			gpio_get_value(LEDGPIO, &newState);
		}
		while (previousState == newState);
	}

	printf("%d", state);
	
	gpio_unexport(LEDGPIO);

	return 0;
}
