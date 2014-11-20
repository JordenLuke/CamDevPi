/********************************************************************
* This is a test program  for use of the MT9M034 camera with  an FPGA
* Name: Jorden Luke
* Depencies: wiringpi
* Compile: cc -o main main.c -lwiringPi
*********************************************************************/

//includes
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <wiringSerial.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
struct serial{

int fd;
int baud;
char  *name;
};
struct mem_cmd{
 char add[4];
 char *data
 int size;
};

enum serial_cmd{
	WRITE_BYTE = 0x31,
	READ_BYTE  = 0x32,
	WRITE_BURST,
	READ_BURST
};
//used for menu
char menu();

int init_serial(struct serial *dev);
void send_burst(struct serial *dev,struct mem_cmd *mem);
void send_byte(struct serial *dev,struct mem_cmd *mem);
void read_byte(struct serial *dev,struct mem_cmd *mem);
void read_burst(struct serial *dev,struct mem_cmd *mem);


int main(){

	struct serial dev;
	int err;
	dev.name = "/dev/tty/AMA0";
	dev.baud = 115200;
	err = init_serial(dev);
	if(err>0)
	{
		return err;
	}

	return err;
}
//menu
char menu(){

	char ch;
	printf(" 1: Send Byte \n");
	printf(" 2: Send Burst \n");
	printf(" 3: Read Byte  \n");
	printf(" 4: Read Burst \n");
	printf(" CMD: "

 while(( ch = getchar() ) != EOF );

}
//used to start the serial
int init_serial(struct serial *dev){

	if ((dev.fd = serialOpen (dev.name, dev.baud)) < 0)
  	{
    		fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    		return 1 ;
  	}
	return 0;

}
//sends out burst o serial data
int send_burst(struct serial *dev,struct mem_cmd *mem){

	char ch;
	int trys = 0;
	serialPutchar(dev->fd,(char) WIRTE_BURST);

	while(!serialDataAvail(dev->fd))
        {
		try ++;
		if(trys==5)
		{
		 	return -1;
		}

		sleep(1);
	}
	ch = serialGetchar(dev->fd);
       	printf("%c /n", ch);


	serialPutchar(dev->fd,mem->add[0]);
	serialPutchar(dev->fd,mem->add[1]);
	serialPutchar(dev->fd,mem->add[2]);
	serialPutchar(dev->fd,mem->add[3]);
	if(serialDataAvail(dev->fd))
        {
                ch = serialGetchar(dev->fd);
                printf("%c /n", ch);
        }

	serialPuts(dev->fd, mem->data);
}
//sends out a byte
void send_byte(struct *serial,struct *mem_cmd){

        serialPutchar(dev->fd,(char) WIRTE_BURST);
        serialPutchar(dev->fd,mem->add[0]);
        serialPutchar(dev->fd,mem->add[1]);
        serialPutchar(dev->fd,mem->add[2]);
        serialPutchar(dev->fd,mem->add[3]);
	if(serialDataAvail(dev->fd))
        {
                ch = serialGetchar(dev->fd);
                printf("%c /n", ch);
        }
	seialPutchar(dev->fd,mem->data[0]);
}
//sends out a byte
void read_byte(struct *serial,struct *mem_cmd){
        serialPutchar(dev->fd,(char) WIRTE_BURST);
        serialPutchar(dev->fd,mem->add[0]);
        serialPutchar(dev->fd,mem->add[1]);
        serialPutchar(dev->fd,mem->add[2]);
        serialPutchar(dev->fd,mem->add[3]);

}
//sends out a byte
void read_burst(struct *serial,struct *mem_cmd){

	serialPutchar(dev->fd,(char) WIRTE_BURST);
        serialPutchar(dev->fd,mem->add[0]);
        serialPutchar(dev->fd,mem->add[1]);
        serialPutchar(dev->fd,mem->add[2]);
        serialPutchar(dev->fd,mem->add[3]);

}

