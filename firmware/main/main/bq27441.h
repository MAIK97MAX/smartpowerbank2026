/*
 * bq27441.h
 *
 * Created: 28.06.2026 14:50:37
 *  Author: Malik
 */ 


#ifndef BQ27441_H_
#define BQ27441_H_

#include <stdint.h>

void bq_probe_start(void);

uint8_t bq_probe_twcr(void);
uint8_t bq_probe_twsr(void);
uint8_t bq_probe_pins(void);

#endif /* BQ27441_H_ */