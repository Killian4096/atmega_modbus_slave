#include "atmega_modbus_slave.h"


void atmega_modbus_slave_process_init(struct atmega_modbus_slave_t* atmega_modbus_slave_tag) {
    atmega_modbus_slave_tag->state = ATMEGA_MODBUS_SLAVE_STATE_PROCESS;
    atmega_modbus_slave_hardware_UART_receive_toggle(0);
    atmega_modbus_slave_hardware_UART_transmit_toggle(0);
}

void atmega_modbus_slave_process(struct atmega_modbus_slave_t* atmega_modbus_slave_tag) {
    //Bypass if not in state
    if (atmega_modbus_slave_tag->state != ATMEGA_MODBUS_SLAVE_STATE_PROCESS){
        return;
    }

    modbus_slave(&(atmega_modbus_slave_tag->modbus_slave_tag));

    atmega_modbus_slave_transmit_init(atmega_modbus_slave_tag);
}
