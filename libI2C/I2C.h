/*
 * i2c.h
 * Author: bernardo
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "../common/app_typedef.h"
#include "../common/app_errors.h"

struct i2c_device {

	char		*i2c_port;	// I2C port name (/dev/i2c-0, /dev/i2c-1...)
	uint16_t	dev_addr;	// Device address (7 or 10 bits)
	uint8_t		reg_addr;	// Register address
	uint8_t		*data;		// Pointer to data buffer
	uint16_t	length;		// Lenght buffer
};

extern error_t __i2c_read(struct i2c_device *i2c_dev);
extern error_t __i2c_write(struct i2c_device *i2c_dev);

#endif /* I2C_H_ */

