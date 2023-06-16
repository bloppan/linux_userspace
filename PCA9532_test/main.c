/*
 * main.c
 *
 *  Created on: Jul 30, 2021
 *      Author: bernardo
 */

#include "../libPCA9532/PCA9532.h"

#include <dlfcn.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{

	void *hdlr_pca9532 = NULL;

	hdlr_pca9532 = dlopen("/usr/lib/libPCA9532.so.1", RTLD_LAZY);
	if(hdlr_pca9532 == NULL)
		return -1;

	pca9532_set_led = (error_t ( *)(unsigned, _Bool)) dlsym(hdlr_pca9532, "pca9532_set_led");
	pca9532_set_mask_out = (error_t ( *)(uint16_t)) dlsym(hdlr_pca9532, "pca9532_set_mask_out");
	pca9532_open = (error_t ( *)(void)) dlsym(hdlr_pca9532, "pca9532_open");
	set_led_rgb = (error_t ( *)(uint8_t, struct RGB *)) dlsym(hdlr_pca9532, "set_led_rgb");

	// Inicializa el controlador de LEDs
	pca9532_open();

	pca9532_set_mask_out(0x24);
	sleep(1);
	pca9532_set_mask_out(0x800);
	sleep(1);

	struct RGB led_rgb = {

		.color = PURPLE,
		.blink = 1
	};

	unsigned RGBn = 1; // (RGB 0 to RGB 3)
	set_led_rgb(RGBn, &led_rgb);

	return 0;

}

