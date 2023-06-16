/*
 * PCA9532_export.h
 *
 *  Created on: Aug 2, 2021
 *      Author: bernardo
 */

#ifndef PCA9532_EXPORT_H_
#define PCA9532_EXPORT_H_

#include "PCA9532.h"

error_t (*pca9532_set_led)(unsigned id_led, _Bool value);
error_t (*pca9532_set_mask_out)(uint16_t mask);
error_t	(*pca9532_open)(void);
error_t (*set_led_rgb)(uint8_t RGBn, struct RGB *LED_RGB);


#endif /* PCA9532_EXPORT_H_ */


