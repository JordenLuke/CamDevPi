#include<wiringPi.h>
#include<wiringPiI2C.h>

#define MT9M034_PIXEL_ARRAY_WIDTH	1280
#define MT9M034_PIXEL_ARRAY_HEIGHT	960

#define	MT9M034_ROW_START_MIN		0
#define	MT9M034_ROW_START_MAX		960
#define	MT9M034_ROW_START_DEF		0
#define	MT9M034_COLUMN_START_MIN	0
#define	MT9M034_COLUMN_START_MAX	1280
#define	MT9M034_COLUMN_START_DEF	0
#define	MT9M034_WINDOW_HEIGHT_MIN	2
#define	MT9M034_WINDOW_HEIGHT_MAX	960
#define	MT9M034_WINDOW_HEIGHT_DEF	960
#define	MT9M034_WINDOW_WIDTH_MIN	2
#define	MT9M034_WINDOW_WIDTH_MAX	1280
#define	MT9M034_WINDOW_WIDTH_DEF	1280
#define MT9M034_ENABLE			1
#define MT9M034_DISABLE			0

#define MT9M034_CHIP_ID_REG		0x3000
#define MT9M034_CHIP_ID			0x2400

#define MT9M034_RESET_REG		0x301A
#define MT9M034_SEQ_CTRL_PORT		0x3088
#define MT9M034_SEQ_DATA_PORT		0x3086
#define MT9M034_ANALOG_REG		0x3ED6
#define MT9M034_TEST_RAW_MODE		0x307A
#define MT9M034_DARK_CTRL		0x3044
#define MT9M034_DATA_PEDESTAL		0x301E
#define MT9M034_COLUMN_CORRECTION	0x30D4

#define MT9M034_VT_SYS_CLK_DIV		0x302A
#define MT9M034_VT_PIX_CLK_DIV		0x302C
#define MT9M034_PRE_PLL_CLK_DIV		0x302E
#define MT9M034_PLL_MULTIPLIER		0x3030
#define MT9M034_DIGITAL_TEST		0x30B0

#define	MT9M034_Y_ADDR_START		0x3002
#define	MT9M034_X_ADDR_START		0x3004
#define	MT9M034_Y_ADDR_END		0x3006
#define	MT9M034_X_ADDR_END		0x3008
#define	MT9M034_FRAME_LENGTH_LINES	0x300A
#define	MT9M034_LINE_LENGTH_PCK		0x300C
#define	MT9M034_COARSE_INT_TIME		0x3012
#define MT9M034_FINE_INT_TIME		0x3014
#define	MT9M034_COARSE_INT_TIME_CB	0x3016
#define MT9M034_FINE_INT_TIME_CB	0x3018
#define	MT9M034_X_ODD_INC		0x30A2
#define	MT9M034_Y_ODD_INC		0x30A6
#define	MT9M034_READ_MODE		0x3040
#define MT9M034_TEST_PATTERN		0x3070
#define MT9M034_LLP_RECOMMENDED		1650
#define MT9M034_DIGITAL_BINNING		0x3032
#define MT9M034_HOR_AND_VER_BIN		0x0022
#define MT9M034_HOR_BIN			0x0011
#define MT9M034_DISABLE_BINNING		0x0000

#define MT9M034_AE_CTRL_REG		0x3100

#define MT9M034_GREEN1_GAIN		0x3056
#define MT9M034_BLUE_GAIN		0x3058
#define MT9M034_RED_GAIN		0x305A
#define MT9M034_GREEN2_GAIN		0x305C
#define MT9M034_GLOBAL_GAIN		0x305E
#define MT9M034_GREEN1_GAIN_CB		0x30BC
#define MT9M034_BLUE_GAIN_CB		0x30BE
#define MT9M034_RED_GAIN_CB		0x30C0
#define MT9M034_GREEN2_GAIN_CB		0x30C2
#define MT9M034_GLOBAL_GAIN_CB		0x30C4

#define MT9M034_RESET_REGISTER		0x301A
#define MT9M034_RESET			0x00D9
#define MT9M034_STREAM_OFF		0x00D8
#define MT9M034_STREAM_ON		0x00DC

#define MT9M034_ERS_PROG_START_ADDR	0x309E
#define MT9M034_MODE_CTRL		0x3082

