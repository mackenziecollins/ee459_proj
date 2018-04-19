//main2.c
//main.c
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>
#include "sci.h"

# define FOSC 9830400 // Clock frequency = Oscillator freq .
# define BDIV ( FOSC / 100000 - 16) / 2 + 1

#define MYSTRING_LEN(s) strlen(s)



unsigned char old_sec = NULL;
unsigned char old_minute = NULL;
unsigned char old_hour = NULL;

unsigned char old_day = NULL;
// unsigned char old_weekday = NULL;
unsigned char old_month = NULL;
unsigned char old_year = NULL;

volatile char single_buf[4];
volatile bool Received_ISR_end = 0;
volatile int counter = 0;

volatile int count = 0;
volatile int before = 0;
volatile int hold = 0;


char checkInput(char bit)
{
    if ((PIND & (1 << bit)) != 0)
        return(1);
    else
        return(0);
}


ISR(PCINT0_vect){
    //shift four bits to the right to make easier to handle
    hold = (( PINB & 0b00000110) >> 1);
    // Print_a_character(0x70);
    
    //starting at 0
    if (before == 0){
        //turned clockwise
        if (hold == 1){
            count++;
            if(count>59){
            	count=0;
            }
        }
        //turned counter clockwise
        else if (hold == 2){
            count--;
            if(count<0){
            	count=59;
            }
        }
    }
    
    //starting at 1
    else if (before == 1){
        //turned clockwise
        if (hold == 3){
            count++;
            if(count>59){
            	count=0;
            }
        }
        //turned counterclockwise
        else if(hold == 0){
            count--;
            if(count<0){
            	count=59;
            }
        }
        
    }
    
    //starting at 3
    else if (before == 3){
        //turned clockwise
        if (hold == 2){
            count++;
            if(count>59){
            	count=0;
            }
        }
        //turned counterclockwise
        else if (hold == 1){
            count--;
            if(count<0){
            	count=59;
            }
        }
        
    }
    
    //starting at 2
    else if (before == 2){
        //turned clockwise
        if (hold == 0){
            count++;
            if(count>59){
            	count=0;
            }
        }
        //turned counterclockwise
        else if (hold == 3){
            count--;
            if(count<0){
            	count=59;
            }
        }
        
    }
    
    before = hold;
}

ISR(USART_RX_vect)
{
	// Code to be executed when the USART receives a byte here
	char ch;

    ch = UDR0;                  // Get the received charater

    // Store in buffer
    // insertArray(storage_buffer, ch);
    if(!Received_ISR_end){
    // Print_a_character(ch);
      single_buf[counter] = ch;
      counter++;
    }
    if(counter == 4){
    	Received_ISR_end = 1;
    }
    // If message complete, set flag
    // if(ch == '\n'){ // read until see a newline character
    // 	Received_ISR_end = 1;
    // }
}

void message_waiting_routine(){
	while(!Received_ISR_end);
	Received_ISR_end = 0;
	counter = 0;
}

int main(void){
	// PORTC = 0x00;
	DDRC &= 0b11110000;

	PORTD = 0x00;
	DDRD &= 0b11000011; // 5, 4, 3, 2 is input

	PORTB |= (1 << PB1) | (1 << PB2);
	DDRB &= 0b11111001;

	PCICR |= (1 << PCIE0);
    
    PCMSK0 |= (1 << PCINT1);
    PCMSK0 |= (1 << PCINT2);
    // sei();


	sci_init();

	/* ----------------------  Segment for Serial Communication Testing
	*/

	// sci_outs("AT");
	// sci_out('A');
	// rtc_subroutine_time();
	// Print_a_character(0x30);
	
	while(1){
		// sci_out(0b01010101);
		_delay_ms(1000);
		// sci_outs("AbCd");

		message_waiting_routine();
		if(strcmp("SEND", single_buf)==0){
			sci_outs("RecV");
		}else{
            sci_outs("WHat");
        }

		/* ----------------------------- Segment for Serial Communication Testing
		*/
		// if(Received_ISR_end){
		// 	Received_ISR_end = 0;
		// 	Print_multiple_character(storage_buffer->array, storage_buffer->size);
		// 	clear_buffer();
		// }

	}
	return 0;
}
