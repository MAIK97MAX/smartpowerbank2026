/*
 * main.c
 *
 * Created: 25.06.2026 22:47:29
 * Author : Malik
 */ 

#define F_CPU 8000000UL
#define INA_REG_SHUNT_V 0x01
#define INA_REG_BUS_V 0x02
#define INA_REG_CURRENT 0x04
#define INA_REG_CALIBRATION 0x05
#define INA_CALIBRATION 0x1000
#define INA1_W 0x80
#define INA1_R 0x81
#define INA2_W 0x88
#define INA2_R 0x89

#include <avr/io.h>
#include <util/delay.h>
#include "molibdisplay.h"

uint16_t ina_read_reg(uint8_t addr_w, uint8_t addr_r, uint8_t reg)
{
	uint16_t value;

	if (!twi_s_start(addr_w))
	{
		twi_s_stop();
		return 0xFFFF;
	}

	if (!twi_s_write(reg))
	{
		twi_s_stop();
		return 0xFFFF;
	}

	if (!twi_s_rep_start(addr_r))
	{
		twi_s_stop();
		return 0xFFFF;
	}

	value = ((uint16_t)twi_s_read(ACK)) << 8;
	value |= twi_s_read(NACK);

	twi_s_stop();

	return value;
}

uint8_t ina_write_reg(uint8_t addr_w, uint8_t reg, uint16_t value) 
{
	if(!twi_s_start(addr_w)) 
	{
		twi_s_stop();
		return 0;
	}
	
	if(!twi_s_write(reg))
	{
		twi_s_stop();
		return 0;
	}
	
	if(!twi_s_write((uint8_t)(value >> 8)))
	{
		twi_s_stop();
		return 0;
	}
	
	if(!twi_s_write((uint8_t)value))
	{
		twi_s_stop();
		return 0;
	}
	
	twi_s_stop();
	
	return 1;
}

float ina_bus_voltage(uint8_t addr_w, uint8_t addr_r)
{
	uint16_t raw = ina_read_reg(addr_w, addr_r, INA_REG_BUS_V);

	raw >>= 3;              // Bits 15..3 enthalten die Busspannung
	return raw * 0.004;    // 4 mV pro Bit
}

int16_t ina_shunt_raw(uint8_t addr_w, uint8_t addr_r)
{
	return (int16_t)ina_read_reg(addr_w, addr_r, INA_REG_SHUNT_V);
}

int16_t ina_current(uint8_t addr_w, uint8_t addr_r)
{
	return (int16_t)ina_read_reg(addr_w, addr_r, INA_REG_CURRENT);
}

void init() {
	DDRB |= (1 << PB5);
	PORTB |= (1 << PB5);
}

void ina_init()
{
	ina_write_reg(INA1_W, INA_REG_CALIBRATION, INA_CALIBRATION);
	ina_write_reg(INA2_W, INA_REG_CALIBRATION, INA_CALIBRATION);
	
	_delay_ms(1);
}

int main(void)
{
	init();
	display_init();
	ina_init();
	
	display_clear();

    while (1) 
    {   
		/*
		int16_t s1 = ina_shunt_raw(INA1_W, INA1_R);
		int16_t c1 = ina_current(INA1_W, INA1_R);

		int16_t s2 = ina_shunt_raw(INA2_W, INA2_R);
		int16_t c2 = ina_current(INA2_W, INA2_R);

		display_clear();
		display_printf_pos(0, 0, "1 S:%d C:%d", s1, c1);
		display_printf_pos(0, 1, "2 S:%d C:%d", s2, c2);
		*/
	
		float u1 = ina_bus_voltage(INA1_W, INA1_R);
		float u2 = ina_bus_voltage(INA2_W, INA2_R);
		
		int16_t i1 = ina_current(INA1_W, INA1_R);
		int16_t i2 = ina_current(INA2_W, INA2_R);

		display_clear();
		display_printf_pos(0, 0, "OUT1:%d.%02dV",
		(int)u1,
		((int)(u1 * 100)) % 100);

		display_printf_pos(0, 1, "OUT2:%d.%02dV",
		(int)u2,
		((int)(u2 * 100)) % 100);
		
		display_printf_pos(0,2, "I1:%dmA", i1);
		display_printf_pos(0,3, "I2:%dmA", i2);

		_delay_ms(500);
    }
}

