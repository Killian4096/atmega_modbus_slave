#include "atmega_modbus_slave.h"


void atmega_modbus_slave_transmit_init(struct atmega_modbus_slave_t* atmega_modbus_slave_tag) {
    atmega_modbus_slave_tag->transmit_timeout_cycles_acc = 0;
    atmega_modbus_slave_tag->state = ATMEGA_MODBUS_SLAVE_STATE_TRANSMIT;
    atmega_modbus_slave_tag->transmit_initiated = 0;
    atmega_modbus_slave_hardware_UART_receive_toggle(0);
    atmega_modbus_slave_hardware_UART_transmit_toggle(1);

    //Reset traverse index
    atmega_modbus_slave_tag->output_data_buffer_acc = 0;
}

void atmega_modbus_slave_transmit(struct atmega_modbus_slave_t* atmega_modbus_slave_tag) {
    //Bypass if not in state
    if (atmega_modbus_slave_tag->state != ATMEGA_MODBUS_SLAVE_STATE_TRANSMIT){
        return;
    }

    //If not done transmiting buffer transmit next item
    if (atmega_modbus_slave_tag->output_data_buffer_acc < atmega_modbus_slave_tag->modbus_slave_tag.output_data_buffer.length){
        //If not started init transmission
        if(!atmega_modbus_slave_tag->transmit_initiated){
            //Reset Transmit
            atmega_modbus_slave_hardware_UART_transmit_reset();
            //Transmit buffer
            atmega_modbus_slave_hardware_UART_data_register_load(atmega_modbus_slave_tag->modbus_slave_tag.output_data_buffer.array[atmega_modbus_slave_tag->output_data_buffer_acc]);
            //Reset transmit
            atmega_modbus_slave_tag->transmit_initiated = 1;
            //Reset timeout
            atmega_modbus_slave_tag->transmit_timeout_cycles_acc = 0;
        }
        //If transmit inited already check if done, if so move acc up
        else if(atmega_modbus_slave_hardware_UART_transmit_complete()){
            //Increase acc
            atmega_modbus_slave_tag->output_data_buffer_acc += 1;
            //Reset transmit
            atmega_modbus_slave_tag->transmit_initiated = 0;
        }
    }
    //If done exit
    else{
        atmega_modbus_slave_wait_init(atmega_modbus_slave_tag);
    }
}


/*
 * This works
if(!modbus_slave_tag.transmit_initiated){
    //Reset Transmit
    modbus_slave_hardware_UART_transmit_reset();
    //Transmit buffer
    modbus_slave_hardware_UART_data_register_load(50);
    //Reset transmit
    modbus_slave_tag.transmit_initiated = 1;
}
else if(modbus_slave_hardware_UART_transmit_complete()){
    modbus_slave_tag = modbus_slave_wait_init(modbus_slave_tag);
}



return modbus_slave_tag;
*/
