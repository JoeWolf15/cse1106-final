#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <unistd.h>
#include <pigpio.h>
#include <stdbool.h>
#define PIN 17 // Change to the correct pin if needed
#define READING_COUNT 5


bool isInRange(double, double, double);
double calculateAverage(double[], int);
void displayReadings(double[], int, double, double);
void displayReadingsToFile(double[], int, double, double);


int main(int argc, char* argv[]) {

	double temperatures[READING_COUNT];
	double lowerBound;
	double upperBound;
	gpioInitialise();
	gpioSetMode(PIN, PI_OUTPUT);
	

	printf("Enter the Maximum Temperature: ");
	scanf("%lf", &upperBound);
	printf("Enter the Minimum Temperature: ");
	scanf("%lf", &lowerBound);

	for (int i = 0; i < READING_COUNT; i++) {

		printf("Enter reading #%d:", i + 1);
		scanf("%lf", &temperatures[i]);
		{
		if (isInRange(temperatures[i], upperBound, lowerBound)) {
			gpioWrite(PIN, 0);
	
		}
		else {
			gpioWrite(PIN, 1);
		}
		
		printf("Temperature Reading:\n");
		if (isInRange(temperatures[i], upperBound, lowerBound)) {
			printf("%.1f F \t | NORMAL \t | OFF\n", temperatures[i]);
		} else printf("%.1f F \t | WARNING \t | ON\n", temperatures[i]);
	}
	}

	
	printf("\nAverage Temperature: %.2f", calculateAverage(temperatures, READING_COUNT));
	displayReadingsToFile(temperatures, READING_COUNT, upperBound, lowerBound);
	
	gpioTerminate();

	return 0;
}

bool isInRange(double temp, double upperBound, double lowerBound) {
	return temp <= upperBound && temp >= lowerBound;
}

double calculateAverage(double temp[], int count) {
	double total = 0;
	for (int i = 0; i < count; i++) total += temp[i];
	return total / count;
}

void displayReadings(double temp[], int count, double upperBound, double lowerBound) {
	printf("Temperature Readings:\n");
	for (int i = 0; i < count; i++) { 
		if (isInRange(temp[i], upperBound, lowerBound)) {
			printf("%.1f F \t | NORMAL \t | OFF\n", temp[i]);
		} else printf("%.1f F \t | WARNING \t | ON\n", temp[i]);
	}
}

void displayReadingsToFile(double temp[], int count, double upperBound, double lowerBound) {
	FILE* fp = fopen("TemperatureReadings.txt", "w");   // create/overwrite the file
	if (fp == NULL) {
		printf("Error opening file\n");
		return;
	}

	fprintf(fp, "Temperature Readings:\n");
	for (int i = 0; i < count; i++) {
		if (isInRange(temp[i], upperBound, lowerBound)) {
			fprintf(fp, "%.1f F \t | NORMAL \t | OFF\n", temp[i]);
		}
		else {
			fprintf(fp, "%.1f F \t | WARNING \t | ON\n", temp[i]);
		}
	}

	fclose(fp);
}

