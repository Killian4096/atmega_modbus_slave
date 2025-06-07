#ifndef __ATMEGA_MODBUS_SLAVE_H__
#define __ATMEGA_MODBUS_SLAVE_H__
#include <stdint.h>
#include <avr/io.h>
#include "modbus_slave.h"

#include "atmega_modbus_slave_settings.h"

#include "atmega_modbus_slave_t.h"


void atmega_modbus_slave_hardware_UART_init(void);
uint8_t atmega_modbus_slave_hardware_UART_receive_complete(void);
uint8_t atmega_modbus_slave_hardware_UART_transmit_complete(void);
void atmega_modbus_slave_hardware_UART_transmit_reset(void);
uint8_t atmega_modbus_slave_hardware_UART_data_register_empty(void);
void atmega_modbus_slave_hardware_UART_data_register_load(uint8_t);
uint8_t atmega_modbus_slave_hardware_UART_data_register_read(void);
void atmega_modbus_slave_hardware_UART_data_register_flush(void);
void atmega_modbus_slave_hardware_UART_receive_toggle(uint8_t);
void atmega_modbus_slave_hardware_UART_transmit_toggle(uint8_t);

void atmega_modbus_slave_init(struct atmega_modbus_slave_t*);

void atmega_modbus_slave(struct atmega_modbus_slave_t*);
void atmega_modbus_slave_launcher(struct atmega_modbus_slave_t*);

void atmega_modbus_slave_wait(struct atmega_modbus_slave_t*);
void atmega_modbus_slave_wait_init(struct atmega_modbus_slave_t*);

void atmega_modbus_slave_receive(struct atmega_modbus_slave_t*);
void atmega_modbus_slave_receive_init(struct atmega_modbus_slave_t*);

void atmega_modbus_slave_process(struct atmega_modbus_slave_t*);
void atmega_modbus_slave_process_init(struct atmega_modbus_slave_t*);

void atmega_modbus_slave_transmit(struct atmega_modbus_slave_t*);
void atmega_modbus_slave_transmit_init(struct atmega_modbus_slave_t*);

#endif
