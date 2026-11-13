#include <stdio.h>
#include <unistd.h>
#include <pigpio.h>
#include <stdbool.h>
#define PIN 26 // Change to the correct pin if needed
#define READING_COUNT 5

bool isInRange(int, int, int);
double calculateAverage(double, int);
int displayReadings(double, int);

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
double calculateAverage(double readings[], int count) {
    double total = 0;
    for (int i = 0; i < count; i++) total += readings[i];
    return total / count;
}

void displayReadings(double readings[], int count) {
    printf("Temperature Readings:\n");
    for (int i = 0; i < count; i++) printf("%.1f F\n", readings[i]);
}

bool isInRange(int temp, int upperbound, int lowerbound) {
    return temp <= upperbound && temp >= lowerbound;
}

