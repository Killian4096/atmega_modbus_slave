#include "atmega_modbus_slave.h"


void atmega_modbus_slave_wait_init(struct atmega_modbus_slave_t* atmega_modbus_slave_tag){
    atmega_modbus_slave_tag->state = ATMEGA_MODBUS_SLAVE_STATE_WAIT;
    atmega_modbus_slave_hardware_UART_receive_toggle(1);
    atmega_modbus_slave_hardware_UART_transmit_toggle(0);
}

void atmega_modbus_slave_wait(struct atmega_modbus_slave_t* atmega_modbus_slave_tag){
    //Bypass if not in wait
    if (atmega_modbus_slave_tag->state != ATMEGA_MODBUS_SLAVE_STATE_WAIT){
        return;
    }

    //If new message transmition to receive state
    if (atmega_modbus_slave_hardware_UART_receive_complete()) {
        atmega_modbus_slave_receive_init(atmega_modbus_slave_tag);
    }
}
