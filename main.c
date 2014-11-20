/********************************************************************
* This is a test program  for use of the MT9M034 camera with  an FPGA
* Name: Jorden Luke
* Depencies: 
*********************************************************************/

//includes
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <WiringSerial.h>

#include <stido.h>
#include <string.h>
#include <errno.h>

struct  serial{

int fd;
int baud;
char  *dev;
};

enum serial_cmd{
	WRITE_BYTE = 0x31,
	READ_BYTE  = 0x32,
	WRITE_BURST,
	READ_BURST
};

int menu();
int main(){


	return 0;
}
//menu
int menu(){
	printf(" 1: Send Byte \n");
	printf(" 2: Send Burst \n");
	printf(" 3: Read Byte  \n");
	printf(	 4: Read Burst \n");
	

}

 while(( ch = getchar() ) != EOF 
