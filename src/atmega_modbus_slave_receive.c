#include "atmega_modbus_slave.h"


void atmega_modbus_slave_receive_init(struct atmega_modbus_slave_t* atmega_modbus_slave_tag) {
    //Set state
    atmega_modbus_slave_tag->state = ATMEGA_MODBUS_SLAVE_STATE_RECEIVE;

    //Reset timer
    atmega_modbus_slave_tag->receive_timeout_cycles_acc = 0;

    //Change UART direction
    atmega_modbus_slave_hardware_UART_transmit_toggle(0);
    atmega_modbus_slave_hardware_UART_receive_toggle(1);

    //Reset data buffer
    modbus_slave_input_data_buffer_init(&(atmega_modbus_slave_tag->modbus_slave_tag));
}

void atmega_modbus_slave_receive(struct atmega_modbus_slave_t* atmega_modbus_slave_tag) {
    //Bypass if not in state
    if (atmega_modbus_slave_tag->state != ATMEGA_MODBUS_SLAVE_STATE_RECEIVE){
        return;
    }

    //If recent transmission
    if (atmega_modbus_slave_hardware_UART_receive_complete()) {
        //Load new data to buffer
        modbus_slave_input_data_buffer_add(&(atmega_modbus_slave_tag->modbus_slave_tag), atmega_modbus_slave_hardware_UART_data_register_read());
        //Reset Timeout
        atmega_modbus_slave_tag->receive_timeout_cycles_acc = 0;
    }
    //If waiting
    else {
        //Increase timeout
        atmega_modbus_slave_tag->receive_timeout_cycles_acc += 1;
        //Check if timed out
        if (atmega_modbus_slave_tag->receive_timeout_cycles_acc > atmega_modbus_slave_tag->receive_timeout_cycles){
            //If timed out set exit
            atmega_modbus_slave_process_init(atmega_modbus_slave_tag);
        }
    }
}
