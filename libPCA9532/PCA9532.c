/*
 * PCA9532.c
 *
 *  Created on: Aug 2, 2021
 *      Author: bernardo
 */


#include "PCA9532.h"

#define NUM_LEDS	12
#define NUM_RGB		NUM_LEDS/3

static LED_struct 	LED[NUM_LEDS] = {0};
static struct i2c_device pca9532_i2c_info = {0};

static error_t pca9532_write_output(void)
{
	uint8_t msg_data[3];
	error_t error_code = NO_ERROR;

	// Fill I2C message data with led values
	msg_data[0] = LED[LED0].value | (LED[LED1].value << 2) | (LED[LED2].value << 4) | (LED[LED3].value << 6); 	// (XX XX XX XX) 1 - 4
	msg_data[1] = LED[LED4].value | (LED[LED5].value << 2) | (LED[LED6].value << 4) | (LED[LED7].value << 6);		// (XX XX XX XX) 5 - 8
	msg_data[2] = LED[LED8].value | (LED[LED9].value << 2) | (LED[LED10].value << 4) | (LED[LED11].value << 6);	// (XX XX XX XX) 9 - 12

	// I2C data
	pca9532_i2c_info.reg_addr 	= 0x16; // LED0 to LED4 with Autoincrement (0x10 | 0x06)
	pca9532_i2c_info.length		= 3;	// 12 Leds
	pca9532_i2c_info.data		= msg_data;

	if(i2c_write(&pca9532_i2c_info) != NO_ERROR)
		error_code = APP_REPORT(PCA9532, SETTING_LED);

	return error_code;
}

error_t pca9532_set_led(unsigned id_led, _Bool value)
{
	if(id_led < 0 || id_led >= NUM_LEDS)
		return APP_REPORT(PCA9532, INVALID_VALUE);

	// Save new led value
	LED[id_led].value 	= value;
	// Write new led value
	return pca9532_write_output();
}

/*
*	Set LED 12 to LED 1 values from uint16 mask
*/
error_t pca9532_set_mask_out(uint16_t mask)
{
	int i = NUM_LEDS;
	uint16_t bit = (1 << (NUM_LEDS - 1));

	// Save each new led value
	while(--i){
		LED[i].value |= (mask & bit) >> i;
		bit >>= 1;
	}
	// Write new led values
	return pca9532_write_output();
}

error_t set_led_rgb(uint8_t RGBn, struct RGB *LED_RGB)
{
	if(RGBn < 0 || RGBn >= NUM_RGB)
		return APP_REPORT(PCA9532, INVALID_VALUE);

	switch(LED_RGB->color){

		case BLUE:
			LED[RGBn*3 + BLUE].value 	= 1 + LED_RGB->blink;
			LED[RGBn*3 + GREEN].value 	= 0;
			LED[RGBn*3 + RED].value 	= 0;
			break;
		case GREEN:
			LED[RGBn*3 + BLUE].value 	= 0;
			LED[RGBn*3 + GREEN].value 	= 1 + LED_RGB->blink;
			LED[RGBn*3 + RED].value 	= 0;
			break;
		case RED:
			LED[RGBn*3 + BLUE].value 	= 0;
			LED[RGBn*3 + GREEN].value	= 0;
			LED[RGBn*3 + RED].value 	= 1 + LED_RGB->blink;
			break;
		case PURPLE:
			LED[RGBn*3 + BLUE].value 	= 1 + LED_RGB->blink;
			LED[RGBn*3 + GREEN].value 	= 0;
			LED[RGBn*3 + RED].value 	= 1 + LED_RGB->blink;
			break;
		case YELLOW:
			LED[RGBn*3 + BLUE].value 	= 0;
			LED[RGBn*3 + GREEN].value 	= 1 + LED_RGB->blink;
			LED[RGBn*3 + RED].value 	= 1 + LED_RGB->blink;
			break;
		case CYAN:
			LED[RGBn*3 + BLUE].value 	= 1 + LED_RGB->blink;
			LED[RGBn*3 + GREEN].value 	= 1 + LED_RGB->blink;
			LED[RGBn*3 + RED].value 	= 0;
			break;
		case WHITE:
			LED[RGBn*3 + BLUE].value 	= 1 + LED_RGB->blink;
			LED[RGBn*3 + GREEN].value 	= 1 + LED_RGB->blink;
			LED[RGBn*3 + RED].value 	= 1 + LED_RGB->blink;
			break;
		case LED_OFF:
			LED[RGBn*3 + BLUE].value 	= 0;
			LED[RGBn*3 + GREEN].value 	= 0;
			LED[RGBn*3 + RED].value 	= 0;
			break;
		default:
			return APP_REPORT(PCA9532, INVALID_VALUE);
			break;
	}

	return pca9532_write_output();
}


