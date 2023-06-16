/*
 * PCA9532.h
 *
 *  Created on: Aug 2, 2021
 *      Author: bernardo
 */

#ifndef PCA9532_H_
#define PCA9532_H_

#include <stdio.h>
#include <stdint.h>
#include <dlfcn.h>

#include "../libI2C/I2C_export.h"
#include "../libGPIO/GPIO_export.h"

#include "../common/app_errors.h"
#include "../common/app_typedef.h"

/*
 * PCA9532 Outputs
 */
#define	LED0	0
#define	LED1	1
#define	LED2	2
#define	LED3	3
#define	LED4	4
#define	LED5	5
#define	LED6	6
#define	LED7	7
#define	LED8	8
#define	LED9	9
#define	LED10	10
#define	LED11	11
//	PCA9532 I2C Address
#define	PCA9532_ADDR	0x67
/*
 * LED struct
 */
typedef struct {

	uint8_t value;

}LED_struct;

struct RGB {

	uint8_t color;	// LED colors
	uint8_t blink;	// O -> no blink, 1 -> blink
};

/*
 * RGB colors
 */
#define BLUE		0
#define	GREEN		1
#define RED			2
#define	PURPLE		3
#define	YELLOW		4
#define CYAN		5
#define	WHITE		6
#define	LED_OFF		7




#endif /* PCA9532_H_ */


