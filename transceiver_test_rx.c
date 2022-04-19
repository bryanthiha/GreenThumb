/*
    RECEIVER - use a nrf24L01 to receive data from a TX to indicate which LEDs to light.
    LEDs are on PD5, PD6, and PD7 (red, green, blue).
    The nrf24L01 [CE, CSN, SCK, MOSI, MISO] connects to [PD0, PD1, PD2, PD3, PD4]
    
    TODO: if signal link lost, blank all LEDs
*/

#define F_CPU 7372800UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>
// #include "radioPinFunctions.c"
#include "nrf24.h"
// #include "nrf24.c"

volatile uint8_t data_array[3] = {0,1,0};
uint8_t address_Tx[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};
uint8_t address_Rx[5] = {0xD7,0xD7,0xD7,0xD7,0xD7};

void SetupRadio(){
    nrf24_init();
    nrf24_config(2,sizeof(data_array)); // Channel and payload size
    nrf24_tx_address(address_Tx);
    nrf24_rx_address(address_Rx);   
}

void SetupIO(){
    DDRD|=(1<<2)|(1<<3)|(1<<4); // traffic light LEDs
}

void ShowLights(){
    if (data_array[0]>0) {PORTD|=(1<<2);} else {PORTD&=~(1<<2);}
    if (data_array[1]>0) {PORTD|=(1<<3);} else {PORTD&=~(1<<3);}
    if (data_array[2]>0) {PORTD|=(1<<4);} else {PORTD&=~(1<<4);}
}

int main()
{
    SetupIO();
    SetupRadio();

    ShowLights();

    for(;;){         
        if(nrf24_dataReady())
        {
            nrf24_getData(data_array);
            ShowLights();
        }
    }
}