static error_t pca9532_blink_config(void)
{
	uint8_t msg_data[1] = {0};

	// Value of PSC0 register
	msg_data[0] = 0x77;

	// I2C data PSC0 register
	pca9532_i2c_info.reg_addr 	= 0x02; // PSC0 reg address
	pca9532_i2c_info.length		= 1;
	pca9532_i2c_info.data		= msg_data;

	// Send I2C data
	if(i2c_write(&pca9532_i2c_info) != NO_ERROR)
		return APP_REPORT(PCA9532, SETTING_LED);

	// Value of PSC1 register
	msg_data[0] = 0xEE;
	// I2C data PSC1 register
	pca9532_i2c_info.reg_addr 	= 0x04; // PSC1 reg address

	if(i2c_write(&pca9532_i2c_info) != NO_ERROR)
		return APP_REPORT(PCA9532, SETTING_LED);

	return NO_ERROR;

}

error_t pca9532_open(void)
{
	error_t error_code = NO_ERROR;

	void *hdlr_i2c 	= NULL;
	void *hdlr_gpio	= NULL;

	// Open I2C library
	hdlr_i2c = dlopen("/usr/lib/libI2C.so.1", RTLD_LAZY);
	if(hdlr_i2c == NULL)
		error_code = APP_REPORT(PCA9532, LOADING_LIBRARY);

	// Open GPIO library
	hdlr_gpio = dlopen("/usr/lib/libGPIO.so.1", RTLD_LAZY);
	if(hdlr_gpio == NULL)
		error_code = APP_REPORT(PCA9532, LOADING_LIBRARY);

	// Load GPIO functions
	gpio_config = (error_t ( *)(struct gpio *)) dlsym(hdlr_gpio, "gpio_config");
	gpio_free = (error_t ( *)(struct gpio *)) dlsym(hdlr_gpio, "gpio_free");
	gpio_get_value = (error_t ( *)(struct gpio *, unsigned *value)) dlsym(hdlr_gpio, "gpio_get_value");
	gpio_get_direction = (error_t ( *)(struct gpio *)) dlsym(hdlr_gpio, "gpio_get_direction");
	gpio_set_value = (error_t ( *)(struct gpio *, unsigned value)) dlsym(hdlr_gpio, "gpio_set_value");

	// Load I2C functions
	i2c_read = (error_t ( *)(struct i2c_device *)) dlsym(hdlr_i2c, "i2c_read");
	i2c_write = (error_t ( *)(struct i2c_device *)) dlsym(hdlr_i2c, "i2c_write");

	// Configure PCA9532 gpio struct
	struct gpio pca9532_en;
	pca9532_en.gpio	= PCA9532_EN;
	pca9532_en.flags = 0;
	pca9532_en.label = "PCA9532_EN";

	// Configure PCA9532 I2C data
	pca9532_i2c_info.i2c_port 	= "/dev/i2c-0";
	pca9532_i2c_info.dev_addr	= PCA9532_ADDR;

	// Power ON PCA9532
	gpio_config(&pca9532_en);
	gpio_set_value(&pca9532_en, 1);

	pca9532_blink_config();

	return error_code;
}



