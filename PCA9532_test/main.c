/*
 * main.c
 * Author: bernardo
 */

#include <dlfcn.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "../libPCA9532/PCA9532.h"

error_t (*pca9532_set_led)(unsigned, _Bool);
error_t (*pca9532_set_mask_out)(uint16_t);
error_t (*pca9532_open)(void);
error_t (*set_led_rgb)(uint8_t, struct RGB *);

int main(int argc, char *argv[])
{

	void *hdlr_pca9532 = NULL;

	hdlr_pca9532 = dlopen("/usr/lib/libPCA9532.so.1", RTLD_LAZY);
	if(hdlr_pca9532 == NULL)
		return -1;

	pca9532_set_led = (error_t ( *)(unsigned, _Bool)) dlsym(hdlr_pca9532, "__pca9532_set_led");
	pca9532_set_mask_out = (error_t ( *)(uint16_t)) dlsym(hdlr_pca9532, "__pca9532_set_mask_out");
	pca9532_open = (error_t ( *)(void)) dlsym(hdlr_pca9532, "__pca9532_open");
	set_led_rgb = (error_t ( *)(uint8_t, struct RGB *)) dlsym(hdlr_pca9532, "__set_led_rgb");

	// Led controller init
	pca9532_open();

	// Set mask output values
	pca9532_set_mask_out(0x24);
	sleep(1);
	pca9532_set_mask_out(0x800);
	sleep(1);

	struct RGB led_rgb = {

		.color = PURPLE,
		.blink = 1
	};

	// Set RGB color
	unsigned RGBn = 1; // (RGB 0 to RGB 3)
	set_led_rgb(RGBn, &led_rgb);

	return 0;

}

