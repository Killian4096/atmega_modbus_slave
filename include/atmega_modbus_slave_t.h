#ifndef __ATMEGA_MODBUS_SLAVE_T__
#define __ATMEGA_MODBUS_SLAVE_T__

struct atmega_modbus_slave_t{
    //State 0=uninit, 1=ready, 2=receiving, 3=transmitting
    uint8_t state;

    //Timeouts
    uint32_t receive_timeout_cycles;
    uint32_t receive_timeout_cycles_acc;

    uint32_t transmit_timeout_cycles;
    uint32_t transmit_timeout_cycles_acc;

    //Modbus logic control
    modbus_slave_t modbus_slave_tag;
    size_t output_data_buffer_acc;

    //Misc
    uint8_t transmit_initiated;

};

typedef struct atmega_modbus_slave_t atmega_modbus_slave_t;

#endif