#define MT9M034_DAC_LD_14_15		0x3EDA
#define MT9M034_DAC_LD_18_19		0x3EDE
#define MT9M034_DAC_LD_12_13		0x3ED8
#define MT9M034_DAC_LD_22_23		0x3EE2
#define MT9M034_DAC_LD_20_21		0x3EE0
#define MT9M034_DAC_LD_16_17		0x3EDC
#define MT9M034_DARK_CONTROL		0x3044
#define MT9M034_DAC_LD_26_27		0x3EE6
#define MT9M034_DAC_LD_24_25		0x3EE4
#define MT9M034_DAC_LD_10_11		0x3ED6
#define MT9M034_ADC_BITS_6_7		0x30E4
#define MT9M034_ADC_BITS_4_5		0x30E2
#define MT9M034_ADC_BITS_2_3		0x30E0
#define MT9M034_ADC_CONFIG1		0x30E6
#define MT9M034_ADC_CONFIG2		0x30E8
#define MT9M034_DIGITAL_CTRL		0x30BA
#define MT9M034_COARSE_INTEGRATION_TIME		0x3012
#define MT9M034_HDR_COMP			0x31D0

#define MT9M034_AE_DCG_EXPOSURE_HIGH_REG	0x3112
#define MT9M034_AE_DCG_EXPOSURE_LOW_REG		0x3114
#define MT9M034_AE_DCG_GAIN_FACTOR_REG		0x3116
#define MT9M034_AE_DCG_GAIN_FACTOR_INV_REG	0x3118
#define MT9M034_AE_LUMA_TARGET_REG		0x3102
#define MT9M034_AE_HIST_TARGET_REG		0x3104
#define MT9M034_AE_ALPHA_V1_REG			0x3126
#define MT9M034_AE_MAX_EXPOSURE_REG		0x311C
#define MT9M034_AE_MIN_EXPOSURE_REG		0x311E
#define MT9M034_EMBEDDED_DATA_CTRL		0x3064

#define V4L2_CID_TEST_PATTERN           (V4L2_CID_USER_BASE | 0x1001)
#define V4L2_CID_GAIN_RED		(V4L2_CID_USER_BASE | 0x1002)
#define V4L2_CID_GAIN_GREEN1		(V4L2_CID_USER_BASE | 0x1003)
#define V4L2_CID_GAIN_GREEN2		(V4L2_CID_USER_BASE | 0x1004)
#define V4L2_CID_GAIN_BLUE		(V4L2_CID_USER_BASE | 0x1005)
#define V4L2_CID_ANALOG_GAIN		(V4L2_CID_USER_BASE | 0x1006)

#define MT9M034_ANALOG_GAIN_MIN		0x0
#define MT9M034_ANALOG_GAIN_MAX		0x3
#define MT9M034_ANALOG_GAIN_DEF		0x0
#define MT9M034_ANALOG_GAIN_SHIFT	4
#define MT9M034_ANALOG_GAIN_MASK	0x0030

#define MT9M034_GLOBAL_GAIN_MIN		0x00
#define MT9M034_GLOBAL_GAIN_MAX		0xFF
#define MT9M034_GLOBAL_GAIN_DEF		0x20

#define MT9M034_EXPOSURE_MIN		1
#define MT9M034_EXPOSURE_MAX		0x02A0
#define MT9M034_EXPOSURE_DEF		0x0100
#define MT9M034_I2C_ADDR		0x10 /* (0x20 >> 1) */

#define MT9M034_WRITE(ret, fd, addr, data)	(ret) = __mt9m034_write((fd), (addr), (data)); \
						if ((ret) < 0)	{ \
							return ((ret)); \
						}
enum {
	MT9M034_COLOR_VERSION,
	MT9M034_MONOCHROME_VERSION,
};

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;


