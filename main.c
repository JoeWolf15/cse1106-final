#include <stdio.h>
#include <unisd.h>
#include <pigpio.h>
#define PIN 17 // Change to the correct pin if needed

int main(int argc, char* argv[]) {
	gpioInitialise();
	gpioSetMode(PIN, PI_OUTPUT);
	gpioWrite(PIN, 1);// LED ON
	getchar(); // waits for enter key
	gpioWrite(PIN, 0); // LED OFF
	getchar(); // waits for enter key
	gpioTerminate();
	return 0;
}
