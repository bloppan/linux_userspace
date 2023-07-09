/*
 * GPIO.h
 *
 *      Author: bernardo
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../common/app_typedef.h"
#include "../common/app_errors.h"

struct gpio {

	unsigned	gpio;
	unsigned long	flags;
	const char	*label;
};


#endif /* GPIO_H_ */