struct mt9m034_pll_divs {
        u32 ext_freq;
        u32 target_freq;
        u16 m;
        u16 n;
        u16 p1;
        u16 p2;
};
struct pin{
	int pin_num;
	int mode;
	int status;
};
struct mt9m034_data{
	struct mt9m034_pll_divs *pll;
	struct pin *reset;
	int fd;
	int version;
};
static struct mt9m034_pll_divs mt9m034_divs[] = {
        /* ext_freq     target_freq     M       N       p1      p2 */
        {24000000,      48000000,       32,     2,      2,      4},
        {24000000,      66000000,       44,     2,      2,      4},
        {27000000,      74250000,       44,	2,	1,	8},
        {48000000,      48000000,       40,     5,      2,      4}
};
static unsigned int mt9m034_seq_data[] = {
	0x0025, 0x5050, 0x2D26, 0x0828, 0x0D17, 0x0926, 0x0028, 0x0526,
	0xA728, 0x0725, 0x8080, 0x2925, 0x0040, 0x2702, 0x1616, 0x2706,
	0x1F17, 0x3626, 0xA617, 0x0326, 0xA417, 0x1F28, 0x0526, 0x2028,
	0x0425, 0x2020, 0x2700, 0x171D, 0x2500, 0x2017, 0x1219, 0x1703,
	0x2706, 0x1728, 0x2805, 0x171A, 0x2660, 0x175A, 0x2317, 0x1122,
	0x1741, 0x2500, 0x9027, 0x0026, 0x1828, 0x002E, 0x2A28, 0x081C,
	0x1470, 0x7003, 0x1470, 0x7004, 0x1470, 0x7005, 0x1470, 0x7009,
	0x170C, 0x0014, 0x0020, 0x0014, 0x0050, 0x0314, 0x0020, 0x0314,
	0x0050, 0x0414, 0x0020, 0x0414, 0x0050, 0x0514, 0x0020, 0x2405,
	0x1400, 0x5001, 0x2550, 0x502D, 0x2608, 0x280D, 0x1709, 0x2600,
	0x2805, 0x26A7, 0x2807, 0x2580, 0x8029, 0x2500, 0x4027, 0x0216,
	0x1627, 0x0620, 0x1736, 0x26A6, 0x1703, 0x26A4, 0x171F, 0x2805,
	0x2620, 0x2804, 0x2520, 0x2027, 0x0017, 0x1D25, 0x0020, 0x1712,
	0x1A17, 0x0327, 0x0617, 0x2828, 0x0517, 0x1A26, 0x6017, 0xAE25,
	0x0090, 0x2700, 0x2618, 0x2800, 0x2E2A, 0x2808, 0x1D05, 0x1470,
	0x7009, 0x1720, 0x1400, 0x2024, 0x1400, 0x5002, 0x2550, 0x502D,
	0x2608, 0x280D, 0x1709, 0x2600, 0x2805, 0x26A7, 0x2807, 0x2580,
	0x8029, 0x2500, 0x4027, 0x0216, 0x1627, 0x0617, 0x3626, 0xA617,
	0x0326, 0xA417, 0x1F28, 0x0526, 0x2028, 0x0425, 0x2020, 0x2700,
	0x171D, 0x2500, 0x2021, 0x1712, 0x1B17, 0x0327, 0x0617, 0x2828,
	0x0517, 0x1A26, 0x6017, 0xAE25, 0x0090, 0x2700, 0x2618, 0x2800,
	0x2E2A, 0x2808, 0x1E17, 0x0A05, 0x1470, 0x7009, 0x1616, 0x1616,
	0x1616, 0x1616, 0x1616, 0x1616, 0x1616, 0x1616, 0x1616, 0x1616,
	0x1616, 0x1616, 0x1616, 0x1614, 0x0020, 0x2414, 0x0050, 0x2B2B,
	0x2C2C, 0x2C2C, 0x2C00, 0x0225, 0x5050, 0x2D26, 0x0828, 0x0D17,
	0x0926, 0x0028, 0x0526, 0xA728, 0x0725, 0x8080, 0x2917, 0x0525,
	0x0040, 0x2702, 0x1616, 0x2706, 0x1736, 0x26A6, 0x1703, 0x26A4,
	0x171F, 0x2805, 0x2620, 0x2804, 0x2520, 0x2027, 0x0017, 0x1E25,
	0x0020, 0x2117, 0x1028, 0x051B, 0x1703, 0x2706, 0x1703, 0x1747,
	0x2660, 0x17AE, 0x2500, 0x9027, 0x0026, 0x1828, 0x002E, 0x2A28,
	0x081E, 0x0831, 0x1440, 0x4014, 0x2020, 0x1410, 0x1034, 0x1400,
	0x1014, 0x0020, 0x1400, 0x4013, 0x1802, 0x1470, 0x7004, 0x1470,
	0x7003, 0x1470, 0x7017, 0x2002, 0x1400, 0x2002, 0x1400, 0x5004,
	0x1400, 0x2004, 0x1400, 0x5022, 0x0314, 0x0020, 0x0314, 0x0050,
	0x2C2C, 0x2C2C
};

