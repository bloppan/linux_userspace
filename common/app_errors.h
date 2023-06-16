/*
 * app_errors.h
 *
 *      Author: bernardo
 */

#ifndef APP_ERRORS_H_
#define APP_ERRORS_H_

#include "app_typedef.h"
#include <stdint.h>

typedef 	uint16_t 	error_t;

#define	    APP_REPORT(type, id_error)		((type << 8) | id_error)

// Peripherals definition (type error)
#define		NO_ERROR		0
#define		I2C				1
#define		GPIO			2
#define		PCA9532			3

// GPIO Errors	(id_error)
#define		OPENING_FILE		1
#define		WRITING_FILE		2
#define		INVALID_VALUE		3
#define		READING_FILE		4
#define     LOADING_LIBRARY     5
#define		SETTING_LED			7

#endif /* APP_ERRORS_H_ */
