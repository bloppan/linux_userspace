/*
 * GPIO.h
 *
 *      Author: bernardo
 */

#ifndef GPIO_H_
#define GPIO_H_


struct gpio {

	unsigned		gpio;
	unsigned long	flags;
	const char		*label;
};


#endif /* GPIO_H_ */
