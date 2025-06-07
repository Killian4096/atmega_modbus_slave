#include "atmega_modbus_slave.h"
#include "atmega_modbus_slave_hardware.c"
#include "atmega_modbus_slave_receive.c"
#include "atmega_modbus_slave_process.c"
#include "atmega_modbus_slave_transmit.c"
#include "atmega_modbus_slave_wait.c"

void atmega_modbus_slave(struct atmega_modbus_slave_t* atmega_modbus_slave_tag){
    atmega_modbus_slave_launcher(atmega_modbus_slave_tag);
    atmega_modbus_slave_wait(atmega_modbus_slave_tag);
    atmega_modbus_slave_receive(atmega_modbus_slave_tag);
    atmega_modbus_slave_process(atmega_modbus_slave_tag);
    atmega_modbus_slave_transmit(atmega_modbus_slave_tag);
}

void atmega_modbus_slave_init(struct atmega_modbus_slave_t* atmega_modbus_slave_tag){
    //Init state
    atmega_modbus_slave_tag->state = 0;

    //Set Timeouts
    atmega_modbus_slave_tag->receive_timeout_cycles = ATMEGA_MODBUS_SLAVE_TIMEOUT_RECEIVE;
    atmega_modbus_slave_tag->transmit_timeout_cycles = ATMEGA_MODBUS_SLAVE_TIMEOUT_TRANSMIT;
}

void atmega_modbus_slave_launcher(struct atmega_modbus_slave_t* atmega_modbus_slave_tag){
    //Bypass if not in state
    if (atmega_modbus_slave_tag->state != ATMEGA_MODBUS_SLAVE_STATE_UNINIT){
        return;
    }
    //Init Hardware
    atmega_modbus_slave_hardware_UART_init();

    //Enter Wait
    atmega_modbus_slave_wait_init(atmega_modbus_slave_tag);
}

