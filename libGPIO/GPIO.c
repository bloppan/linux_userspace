/*
 * gpio.c
 *
 *      Author: bernardo
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <dirent.h>
#include <dlfcn.h>

#include "GPIO.h"

error_t gpio_config(struct gpio *gpio)
{
	error_t	code_error = NO_ERROR;
	int8_t 	fd_export;					// File descriptor export file
	int8_t  fd_direction;				// File descriptor direction file
	char 	gpio_str[4] = {0}; 			// String gpio
	char	gpio_path_str[50] = {0}; 	// String path gpio

	fd_export = open("/sys/class/gpio/export", O_WRONLY);

	if(fd_export < 0)
		return APP_REPORT(GPIO, OPENING_FILE);

	// GPIO number as character string
	sprintf(gpio_str, "%d", gpio->gpio);

	if(write(fd_export, gpio_str, strlen(gpio_str)) < 1){
		close(fd_export);
		return APP_REPORT(GPIO, WRITING_FILE);
	}

	sprintf(gpio_path_str, "/sys/class/gpio/gpio%d/direction", gpio->gpio);

	fd_direction = open(gpio_path_str, O_WRONLY);

	if(fd_direction < 0){
		code_error = APP_REPORT(GPIO, OPENING_FILE);
		goto error;
	}
		
	// Configure direction
	switch(gpio->flags & 1){
		// Output
		case 0:
			if(write(fd_direction, "out", strlen("out")) < 0)
				code_error = APP_REPORT(GPIO, WRITING_FILE);
		break;
		// Input
		case 1:
			if(write(fd_direction, "in", strlen("in")) < 0)
				code_error = APP_REPORT(GPIO, WRITING_FILE);
		break;
		default:
			code_error = APP_REPORT(GPIO, INVALID_VALUE);
		break;
	}

error:
	close(fd_direction);
	close(fd_export);
	
	return code_error;
}

error_t gpio_free(struct gpio *gpio)
{
	error_t	code_error = NO_ERROR;
	int8_t 	fd_unexport;			// File descriptor export file
	char 	gpio_str[4] = {0}; 		// String gpio

	fd_unexport = open("/sys/class/gpio/unexport", O_WRONLY);

	if(fd_unexport < 0)
		return APP_REPORT(GPIO, OPENING_FILE);

	// GPIO number as character string
	sprintf(gpio_str, "%d", gpio->gpio);

	// Write pin number in /sys/class/gpio/unexport
	if(write(fd_unexport, gpio_str, strlen(gpio_str)) < 1)
		code_error = APP_REPORT(GPIO, WRITING_FILE);

	close(fd_unexport);

	return code_error;
}

error_t gpio_get_value(struct gpio *gpio, unsigned *value)
{
	error_t code_error = NO_ERROR;
	char 	gpio_value_str[2] = {0}; 	// String gpio
	char	gpio_path_str[50] = {0}; 	// String path gpio

	int8_t	fd_value;		// File descriptor

	sprintf(gpio_path_str, "/sys/class/gpio/gpio%d/value", gpio->gpio);

	fd_value = open(gpio_path_str, O_RDONLY);

	if(fd_value < 0)
		return APP_REPORT(GPIO, OPENING_FILE);
	
	if(read(fd_value, gpio_value_str, 1) < 1){
		code_error = APP_REPORT(GPIO, READING_FILE);
		goto error;
	}

	*value = atoi(gpio_value_str);

error:

	close(fd_value);
	return code_error;
}

error_t gpio_get_direction(struct gpio *gpio, char *direction)
{
	error_t code_error = NO_ERROR;

	char	gpio_path_str[50] = {0}; 	// String path gpio
	int8_t	fd_direction;		// File descriptor

	sprintf(gpio_path_str, "/sys/class/gpio/gpio%d/direction", gpio->gpio);

	fd_direction = open(gpio_path_str, O_RDONLY);

	if(fd_direction < 0)
		return APP_REPORT(GPIO, OPENING_FILE);

	if(read(fd_direction, direction, 4) < 2)
		code_error = APP_REPORT(GPIO, READING_FILE);

	close(fd_direction);
	return code_error;
}

error_t gpio_set_value(struct gpio *gpio, unsigned value)
{
	error_t	code_error = NO_ERROR;
	char 	gpio_value_str[2] = {0}; 	// String gpio
	char	gpio_path_str[50] = {0}; 	// String path gpio
	int8_t	fd_value;

	if(value < 0 || value > 1)
		return APP_REPORT(GPIO, INVALID_VALUE);

	sprintf(gpio_path_str, "/sys/class/gpio/gpio%d/value", gpio->gpio);

	fd_value = open(gpio_path_str, O_WRONLY);
	if(fd_value < 0)
		return APP_REPORT(GPIO, OPENING_FILE);

	sprintf(gpio_value_str, "%d", value);

	if(write(fd_value, gpio_value_str, strlen(gpio_value_str)) < 0)
		code_error = APP_REPORT(GPIO, WRITING_FILE);

	close(fd_value);

	return code_error;
}

