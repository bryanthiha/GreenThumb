#include <avr/io.h>
#include "adc.h"


void adc_init()
{
    // Initialize the ADC
    
    // Bits REFS1 and REFS0 control the selection of the high reference source. 01 for AVCC
    // The ADLAR bit determines whether to left adjust the result or right adjust it. left adjust with 8 bits
    
    ADMUX |= ((1 << ADLAR) | (1 << REFS0));
    
	ADMUX &= ~(1 << REFS1);
	
	ADMUX &= 0b11110000;
	
	// ADMUX |= (1 << MUX1);  // Configuring PC2 for light sensor... DONT FORGET TO CONFIGURE PC1 FOR MOISTURE SENSOR

	
    // The ADEN bit enables the ADC module. Must be set to 1 to do any ADC operations.
	
	ADCSRA |= ((1 << ADPS1) | (1 << ADPS2) | (1 << ADEN));
    ADCSRA &= ~(1 << ADPS0);

    // The ADPS2, ADPS1 and ADPS0 bits selects the prescaler divisor value. 1 1 0 for a pre scalar of 64 --> Clock/atmega range = 7372800/64 ~ 115 kHZ (needs to be 50 - 200kHz)
	
	ADCSRA &= ~(1 << ADSC);   // Setting the ADSC bit to a 1 initiates a single conversion. This bit will remain a 1 until the conversion is complete. 
                              // If your program using the polling method to determine when the conversion is compete, 
                              // it can test the state of this bit to determine when it can read the result of the conversion from the data registers.
                              // As long as this bit is a one, the data registers do not yet contain a valid result
	
    // ADCSRA &= 0b11000111;
    // ADMUX = 0b01000010;
    // ADCSRA = 0b10000111;

}

unsigned char adc_sample(unsigned char channel)
{
    ADMUX &= 0b11110000;
    ADMUX |= channel;           // channel is ADC pin number, 

    // Convert an analog input and return the 8-bit result
    
    ADCSRA |= (1 << ADSC);
    while((ADCSRA & (1 << ADSC)) != 0)
    {}
    
    unsigned char result = ADCH;

	return (result);
}
