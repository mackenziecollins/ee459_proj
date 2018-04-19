//sci.c
/*
  Code Provided by Professor A. Weber. Accessed through EE459 website.
*/
/* ----------------------------------------------------------------------- */

/*
  sci_init - Initialize the SCI port
*/
#include "sci.h"

#define FOSC 7372800		// Clock frequency
#define BAUD 115200              // Baud rate used by the LCD
#define MYUBRR FOSC/16/BAUD-1   // Value for UBRR0 register

// volatile bool Received_ISR_end = 0;
// volatile struct Array *storage_buffer;
// volatile char single_buf = ' ';

void sci_init(void) {
    UCSR0B |= (1 << RXCIE0);    // Enable receiver interrupts


    // UBRR0 = MYUBRR;          // Set baud rate
    // UCSR0C = (3 << UCSZ00);  // Set for asynchronous operation, no parity, 
    //                          // one stop bit, 8 data bits
    // UCSR0B = (1<<RXEN0)|(1<<TXEN0);  // Turn on transmitter

    UBRR0H = (unsigned char)(MYUBRR >> 8);
    UBRR0L = (unsigned char)MYUBRR;
    UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
     /* Set frame format: 8data, 2stop bit */
    UCSR0C = (0<<USBS0)|(3<<UCSZ00);

    sei();                      // Enable interrupts
    // initArray(storage_buffer, 4);
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

char sci_in(){
	while(!(UCSR0A & (1<<RXC0)));
	 return UDR0;
}

// ISR(USART_RX_vect)
// {
// 	// Code to be executed when the USART receives a byte here
// 	char ch;

//     ch = UDR0;                  // Get the received charater

//     // Store in buffer
//     // insertArray(storage_buffer, ch);
//     // if(!Received_ISR_end){
//       single_buf = ch;
//       Received_ISR_end = 1;
//     // }
//     // If message complete, set flag
//     // if(ch == '\n'){ // read until see a newline character
//     // 	Received_ISR_end = 1;
//     // }
// }

// void clear_buffer(void){
// 	//
// 	freeArray(storage_buffer);
// 	initArray(storage_buffer, 4);
// }