int pin_mode(struct pin *p, int mode)
{
	pinMode(p->pin_num,mode);
	p->mode = mode;

	return 0;
}
int pin_write(struct pin *p, int value)
{
	if(p->mode == OUTPUT)
	{
		digitalWrite(p->pin_num,value);
		p->status = value;
		return 0;
	}
	return -1;
}
int pin_read(struct pin *p)
{
	return digitalRead(p->pin_num);

}

/**
 * mt9m034_read - reads the data from the given register
 * @client: pointer to i2c client
 * @addr: address of the register which is to be read
 *
 */
static int mt9m034_read(int fd, u16 addr)
{
	return wiringPiI2CReadReg16(fd, (int) addr);
}

/**
 * __mt9m034_write - writes the data into the given register
 * @client: pointer to i2c client
 * @addr: address of the register in which to write
 * @data: data to be written into the register
 *
 */
static int __mt9m034_write(int fd, u16 addr,
				u16 data)
{

	int ret;
	/* i2c_transfer returns message length, but function should return 0 */
	ret = wiringPiI2CWriteReg16(fd, (int) addr, (int) data);
	return ret;
}

/**
 * mt9m034_sequencer_settings
 * @client: pointer to the i2c client
 *
 */
static int mt9m034_sequencer_settings(struct mt9m034_data *mt9m034)
{
	int i, ret;

	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_SEQ_CTRL_PORT, 0x8000)

	for(i = 0; i < sizeof(mt9m034_seq_data); i++){
		MT9M034_WRITE(ret, mt9m034->fd, MT9M034_SEQ_DATA_PORT, mt9m034_seq_data[i])
	}

	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_ERS_PROG_START_ADDR, 0x0186)

	return ret;
}

/**
 * mt9m034_linear_mode_setup - retrigger column correction
 * @fd: pointer to the i2c client
 *
 */
static int mt9m034_linear_mode_setup(struct mt9m034_data *mt9m034)
{
	int ret;

	/* Disable Streaming */
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_RESET_REG, MT9M034_STREAM_OFF)

	/* Operation mode control */
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_MODE_CTRL, 0x0029)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_DATA_PEDESTAL, 0x00C8)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_DAC_LD_14_15, 0x0F03)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_DAC_LD_18_19, 0xC005)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_DAC_LD_12_13, 0x09EF)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_DAC_LD_22_23, 0xA46B)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_DAC_LD_20_21, 0x067D)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_DAC_LD_16_17, 0x0070)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_DARK_CONTROL, 0x0404)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_DAC_LD_26_27, 0x8303)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_DAC_LD_24_25, 0xD208)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_DAC_LD_10_11, 0x00BD)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_ADC_BITS_6_7, 0x6372)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_ADC_BITS_4_5, 0x7253)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_ADC_BITS_2_3, 0x5470)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_ADC_CONFIG1, 0xC4CC)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_ADC_CONFIG2, 0x8050)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_DIGITAL_TEST, 0x1300)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_COLUMN_CORRECTION, 0xE007)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_DIGITAL_CTRL, 0x0008)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_RESET_REGISTER, 0x10DC)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_RESET_REGISTER, 0x10D8)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_BLUE_GAIN, 0x003F)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_COARSE_INTEGRATION_TIME, 0x02A0)

	delay(200);

	return ret;
}

static int mt9m034_pll_setup(struct mt9m034_data *mt9m034)
{
	int ret;

	mt9m034->pll  = & mt9m034_divs[0];

	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_VT_SYS_CLK_DIV, mt9m034->pll->p1)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_VT_PIX_CLK_DIV, mt9m034->pll->p2)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_PRE_PLL_CLK_DIV, mt9m034->pll->n)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_PLL_MULTIPLIER, mt9m034->pll->m)

	if (mt9m034->version == MT9M034_COLOR_VERSION)
		MT9M034_WRITE(ret, mt9m034->fd, MT9M034_DIGITAL_TEST, 0x0000)
	else
		MT9M034_WRITE(ret, mt9m034->fd, MT9M034_DIGITAL_TEST, 0x0080)

	delay(100);

	return ret;
}

