#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#define START 4
#define SNAP  5
#define RESET 1
#define DONE  6

int gpio_setup();
void myInterupt();

int main(void)
{
	if( gpio_setup()  < 0)
	{
		printf("ERROR: Failed on gpio init \n");
		return 1;

	}

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

	if (wiringPiSetup () < 0)
  	{
    		fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno)) ;
    		return 1 ;
  	}

  	if (wiringPiISR (DONE, INT_EDGE_FALLING, &myInterrupt) < 0)
  	{
    		fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
    		return 1 ;
  	}

	pinMode(START,INPUT);
	pinMode(SNAP,INPUT);
	pullUpDnControl (START,PUD_UP);
	pullUpDnControl (SNAP,PUD_UP);
	return 1;
}
void myInterupt()
{

	printf("Picture Captured \n");

}
