/*
 * i2c_export.h
 *
 *      Author: bernardo
 */

#ifndef I2C_EXPORT_H_
#define I2C_EXPORT_H_

#include "I2C.h"

error_t (*i2c_read)(struct i2c_device *i2c_dev);
error_t (*i2c_write)(struct i2c_device *i2c_dev);

#endif /* I2C_EXPORT_H_ */