static int mt9m034_ae_setup(struct mt9m034_data *mt9m034)
{
	int ret;

	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_RESET_REGISTER, 0x10D8)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_HDR_COMP, 0x0001)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_VT_SYS_CLK_DIV, 0x0002)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_VT_PIX_CLK_DIV, 0x0004)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_PRE_PLL_CLK_DIV, 0x0002)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_PLL_MULTIPLIER, 0x002C)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_DIGITAL_TEST, 0x1300)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_RESET_REGISTER, 0x10DC)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_EMBEDDED_DATA_CTRL, 0x1982)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_BLUE_GAIN, 0x003F)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_AE_CTRL_REG, 0x001B)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_AE_DCG_EXPOSURE_HIGH_REG, 0x029F)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_AE_DCG_EXPOSURE_LOW_REG, 0x008C)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_AE_DCG_GAIN_FACTOR_REG, 0x02C0)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_AE_DCG_GAIN_FACTOR_INV_REG, 0x005B)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_AE_LUMA_TARGET_REG, 0x0384)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_AE_HIST_TARGET_REG, 0x1000)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_AE_ALPHA_V1_REG, 0x0080)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_AE_MAX_EXPOSURE_REG, 0x03DD)
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_AE_MIN_EXPOSURE_REG, 0x0003)

	return ret;
}

static int mt9m034_is_streaming(struct mt9m034_data *mt9m034)
{
	u16 streaming;

	streaming = mt9m034_read(mt9m034->fd, MT9M034_RESET_REG);
	streaming = ( (streaming >> 2) & 0x0001);

	return (streaming != 0);
}
/**
 * mt9m034_power_on - power on the sensor
 * @mt9m034: pointer to private data structure
 *
 */
void mt9m034_power_on(struct mt9m034_data *mt9m034)
{
	/* Ensure RESET_BAR is low */
	pin_write(mt9m034->reset, LOW);
	delay(2);
	pin_write(mt9m034->reset, HIGH);
}
/**
*
* Starts streaming
*
*/
static int mt9m034_s_stream(struct mt9m034_data *mt9m034, int enable)
{
	int ret;

	if (!enable){
		MT9M034_WRITE(ret, mt9m034->fd, MT9M034_RESET_REG, MT9M034_STREAM_OFF)
		return ret;
	}

	ret = mt9m034_sequencer_settings(mt9m034);
	if (ret < 0){
		//printk(KERN_ERR"%s: Failed to setup sequencer\n",__func__);
		return ret;
	}

	delay(200);

	ret = mt9m034_linear_mode_setup(mt9m034);
	if (ret < 0){
		//printk(KERN_ERR"%s: Failed to setup linear mode\n",__func__);
		return ret;
	}

	//ret = mt9m034_set_size(client, &frame);
	if (ret < 0){
		//printk(KERN_ERR"%s: Failed to setup resolution\n",__func__);
		return ret;
	}

	ret = mt9m034_pll_setup(mt9m034);
	if (ret < 0){
		//printk(KERN_ERR"%s: Failed to setup pll\n",__func__);
		return ret;
	}

	ret = mt9m034_ae_setup(mt9m034);
	if (ret < 0){
		//printk(KERN_ERR"%s: Failed to setup auto-exposure\n",__func__);
		return ret;
	}

	/* start streaming */
	MT9M034_WRITE(ret, mt9m034->fd, MT9M034_RESET_REG, MT9M034_STREAM_ON)

	return ret;

}
int mt9m034_init(struct mt9m034_data *mt9m034, int pin)
{
	int fd;

	mt9m034->reset->pin_num = pin;
	pin_mode(mt9m034->reset,OUTPUT);
	if ((fd = wiringPiI2CSetup (MT9M034_I2C_ADDR)) < 0)
	return fd ;

	mt9m034->fd = fd;

	return 0;
}
