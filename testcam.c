#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#define START 4
#define SNAP  5
#define RESET 1

int gpio_setup();


int main(void)
{
	gpio_setup();

	printf("Welcome to the MT9M034 test software \n");
	printf("Press button to start test \n");
	while(digitalRead(START));
	printf("Starting Camera \n");
	while(digitalRead(SNAP));
	printf("Taking Snap Shot \n");

	return 0;
}
int gpio_setup()
{


	if( wiringPiSetup() == -1)
	return -1;

	pinMode(START,INPUT);
	pinMode(SNAP,INPUT);
	pullUpDnControl (START,PUD_UP);
	pullUpDnControl (SNAP,PUD_UP);
	return 0;

}
