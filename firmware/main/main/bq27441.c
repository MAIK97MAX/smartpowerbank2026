/*
 * bq27441.c
 *
 * Created: 28.06.2026 16:25:13
 *  Author: Malik
 */ 

#define BQ27441_ADDR_W      0xAA
#define BQ27441_ADDR_R      0xAB

#define BQ_CMD_CONTROL      0x00
#define BQ_CMD_TEMPERATURE  0x02
#define BQ_CMD_VOLTAGE      0x04
#define BQ_CMD_FLAGS        0x06
#define BQ_CMD_REMAINING    0x0C
#define BQ_CMD_CURRENT      0x10
#define BQ_CMD_SOC          0x1C

#define BQ_CTRL_DEVICE_TYPE 0x0001
uint8_t bq_read_reg(uint8_t reg, uint16_t *value)
{
	uint8_t low;
	uint8_t high;

	if (twi_s_start(BQ27441_ADDR_W) != ACK)
	{
		twi_s_stop();
		return 0;
	}

	if (twi_s_write(reg) != ACK)
	{
		twi_s_stop();
		return 0;
	}

	if (twi_s_rep_start(BQ27441_ADDR_R) != ACK)
	{
		twi_s_stop();
		return 0;
	}

	low = twi_s_read(ACK);
	high = twi_s_read(NACK);

	twi_s_stop();
	_delay_us(70);

	*value = (uint16_t)low | ((uint16_t)high << 8);

	return 1;
}
uint8_t bq_write_reg(uint8_t reg, uint16_t value)
{
	if (twi_s_start(BQ27441_ADDR_W) != ACK)
	{
		twi_s_stop();
		return 0;
	}

	if (twi_s_write(reg) != ACK)
	{
		twi_s_stop();
		return 0;
	}

	if (twi_s_write((uint8_t)value) != ACK)
	{
		twi_s_stop();
		return 0;
	}

	if (twi_s_write((uint8_t)(value >> 8)) != ACK)
	{
		twi_s_stop();
		return 0;
	}

	twi_s_stop();
	_delay_us(70);

	return 1;
}
uint8_t bq_control(uint16_t subcommand, uint16_t *answer)
{
	if (!bq_write_reg(BQ_CMD_CONTROL, subcommand))
	{
		return 0;
	}

	_delay_ms(1);

	return bq_read_reg(BQ_CMD_CONTROL, answer);
}