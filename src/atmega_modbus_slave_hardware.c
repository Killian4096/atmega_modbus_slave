#include "atmega_modbus_slave.h"


void atmega_modbus_slave_hardware_UART_init(void){
    //initialization
    //Baud rate
    UBRR0H = (BAUD_PRESCALER>>8);
    UBRR0L = (BAUD_PRESCALER);
    //Enable rx and tx
    //UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
    //Format 8data, 2 stop bit, no parity
    UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00) | (1<<USBS0);

    //modbus_slave_hardware_UART_receive_toggle(0);
    //modbus_slave_hardware_UART_transmit_toggle(0);
}

uint8_t atmega_modbus_slave_hardware_UART_receive_complete(void){
    //Return if new message
    return (UCSR0A&(1<<RXC0)) > 0;
}

uint8_t atmega_modbus_slave_hardware_UART_transmit_complete(void){
    //Return if new message
    return (UCSR0A&(1<<TXC0)) > 0;
}

void atmega_modbus_slave_hardware_UART_transmit_reset(void){
    //Clear TXC0 by writing 1, see datasheet
    UCSR0A |= (1<<TXC0);
}

uint8_t atmega_modbus_slave_hardware_UART_data_register_empty(void){
    //Return if new message
    return (UCSR0A&(1<<UDRE0)) > 0;
}

void atmega_modbus_slave_hardware_UART_data_register_load(uint8_t data){
    UDR0 = data;
}

uint8_t atmega_modbus_slave_hardware_UART_data_register_read(void){
    return UDR0;
}

void atmega_modbus_slave_hardware_UART_data_register_flush(void){
    uint8_t dummy;
    while (UCSR0A & (1<<UDRE0)) {
        dummy = UDR0;
    }
    dummy = dummy + 1;
}

void atmega_modbus_slave_hardware_UART_receive_toggle(uint8_t enable){
    if (enable){
        UCSR0B |= (1<<RXEN0);
    }
    else{
        UCSR0B &= ~(1<<RXEN0);
    }
}

void atmega_modbus_slave_hardware_UART_transmit_toggle(uint8_t enable){
    if (enable){
        UCSR0B |= (1<<TXEN0);
    }
    else{
        UCSR0B &= ~(1<<TXEN0);
    }
}

