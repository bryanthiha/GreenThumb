#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include<stdio.h>


int main(void)
{
    // printf("Hello World");

    DDRD |= (1 << 2);         // Set PORTD for pump controller output
    // PORTD &= ~(1 << PD2);    // PD2 will be used for pump controller


    while(1)
    {
       
        PORTD |= (1 << PD2);      
        _delay_ms(500);         
        PORTD &= ~(1 << PD2);   
        _delay_ms(500); 
    }
    
    return 0;   /* never reached */
}