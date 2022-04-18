#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>

#include "adc.h"
#include "lcd.h"
#include "serial.h"
#include "i2c_master.h"
#include "liquid_crystal_i2c.h"

char str1[] = ">>> at328-4.c <<78901234";
char str2[] = ">> USC EE459L <<78901234";

int main(void)
{
    // printf("Hello World\n");

    //Outputs

    DDRD |= (1 << 2);         // Set PORTD2 for pump controller output    PORTD &= ~(1 << PD2);    // PD2 will be used for pump controller
    DDRD |= (1 << 3);         // Set PORTD4 for canopy motor
    DDRD |= (1 << 4);         // Set PORTD4 for light output

    DDRC |= 1 << DDC0;          // Set PORTC bit 0 for output

    // Inputs
    DDRC &= ~(1 << PC2);      // Set PORTC for light sensor input

    adc_init();
    unsigned char adc_result;
    adc_result = adc_sample();

    sci_init();                 // Initialize the SCI port
    
   //  lcd_init();                 // Initialize the LCD display

   //  lcd_moveto(0, 0);
   //  lcd_stringout(str1);        // Print string on line 1

   //  lcd_moveto(1, 0);
   //  lcd_stringout(str2);  

   LiquidCrystalDevice_t device = lq_init(0x27, 16, 2, LCD_5x8DOTS);
   lq_setCursor(&device, 0, 0);
   lq_print(&device, "Hello world!");
   lq_setCursor(&device, 1, 0); // moving cursor to the next line
   lq_print(&device, "How are you?");
   _delay_ms(2000);

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
      

       if(adc_result > 128)
       {

            PORTC |= (1 << PC0);      
            _delay_ms(500);         
   
            
       }
       else{
            PORTC &= ~(1 << PC0);
             _delay_ms(500);
       }

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