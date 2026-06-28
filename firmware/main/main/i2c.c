/*
 * i2c.c
 *
 * Created: 27.06.2026 20:00:03
 *  Author: Malik
 */ 

#include <avr/io.h>
#include "i2c.h"

#define F_CPU 1000000UL
#define F_SCL 100000UL

void i2c_init(void)
{
	TWSR = 0x00;

	TWBR = ((F_CPU/F_SCL)-16)/2;

	TWCR = (1<<TWEN);
}

uint8_t i2c_start(uint8_t address)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);

	while(!(TWCR & (1<<TWINT)));

	TWDR = address;

	TWCR = (1<<TWINT)|(1<<TWEN);

	while(!(TWCR & (1<<TWINT)));

	return ((TWSR & 0xF8) == 0x18 ||
	(TWSR & 0xF8) == 0x40);
}

void i2c_stop(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);

	while(TWCR & (1<<TWSTO));
}

uint8_t i2c_write(uint8_t data)
{
	TWDR = data;

	TWCR = (1<<TWINT)|(1<<TWEN);

	while(!(TWCR & (1<<TWINT)));

	return ((TWSR & 0xF8) == 0x28);
}

uint8_t i2c_readAck(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);

	while(!(TWCR & (1<<TWINT)));

	return TWDR;
}

uint8_t i2c_readNack(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN);

	while(!(TWCR & (1<<TWINT)));

	return TWDR;
}


