/*
* Complie :gcc -o testcam  testcam.c mt9m034Pi.c -lwiringPi -lpthread -lm
*
*
*/
#include <wiringPi.h>
#include "mt9m034Pi.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


#define START 4
#define SNAP  5
#define RESET 1
#define DONE  6

void myInterrupt();
int gpio_setup();

struct mt9m034_data *mt9m034;

int main(void)
{
	if( gpio_setup()  < 0)
	{
		printf("ERROR: Failed on gpio init \n");
		fflush(stdout);
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
    		printf ("Unable to setup wiringPi: \n");
    		return - 1 ;
  	}

  	if (wiringPiISR (DONE, INT_EDGE_FALLING, &myInterrupt) < 0)
  	{
   		printf ("Unable to setup ISR: \n") ;
    		return -1 ;
  	}
	if(mt9m034_init(mt9m034, RESET)  < 0 )
	{
		printf ("Unable to init camera:  \n") ;
		return -1;
	}

	pinMode(START,INPUT);
	pinMode(SNAP,INPUT);
	pullUpDnControl (START,PUD_UP);
	pullUpDnControl (SNAP,PUD_UP);
	return 1;
}
void myInterrupt()
{

	printf("Picture Captured \n");

}
