#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>

#include "adc.h"
#include "serial.h"

int main(void)
{
    // printf("Hello World\n");

    //Outputs

    DDRD |= (1 << 2);         // Set PORTD2 for pump controller output    PORTD &= ~(1 << PD2);    // PD2 will be used for pump controller
    DDRD |= (1 << 3);         // Set PORTD4 for canopy motor
    DDRD |= (1 << 4);         // Set PORTD4 for light output

    // Inputs
    DDRC &= ~(1 << 2);      // Set PORTC for light sensor input

    adc_init();
    unsigned char adc_result;
    adc_result = adc_sample();

    sci_init();                 // Initialize the SCI port
    

    while(1)
    {
    //    Solar Panel Readings
       
       adc_result = adc_sample();
       char buffer[20];
       snprintf(buffer, 20, "%d", adc_result);

    //    while(index != 8)
    //    {
    //        result[index] = (adc_result >> index) & 1;
    //        index +=1;
    //    }

       sci_outs(buffer);
       _delay_ms(500);


    //    if(adc_result > 128)
    //    {

    //         PORTD |= (1 << PD2);      
    //         _delay_ms(500);         
   
            
    //    }
    //    else{
    //         PORTD &= ~(1 << PD2);
    //          _delay_ms(500);
    //    }

        // Turn on Pump Controller
        PORTD |= (1 << PD2);      
        _delay_ms(500);         
        PORTD &= ~(1 << PD2);   
        _delay_ms(500); 

     // Turn on canopy motor
        PORTD |= (1 << PD3);      
        _delay_ms(500);         
        PORTD &= ~(1 << PD3);   
        _delay_ms(500);


        // Turn on Light output
        PORTD |= (1 << PD4);      
        _delay_ms(500);         
        PORTD &= ~(1 << PD4);   
        _delay_ms(500);

        // Moisture Sensor Readings
    }
    
    return 0;   /* never reached */
}