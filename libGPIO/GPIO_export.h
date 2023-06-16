/*
 * GPIO_export.h
 *
 *      Author: bernardo
 */

#ifndef GPIO_EXPORT_H_
#define GPIO_EXPORT_H_

#include "GPIO.h"
#include "../common/app_typedef.h"

error_t (*gpio_config)(struct gpio *);
error_t (*gpio_free)(struct gpio *);
error_t (*gpio_get_direction)(struct gpio *);
error_t (*gpio_get_value)(struct gpio *, unsigned *value);
error_t (*gpio_set_value)(struct gpio *, unsigned value);


#endif /* GPIO_EXPORT_H_ */
