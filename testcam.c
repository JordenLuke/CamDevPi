/*
* Complie : gcc -o testcam testcam.c  -I. mt9m034Pi.o -lwiringPi -lpthread
*
*
*/
#include <wiringPi.h>
#include "mt9m034Pi.h"
#include <wiringSerial.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


#define START 4
#define SNAP  5
#define RESET 1
#define DONE  6


struct serial{
 int fd;
 int baud;
 char  *name;
};

struct mem_cmd{
 char add[4];
 char *data;
 int size;
};

void myInterrupt();
int gpio_setup(struct serial *dev);
int init_serial(struct serial *dev);

struct mt9m034_data mt9m034;
struct pin reset;
int flag = 0x00;
//serial device name and baud
int main(int argc,char *args[])
{
	struct serial dev;
	struct mem_cmd mem;
	int err;

	if(argc > 1)
	{
		memcpy(dev.name, (args[1]+1), sizeof(args[1]-1);
		dev.baud = atoi((args[2]+1));
	}
	else
	{
		dev.name = "/dev/tty/AMA0";
		dev.baud = 115200;
	}

	mt9m034.reset = reset;
	if( gpio_setup(&dev)  < 0)
	{
		printf("ERROR: Failed on gpio init \n");
		fflush(stdout);
		return 1;
	}

	printf("Welcome to the MT9M034 test software \n");
	printf("Press button to start test \n");
	for(;;)
	{
		while(digitalRead(START));

		mt9m034_s_stream(&mt9m034,1);
		printf("Starting Camera \n");
		while(!flag);
		while(digitalRead(SNAP));
		printf("Taking Snap Shot \n");
	}

	return 0;
}
int gpio_setup(struct serial *dev)
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
	if(mt9m034_init(&mt9m034, RESET)  < 0 )
	{
		printf ("Unable to init camera:  \n") ;
		return -1;
	}
	if ((dev->fd = serialOpen (dev->name, dev->baud)) < 0)
        {
                fprintf (stderr, "Unable to open serial device: %s\n", strerror (errn$
                return 1 ;
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
	mt9m034_s_stream(&mt9m034,0);
	flag = 0x01;
}
int init_serial(struct serial *dev){

	if ((dev->fd = serialOpen (dev->name, dev->baud)) < 0)
  	{
    		fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    		return 1 ;
  	}
	return 0;
}
