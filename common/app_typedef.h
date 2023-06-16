/*
 * app_typedef.h
 *
 *  Created on: Jul 26, 2021
 *      Author: bernardo
 */

#ifndef APP_TYPEDEF_H_
#define APP_TYPEDEF_H_

#include "app_errors.h"

#define GPIO_NUMBER(bank, index)    ((((bank)-1)*32)+((index)&31))

// GPIOs defined
#define	PCA9532_EN	GPIO_NUMBER(1, 2)	// Enable PCA9532		(id 2,   J2.48 <-- 138)

#endif /* APP_TYPEDEF_H_ */
