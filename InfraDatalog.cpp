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
	printf("asd");
/*	gpio_export(LEDGPIO);
	gpio_set_dir(LEDGPIO, INPUT_PIN);
	gpio_wait_value(LEDGPIO);*/
	
	return 0;
}
