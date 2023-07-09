/*
 * i2c.c
 *
 *      Author: bernardo
 */

#include <stdio.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "I2C.h"

error_t i2c_read(struct i2c_device *i2c_dev)
{
	struct i2c_rdwr_ioctl_data i2c_packet;
	struct i2c_msg message[2];	// We need 2 structs: one for write and one for read
	uint32_t i2c_file;					
	uint8_t outbuf[1];
	error_t error_code = NO_ERROR;

	i2c_file = open(i2c_dev->i2c_port, O_RDWR);
	if(i2c_file < 0)
		return APP_REPORT(I2C, OPENING_FILE);

	// Fill write struct
	// First we must write the register address which we want to start reading.
	outbuf[0] 			= i2c_dev->reg_addr;
	message[0].addr 	= i2c_dev->dev_addr;
	message[0].flags 	= 0; 					// 0 -> Write
	message[0].len 		= 1;					// 1 byte
	message[0].buf		= outbuf;
	// Fill read struct
	message[1].addr		= i2c_dev->dev_addr;
	message[1].flags	= 1;					// 1 -> Read
	message[1].len		= i2c_dev->length;		// N bytes que se van a leer a partir de la direccion reg_addr
	message[1].buf		= i2c_dev->data; 		// Buffer de recepcion

	/* Send the request to the kernel and get the result back */
	i2c_packet.msgs		= message;
	i2c_packet.nmsgs	= 2;

	if(ioctl(i2c_file, I2C_RDWR, &i2c_packet) < 0)
		error_code = APP_REPORT(I2C, WRITING_FILE);

	close(i2c_file);

	return error_code;
}


error_t i2c_write(struct i2c_device *i2c_dev)
{
	struct i2c_rdwr_ioctl_data i2c_packet;
	struct i2c_msg message[1];			
	uint32_t i2c_file;					
	uint8_t outbuf[128] = {0};
	error_t error_code = NO_ERROR;

	i2c_file = open(i2c_dev->i2c_port, O_RDWR);

	if(i2c_file < 0)
		return APP_REPORT(I2C, OPENING_FILE);

	memset(outbuf, 0, sizeof(outbuf));
	outbuf[0] = i2c_dev->reg_addr;

	for(int i = 0; i < i2c_dev->length; i++)
		outbuf[i + 1] = i2c_dev->data[i];
	
	message[0].addr 	= i2c_dev->dev_addr;	// Device address
	message[0].flags 	= 0; 					// 0 -> Write
	message[0].len 		= i2c_dev->length + 1; 	// N bytes write
	message[0].buf		= outbuf;				// First register to write

	// Send the request to the kernel and get the result back
	i2c_packet.msgs		= message;
	i2c_packet.nmsgs	= 1;

	if(ioctl(i2c_file, I2C_RDWR, &i2c_packet) < 0)
		error_code = APP_REPORT(I2C, WRITING_FILE);
	
	close(i2c_file);

	return error_code;
}




