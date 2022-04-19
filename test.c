#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>


#include "adc.h"
#include "lcd.h"
#include "serial.h"
// #include "i2c_master.h"
// #include "liquid_crystal_i2c.h"

#define FOSC 7372800		// Clock frequency
#define BAUD 9600              // Baud rate
#define MYUBRR FOSC/16/BAUD-1   // Value for UBRR0 register
#define BDIV (FOSC / 100000 - 16) / 2 + 1    // Puts I2C rate just below 100kHz

#define LIGHT 2      // ADC light sensor channel
#define MOISTURE 1      // ADC Moisture sensor channel


char str1[] = ">>> at328-4.c <<78901234";
char str2[] = ">> USC EE459L <<78901234";

int main(void)
{
    // printf("Hello World\n");

    //Outputs

    DDRD = 0b00000000;

    DDRD |= (1 << 2);         // Set PORTD2 for pump controller output    PORTD &= ~(1 << PD2);    // PD2 will be used for pump controller
    DDRD |= (1 << 3);         // Set PORTD4 for canopy motor
    DDRD |= (1 << 4);         // Set PORTD4 for light output

    DDRC |= 1 << DDC0;          // Set PORTC bit 0 for output

    // Inputs
    DDRC &= ~(1 << PC2);      // Set PORTC for light sensor input
    DDRC &= ~(1 << PC5);
    DDRC &= ~(1 << PC4);

    PORTC |= (1 << PC4);
    PORTC |= (1 << PC5);    
    PORTD &= ~(1 << PD2);

    PORTD = 0b00000000;

    adc_init();
    unsigned char adc_result_light, adc_result_moisture;

   //  adc_result_light = adc_sample(LIGHT);

   //  sci_init();                 // Initialize the SCI port

    
   //  lcd_init();                 // Initialize the LCD display

   //  lcd_moveto(0, 0);
   //  lcd_stringout(str1);        // Print string on line 1

   //  lcd_moveto(1, 0);
   //  lcd_stringout(str2); 
   //  _delay_ms(2000); 

   // LiquidCrystalDevice_t device = lq_init(0x27, 16, 2, LCD_5x8DOTS);
   // lq_setCursor(&device, 0, 0);
   // lq_print(&device, "Hello world!");
   // lq_setCursor(&device, 1, 0); // moving cursor to the next line
   // lq_print(&device, "How are you?");
   // _delay_ms(2000);

    while(1)
    {
      
      //Solar Panel Readings 
      adc_result_light = adc_sample(LIGHT);      

      if(adc_result_light < 64)                 // If we don't have enough light, we will turn on LEDs
      {
         PORTD |= (1 << PD4);
      }
      
      else
      {
         PORTD &= ~(1 << PD4);

         if(adc_result_light > 200)          // If too much light, deploy canopy
         {
            PORTD |= (1 << PD3);
         } 
         else
         {
            PORTD &= ~(1 << PD3);
         }
      }

      
      // Moisture Sensor Readings
      adc_result_moisture = adc_sample(MOISTURE);     // If we don't have enough moisture, we will turn on water pump

      if(adc_result_moisture < 150)
      {
         PORTD |= (1 << PD2);
      }
      else
      {
         PORTD &= ~(1 << PD2);
      }
      
    }
    
    return 0;   /* never reached */
}



//  char buffer[20];
      //  snprintf(buffer, 20, "%d", adc_result);

    //    while(index != 8)
    //    {
    //        result[index] = (adc_result >> index) & 1;
    //        index +=1;
    //    }

      //  sci_outs(buffer);
      //  _delay_ms(500);



   //      // Turn on Pump Controller
   //      PORTD |= (1 << PD2);      
   //      _delay_ms(500);         
   //      PORTD &= ~(1 << PD2);   
   //      _delay_ms(500); 

   //   // Turn on canopy motor
   //      PORTD |= (1 << PD3);      
   //      _delay_ms(500);         
   //      PORTD &= ~(1 << PD3);   
   //      _delay_ms(500);


   //      // Turn on Light output
   //      PORTD |= (1 << PD4);      
   //      _delay_ms(500);         
   //      PORTD &= ~(1 << PD4);   
   //      _delay_ms(500);