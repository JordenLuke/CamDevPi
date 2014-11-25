/*
*Compile info: gcc -c mt9m034Pi.c -lwiringPi -lpthread -lm
*
*
*/

#ifndef MT9M034PI_H
#define MT9M034PI_H


//structed used to hold some data
struct mt9m034_data{
	struct mt9m034_pll_divs *pll;
	struct pin *reset;
	int fd;
	int version;
};
//used to start  the  i2c and used
int mt9m034_init(struct mt9m034_data *mt9m034, int pin);
//can be used as rest
void mt9m034_power_on(struct mt9m034_data *mt9m034);
//toggle streaming
static int mt9m034_s_stream(struct mt9m034_data *mt9m034, int enable);



#endif
