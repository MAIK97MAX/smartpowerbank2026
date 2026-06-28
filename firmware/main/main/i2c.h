/*
 * i2c.h
 *
 * Created: 27.06.2026 19:59:01
 *  Author: Malik
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

void i2c_init(void);

uint8_t i2c_start(uint8_t address);

void i2c_stop(void);

uint8_t i2c_write(uint8_t data);

uint8_t i2c_readAck(void);

uint8_t i2c_readNack(void);

#endif /* I2C_H_ */