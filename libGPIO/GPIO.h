/*
 * GPIO.h
 * Author: bernardo
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


extern error_t __gpio_config(struct gpio *);
extern error_t __gpio_free(struct gpio *);
extern error_t __gpio_get_direction(struct gpio *, char *);
extern error_t __gpio_get_value(struct gpio *, unsigned *value);
extern error_t __gpio_set_value(struct gpio *, unsigned value);

#endif /* GPIO_H_ */
