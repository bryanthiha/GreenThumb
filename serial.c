#include <avr/io.h>
#include "serial.h"


#define FOSC 7372800		// Clock frequency
#define BAUD 9600              // Baud rate
#define MYUBRR FOSC/16/BAUD-1   // Value for UBRR0 register


void sci_init(void);
void sci_out(char);
void sci_outs(char *);


/*
  sci_init - Initialize the SCI port
*/
void sci_init(void)
{
    UBRR0 = MYUBRR;          // Set baud rate
    UCSR0B |= (1 << TXEN0);  // Turn on transmitter
    UCSR0B |= (1 << RXEN0);  // Turn on receiver
    UCSR0C = (3 << UCSZ00);  // Set for asynchronous operation, no parity, 
                             // one stop bit, 8 data bits
}


/*
  sci_out - Output a byte to SCI port
*/
void sci_out(char ch)
{
    while ( (UCSR0A & (1<<UDRE0)) == 0);
    UDR0 = ch;
}

/*
  sci_outs - Print the contents of the character string "s" out the SCI
  port. The string must be terminated by a zero byte.
*/

void sci_outs(char *s)
{
    char ch;

    while ((ch = *s++) != '\0')
        sci_out(ch);
}

// Ask weber how this function works